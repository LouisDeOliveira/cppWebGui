#include "crow.h"
#include <fstream>
#include <sstream>

// Helper to serve static files
std::string readFile(const std::string &path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
    {
        return "File not found";
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

int main()
{
    crow::SimpleApp app;

    // Route to serve static files (e.g., index.html)
    CROW_ROUTE(app, "/")([]() { return crow::response(readFile("../src/static/index.html")); });

    // Serve other static assets (CSS, JS)
    CROW_ROUTE(app, "/<string>")
    ([](const std::string &filename) { return crow::response(readFile("../src/static/" + filename)); });

    // WebSocket or API route
    CROW_ROUTE(app, "/api/click")
        .methods(crow::HTTPMethod::POST)(
            [](const crow::request &req)
            {
                auto data = req.body; // Process incoming data
                return crow::response("Received: " + data + " lol");
            });

    // Start the server on a single port
    app.port(8080).multithreaded().run();

    return 0;
}
