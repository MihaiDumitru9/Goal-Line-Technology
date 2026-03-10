#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include <TM1637Display.h>

#define TM1637_CLK 14  // GPIO14
#define TM1637_DIO 12  // GPIO12

TM1637Display display(TM1637_CLK, TM1637_DIO);

const char* WIFI_SSID = "SALA ASPC";
const char* WIFI_PASS = "ASPC2022";

WebServer server(80);

// Resolutions
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600);

// Character map for TM1637 (custom letters)
uint8_t encodeLetter(char c) {
  switch (c) {
    case 'G': return 0b00000111;
    case 'O': return 0b01111110;
    case 'A': return 0b00111111;
    case 'L': return 0b01101111;
    default: return 0;
  }
}

// Display a string like "GOAL" on TM1637
void showString(const char* str) {
  uint8_t data[4] = {0};
  for (int i = 0; i < 4 && str[i]; i++) {
    data[i] = encodeLetter(toupper(str[i]));
  } 
  display.setSegments(data);
}

// Show JPEG from camera
void serveJpg() {
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}

// Camera resolution endpoints
void handleJpgLo() {
  if (!esp32cam::Camera.changeResolution(loRes)) Serial.println("SET-LO-RES FAIL");
  serveJpg();
}
void handleJpgMid() {
  if (!esp32cam::Camera.changeResolution(midRes)) Serial.println("SET-MID-RES FAIL");
  serveJpg();
}
void handleJpgHi() {
  if (!esp32cam::Camera.changeResolution(hiRes)) Serial.println("SET-HI-RES FAIL");
  serveJpg();
}

// Handle /goal
void handleGoal() {
  Serial.println("GOAL triggered");
  showString("GOAL");
  server.send(200, "text/plain", "GOAL displayed");
}

// Handle /clear
void handleClear() {
  Serial.println("CLEAR triggered");
  display.clear();
  server.send(200, "text/plain", "Display cleared");
}

void setup() {
  Serial.begin(115200);
  display.setBrightness(0x0f);
  display.clear();
  delay(100);
  showString("----");

  // Camera setup
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }

  // WiFi
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.print("\nESP32-CAM ready: http://");
  Serial.println(WiFi.localIP());

  // Web endpoints
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam-mid.jpg", handleJpgMid);
  server.on("/goal", handleGoal);
  server.on("/clear", handleClear);  // <--- Added
  server.begin();
}

void loop() {
  server.handleClient();
}
