
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL3btBFOckZ"
#define BLYNK_TEMPLATE_NAME "Classroom Automation"

// Add your Blynk token locally before uploading to your NodeMCU
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials — keep private
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// Relay pins
#define LOAD1 D3
#define LOAD2 D4
#define LOAD3 D5
#define LOAD4 D6

// Active-low relay module
#define RELAY_ON LOW
#define RELAY_OFF HIGH

// Load 1 — Blynk V1
BLYNK_WRITE(V1)
{
  digitalWrite(LOAD1, param.asInt() ? RELAY_ON : RELAY_OFF);
  Serial.println(param.asInt() ? "LOAD 1 ON" : "LOAD 1 OFF");
}

// Load 2 — Blynk V2
BLYNK_WRITE(V2)
{
  digitalWrite(LOAD2, param.asInt() ? RELAY_ON : RELAY_OFF);
  Serial.println(param.asInt() ? "LOAD 2 ON" : "LOAD 2 OFF");
}

// Load 3 — Blynk V3
BLYNK_WRITE(V3)
{
  digitalWrite(LOAD3, param.asInt() ? RELAY_ON : RELAY_OFF);
  Serial.println(param.asInt() ? "LOAD 3 ON" : "LOAD 3 OFF");
}

// Load 4 — Blynk V4
BLYNK_WRITE(V4)
{
  digitalWrite(LOAD4, param.asInt() ? RELAY_ON : RELAY_OFF);
  Serial.println(param.asInt() ? "LOAD 4 ON" : "LOAD 4 OFF");
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("    CLASSROOM AUTOMATION");
  Serial.println("================================");

  // Configure relay pins and switch all loads OFF
  pinMode(LOAD1, OUTPUT);
  pinMode(LOAD2, OUTPUT);
  pinMode(LOAD3, OUTPUT);
  pinMode(LOAD4, OUTPUT);

  digitalWrite(LOAD1, RELAY_OFF);
  digitalWrite(LOAD2, RELAY_OFF);
  digitalWrite(LOAD3, RELAY_OFF);
  digitalWrite(LOAD4, RELAY_OFF);

  Serial.println("All loads OFF");

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to Wi-Fi");

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 30)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  Serial.println();

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wi-Fi connection failed!");
    return;
  }

  Serial.println("Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");

  Blynk.config(BLYNK_AUTH_TOKEN);

  if (Blynk.connect(10000))
  {
    Serial.println("Blynk connected!");
    Serial.println("Device online!");
  }
  else
  {
    Serial.println("Blynk connection failed!");
  }
}

void loop()
{
  // Maintain Blynk connection
  Blynk.run();

  // Reconnect Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    delay(1000);
  }

  // Reconnect Blynk if disconnected
  if (WiFi.status() == WL_CONNECTED && !Blynk.connected())
  {
    Serial.println("Blynk disconnected. Reconnecting...");
    Blynk.connect(5000);
  }
}
