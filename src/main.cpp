// /******************************************************************************
//  * main.cpp
//  * C plus plus function for the main file
//  *****************************************************************************/

#include "Arduino.h"
#include "main.h"


AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);

  Serial.print("WIFI init");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Make it possible to access webserver at http://myEsp32.local
  if (!MDNS.begin(hostname)) {
    Serial.println("Error setting up mDNS responder!");
  } else {
    Serial.printf("Access at http://%s.local\n", hostname);
  }

  // Show a link to OTA page at http://myEsp32.local
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<html><body>";
    html += "<a href=\"/ota\">Update Software</a>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  AsyncOTA.begin(&server);
  server.begin();
}

void loop(){
    delay(1000);
}