#include "crow.h"
#include <crow/json.h>
#include <cstdint>
#include <fstream>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

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

void functionA()
{
    std::cout << "Function A called" << std::endl;
}

void functionB()
{
    std::cout << "Function B called" << std::endl;
}

std::vector<uint8_t> readBinaryFile(const std::string &path)
{
    std::ifstream ifs(path, std::ios::binary | std::ios::in);
    if (!ifs)
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return {};
    }
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
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

    // Route to call function A
    CROW_ROUTE(app, "/api/functionA")
        .methods(crow::HTTPMethod::POST)(
            [](const crow::request &req)
            {
                functionA();
                return crow::response("Function A called");
            });

    // Route to call function B
    CROW_ROUTE(app, "/api/functionB")
        .methods(crow::HTTPMethod::POST)(
            [](const crow::request &req)
            {
                functionB();
                return crow::response("Function B called");
            });

    // Route to request a binary file
    CROW_ROUTE(app, "/api/binary")
        .methods(crow::HTTPMethod::POST)(
            [](const crow::request &req)
            {
                std::string data_path;
                // read the path from the query json
                crow::json::rvalue json = crow::json::load(req.body);
                if (json.has("path"))
                {
                    data_path = json["path"].s();
                }
                else
                {
                    return crow::response("No path provided");
                }
                auto data = readBinaryFile(data_path);
                return crow::response(std::string(data.begin(), data.end()));
            });

    // Start the server on a single port
    app.port(8080).multithreaded().run();

    return 0;
}
