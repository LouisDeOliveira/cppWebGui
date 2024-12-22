console.log('Hello, world!');

function sendMessage() {
    fetch("/api/click", { method: "POST" , headers: { 'Content-Type': 'application/json' }, body: JSON.stringify({ message: "Hello, world!" }) })
        .then((res) => res.text())
        .then((data) => {
            document.getElementById("response").innerText = data;
        });
}