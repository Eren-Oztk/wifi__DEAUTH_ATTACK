<div align="center">

# 📡 WiFi Deauth Attack

**`ESP32 Tabanlı Ağ Test Aracı · Deneyap Kart · Eğitim Amaçlı`**

<br>

[![Live Demo](https://img.shields.io/badge/🌐_Canlı_Demo-GitHub_Pages-1f6feb?style=for-the-badge)](https://eren-oztk.github.io/WiFi_DEAUTH_ATTACK)
[![Language](https://img.shields.io/badge/C++-100%25-00599C?style=for-the-badge&logo=cplusplus)](https://github.com/Eren-Oztk/WiFi_DEAUTH_ATTACK)
[![Platform](https://img.shields.io/badge/ESP32--S3-Deneyap_Kart-red?style=for-the-badge)](https://github.com/Eren-Oztk/WiFi_DEAUTH_ATTACK)

</div>

---

> **⚠️ EĞİTİM AMAÇLIDIR — YASAL UYARI**
>
> Bu proje **yalnızca eğitim, araştırma ve kendi sahip olduğunuz ağlarda güvenlik testi** amacıyla hazırlanmıştır.
> İzin verilmemiş ağlara karşı bu tür araçların kullanılması **yasadışıdır** ve ciddi hukuki sonuçlar doğurabilir.
> Proje sahibi, bu kodun kötüye kullanılmasından doğan hiçbir zarardan sorumlu tutulamaz.
>
> **This project is for EDUCATIONAL PURPOSES ONLY. Use only on networks you own or have explicit permission to test.**

---

## Proje Hakkında

NodeMCU (ESP8266) tabanlı, OLED ekranlı, potansiyometre ve buton kontrollü taşınabilir bir WiFi ağ analiz ve stres test cihazı. Çevredeki WiFi ağlarını tarar, OLED ekranda listeler ve seçilen ağ üzerinde 802.11 deauthentication paketi tabanlı bağlantı dayanıklılığı testleri yapılmasına olanak tanır.

Proje aynı zamanda `ag-test-cihazi-simulasyon.html` adlı bir **tarayıcı simülatörü** içermekte olup donanım olmadan arayüzü ve akışı test etmenizi sağlar.

---

## Özellikler

- Çevredeki tüm WiFi ağlarını tarar (en fazla 20)
- Ağ adı (SSID) ve sinyal gücü (RSSI) bilgisini 128x64 OLED ekranda gösterir
- Potansiyometre ile ağ seçimi
- Donanım kesmesi (interrupt) kullanan anlık buton kontrolü (debounce dahil)
- Tarayıcı tabanlı simülatör (HTML/JS)

---

## Donanım Listesi

| Bileşen | Adet |
|---|---|
| NodeMCU ESP8266 (v2/v3) | 1 |
| SSD1306 OLED 128x64 (I2C) | 1 |
| 10kΩ Potansiyometre | 1 |
| Push-button (anlık buton) | 1 |
| 10kΩ direnç (pull-down, isteğe bağlı) | 1 |
| Breadboard + jumper kablo | — |

---

## Devre Şeması (Pin Bağlantıları)

```
NodeMCU ESP8266
┌─────────────────────────────────┐
│                                 │
│  3.3V ──────────────────┐       │
│  GND  ──────────────┐   │       │
│                     │   │       │
│         SSD1306 OLED (I2C)      │
│  D1 (GPIO5) ─── SCL │   │       │
│  D2 (GPIO4) ─── SDA │   │       │
│  3.3V ──────── VCC ─┘   │       │
│  GND  ──────── GND ─────┘       │
│                                 │
│         Potansiyometre          │
│  A0   ──────── ORTA PIN         │
│  3.3V ──────── SOL  PIN         │
│  GND  ──────── SAĞ  PIN         │
│                                 │
│         Push-Button             │
│  D8 (GPIO15) ── PIN 1           │
│  GND  ──────── PIN 2            │
│  (INPUT_PULLUP aktif,           │
│   harici direnç gerekmez)       │
└─────────────────────────────────┘
```

> **Not:** SSD1306 I2C adresi `0x3D` olarak ayarlanmıştır. Bazı modüllerde `0x3C` olabilir; uyumsuzluk durumunda `SCREEN_ADDRESS` sabitini güncelleyin.

---

## Kurulum

### 1. Arduino IDE Kütüphaneleri

Arduino IDE → Library Manager üzerinden şunları yükleyin:

- `Adafruit SSD1306`
- `Adafruit GFX Library`
- `ESP8266WiFi` (NodeMCU kartı için otomatik gelir)

### 2. Kart Ayarı

Arduino IDE → Tools → Board: **NodeMCU 1.0 (ESP-12E Module)**

### 3. Kodu Yükleyin

`wifi__DEAUTH_ATTACK.ino` dosyasını açın ve kartınıza yükleyin.

---

## Simülatör

Donanım olmadan projeyi test etmek için `ag-test-cihazi-simulasyon.html` dosyasını herhangi bir tarayıcıda açın.

---

## GitHub Repository Ayarları

**Önerilen Description:**
```
ESP8266 tabanlı taşınabilir WiFi ağ tarama ve güvenlik test cihazı — Eğitim Amaçlıdır
```

**Önerilen Topics:**
```
esp8266  nodemcu  arduino  wifi-security  deauth  oled-display  cybersecurity  education  iot  hardware
```

---

## Lisans

MIT License — Yalnızca eğitim ve kişisel araştırma amaçlı kullanım.
