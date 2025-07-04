#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Chandu";
const char* password = "123456789";

// Use HTTPS URL
const char* serverUrl = "https://scanning-e0n6.onrender.com/api/add_product";

ESP8266WebServer server(80);

const char* trolleyId = "1";
const int quantity = 1;

void handleRoot() {
  String html = R"rawliteral(
    <html>
      <head>
        <script src="https://unpkg.com/html5-qrcode"></script>
      </head>
      <body>
        <h2>Scan Barcode via Camera</h2>
        <div id="reader" width="300px"></div>
        <script>
          function sendToESP(productId) {
            fetch("/send?barcode=" + productId).then(() => {
              alert("Scanned and sent: " + productId);
            });
          }

          function onScanSuccess(decodedText, decodedResult) {
            sendToESP(decodedText);
            html5QrcodeScanner.pause();
            setTimeout(() => {
              html5QrcodeScanner.resume();
            }, 2000);
          }

          const html5QrcodeScanner = new Html5QrcodeScanner("reader", { fps: 10, qrbox: 250 });
          html5QrcodeScanner.render(onScanSuccess);
        </script>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleSend() {
  String barcode = server.arg("barcode");
  Serial.println("Scanned Barcode: " + barcode);

  WiFiClientSecure secureClient;
  secureClient.setInsecure();  // WARNING: Insecure, but works if you're okay skipping SSL cert check

  HTTPClient http;
  http.begin(secureClient, serverUrl); // HTTPS begin
  http.addHeader("Content-Type", "application/json");

  // JSON Payload
  String payload = "{";
  payload += "\"product_id\":\"" + barcode + "\",";
  payload += "\"trolley_id\":\"" + String(trolleyId) + "\",";
  payload += "\"quantity\":\"" + String(quantity) + "\"";
  payload += "}";

  int httpCode = http.POST(payload);
  String response = http.getString();

  Serial.println("HTTP Code: " + String(httpCode));
  Serial.println("Response: " + response);

  http.end();

  server.send(200, "text/plain", "Sent: " + barcode);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");

  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.begin();

  Serial.println("Server started at IP: " + WiFi.localIP().toString());
}

void loop() {
  server.handleClient();
}
