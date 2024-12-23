console.log("Hello, world!");

var count = 0;

function sendMessage() {
    count++;
    fetch("/api/click", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ message: "Hello, world!, count = " + count }),
    })
        .then((res) => res.text())
        .then((data) => {
            document.getElementById("response").innerText = data;
        });
}

function callFunctionA() {
    fetch("/api/functionA", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ message: "Hello, world" }),
    })
        .then((res) => res.text())
        .then((data) => {
            document.getElementById("response").innerText = data;
        });
}

function callFunctionB() {
    fetch("/api/functionB", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ message: "Hello, world" }),
    })
        .then((res) => res.text())
        .then((data) => {
            document.getElementById("response").innerText = data;
        });
}

function requestData() {
    fetch("/api/binary", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ path: "../assets/gromit.jpg" }),
    })
        .then((res) => res.blob())
        .then((data) => {
            var img = document.createElement("img");
            img.src = URL.createObjectURL(data);
            document.getElementById("response").appendChild(img);
        });
}
