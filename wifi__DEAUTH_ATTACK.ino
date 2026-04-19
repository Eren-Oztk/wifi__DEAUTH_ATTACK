#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3D
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN D8 // GPIO 15, D8 pinine bağlanacak
#define POT_PIN A0

int selectedNetwork = 0;
int totalNetworks = 0;
String ssidList[20];
int ssidRSSI[20];

bool attack = false;
unsigned long lastPressTime = 0; // Butonun son basılma zamanını saklamak için

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleAttack, FALLING);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  scanNetworks();
}

void toggleAttack() {
  unsigned long currentTime = millis();
  if (currentTime - lastPressTime > 500) { // Debouncing için 500ms gecikme
    attack = !attack;
    if (attack) {
      Serial.print("Starting attack on ");
      Serial.println(ssidList[selectedNetwork]);
    } else {
      Serial.println("Attack stopped");
    }
    lastPressTime = currentTime;
  }
}

void scanNetworks() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Scanning...");
  display.display();

  int n = WiFi.scanNetworks();
  if (n == 0) {
    display.setCursor(0, 10);
    display.print("No networks found");
  } else {
    totalNetworks = n > 20 ? 20 : n;
    for (int i = 0; i < totalNetworks; ++i) {
      ssidList[i] = WiFi.SSID(i);
      ssidRSSI[i] = WiFi.RSSI(i); // RSSI değerini de saklıyoruz
    }
  }
  displayNetworks();
}

void displayNetworks() {
  display.clearDisplay();
  for (int i = 0; i < totalNetworks; i++) {
    if (i == selectedNetwork) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
    display.setCursor(0, i * 10);
    display.print(ssidList[i]);
    display.print(" (");
    display.print(ssidRSSI[i]);
    display.println(")");
  }
  display.display();
}

void sendDeauth() {
  // Bu işlev, ESP32'nin WiFi kütüphanesindeki düşük seviyeli paket gönderme işlevselliği için kullanılabilir.
  // Bu fonksiyon şu an boş bırakılmıştır çünkü doğrudan deauth paketi gönderme işlevi yoktur.
  // Buraya ESP32'nin WiFi kitaplığı ile uyumlu bir paket gönderme işlevi eklenmelidir.
  // Bu örnek sadece gösterim amaçlıdır ve tam fonksiyonellik sağlamayabilir.
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int newSelectedNetwork = map(potValue, 0, 1023, 0, totalNetworks - 1);
  if (newSelectedNetwork != selectedNetwork) {
    selectedNetwork = newSelectedNetwork;
    displayNetworks();
  }

  if (attack) {
    sendDeauth();
  }
  delay(500);
}
