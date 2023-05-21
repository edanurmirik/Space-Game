#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int asagi_buton = 5;
const int yukari_buton = 6;
const int sec_buton = 7;
const int atis_buton = A1;

const byte potPin = A0;
int potDeger = 0;
int x = 0;
const int buzzerPin = 4;

const int can1_led = 10;
const int can2_led = 9;
const int can3_led = 8;

const int silah1_led = 13;
const int silah2_led = 12;
const int silah3_led = 11;

String menuItems[] = { "ZORLUK 1", "ZORLUK 2" };
int currentIndex = 0;

const unsigned char rocket_bitmap[] PROGMEM = {
  0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0x18, 0x18, 0x00
};
const unsigned char meteor_bitmap[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap1[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap2[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap3[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap4[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap5[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap6[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap7[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap8[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap9[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap10[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap11[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap12[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char meteor_bitmap13[] PROGMEM = {
  0x00, 0x38, 0x7C, 0x3C, 0x3E, 0x3C, 0x00, 0x00
};
const unsigned char can_bitmap[] PROGMEM = {
  0x08, 0xD8, 0xFC, 0x7F, 0x7F, 0xFC, 0xD8, 0x08
};
const unsigned char mermi_bitmap[] PROGMEM = {
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFE, 0x00, 0x00
};

int sayac = 0;
int currentZorluk = 0;
int rastgeleSayi;
int y = 0;
int y1 = 0;
int y2 = 0;
int y3 = 0;
int y4 = 0;
int y5 = 0;
int y6 = 0;
int y7 = 0;
int y8 = 0;
int y9 = 0;
int y10 = 0;
int y11 = 0;
int y12 = 0;
int y13 = 0;
int ycan = 0;
int ymer = 0;

int mermi1y = 128;
int mermi2y = 128;
int mermi3y = 128;
int mermi1x = 0;
int mermi2x = 0;
int mermi3x = 0;
int mermihakki = 3;

int canhakki = 3;

bool mermi1v = false;
bool mermi2v = false;
bool mermi3v = false;

bool can1v = true;
bool can2v = true;
bool can3v = true;

bool gameOver = false;  // oyunun bitip bitmediği

int rastgeleSayiUret() {
  rastgeleSayi = random(0, 8);
  return rastgeleSayi;
}

int xkonum;
int xkonum1;
int xkonum2;
int xkonum3;
int xkonum4;
int xkonum5;
int xkonum6;
int xkonum7;
int xkonum8;
int xkonum9;
int xkonum10;
int xkonum11;
int xkonum12;
int xkonum13;
int canx;
int merx;

#define Num_of_Display 3
int clockPin = 1;
int dataPin = 0;
int latchPin = 2;

int skorPuani = 0;
char shiftOutBuffer[Num_of_Display] = { 0 };

byte digitValues[] = {
  0b0111111,  // 0
  0b0000110,  // 1
  0b1011011,  // 2
  0b1001111,  // 3
  0b1100110,  // 4
  0b1101101,  // 5
  0b1111101,  // 6
  0b0000111,  // 7
  0b1111111,  // 8
  0b1101111,  // 9
};

void setup() {

  Serial.begin(115200);
  display.setRotation(3);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();

  pinMode(asagi_buton, INPUT_PULLUP);
  pinMode(yukari_buton, INPUT_PULLUP);
  pinMode(sec_buton, INPUT_PULLUP);
  pinMode(atis_buton, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);

  pinMode(can1_led, OUTPUT);
  pinMode(can2_led, OUTPUT);
  pinMode(can3_led, OUTPUT);
  pinMode(silah1_led, OUTPUT);
  pinMode(silah2_led, OUTPUT);
  pinMode(silah3_led, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  displayMenu();
  currentZorluk = menuEkrani();
  randomSeed(millis());

  xkonum = rastgeleSayiUret();
  xkonum1 = rastgeleSayiUret();
  xkonum2 = rastgeleSayiUret();
  xkonum3 = rastgeleSayiUret();
  xkonum4 = rastgeleSayiUret();
  xkonum5 = rastgeleSayiUret();
  xkonum6 = rastgeleSayiUret();
  xkonum7 = rastgeleSayiUret();
  xkonum8 = rastgeleSayiUret();
  xkonum9 = rastgeleSayiUret();
  xkonum10 = rastgeleSayiUret();
  xkonum11 = rastgeleSayiUret();
  xkonum12 = rastgeleSayiUret();
  xkonum13 = rastgeleSayiUret();
  canx = rastgeleSayiUret();
  merx = rastgeleSayiUret();

  digitalWrite(can1_led, HIGH);
  digitalWrite(can2_led, HIGH);
  digitalWrite(can3_led, HIGH);
  digitalWrite(silah1_led, HIGH);
  digitalWrite(silah2_led, HIGH);
  digitalWrite(silah3_led, HIGH);

  display.display();
}

void loop() {

  display.clearDisplay();

  if (!gameOver) {

    skorPuani++;
    skorPuaniYazdir(skorPuani);

    potDeger = analogRead(potPin);
    potDeger = potDeger >> 2;
    x = map(potDeger, 0, 255, 0, 80);

    if (x == 7 || x == 23) {
      x++;
    }
    if (x >= 56) {
      display.drawBitmap(56, 120, rocket_bitmap, 8, 8, WHITE);
    } else {
      display.drawBitmap(x, 120, rocket_bitmap, 8, 8, WHITE);  // Resmi çiz
    }

    display.drawBitmap(xkonum * 8, y * 8, meteor_bitmap, 8, 8, WHITE);
    y++;

    if (y > 3) {
      display.drawBitmap(xkonum1 * 8, y1 * 8, meteor_bitmap1, 8, 8, WHITE);
      y1++;
    }
    if (y1 > 3) {
      display.drawBitmap(xkonum2 * 8, y2 * 8, meteor_bitmap2, 8, 8, WHITE);
      y2++;
    }
    if (y2 > 3) {
      display.drawBitmap(xkonum3 * 8, y3 * 8, meteor_bitmap3, 8, 8, WHITE);
      y3++;
    }
    if (y3 > 3) {
      display.drawBitmap(xkonum4 * 8, y4 * 8, meteor_bitmap4, 8, 8, WHITE);
      y4++;
    }
    if (y4 > 3) {
      display.drawBitmap(xkonum5 * 8, y5 * 8, meteor_bitmap5, 8, 8, WHITE);
      y5++;
    }
    if (y5 > 3) {
      display.drawBitmap(xkonum6 * 8, y6 * 8, meteor_bitmap6, 8, 8, WHITE);
      y6++;
    }
    if (y6 > 3) {
      display.drawBitmap(xkonum7 * 8, y7 * 8, meteor_bitmap7, 8, 8, WHITE);
      y7++;
    }
    if (y7 > 3) {
      display.drawBitmap(xkonum8 * 8, y8 * 8, meteor_bitmap8, 8, 8, WHITE);
      y8++;
    }
    if (y8 > 3) {
      display.drawBitmap(xkonum9 * 8, y9 * 8, meteor_bitmap9, 8, 8, WHITE);
      y9++;
    }
    if (y9 > 3) {
      display.drawBitmap(xkonum10 * 8, y10 * 8, meteor_bitmap10, 8, 8, WHITE);
      y10++;
    }
    if (y10 > 3) {
      display.drawBitmap(xkonum11 * 8, y11 * 8, meteor_bitmap11, 8, 8, WHITE);
      y11++;
    }
    if (y11 > 3) {
      display.drawBitmap(xkonum12 * 8, y12 * 8, meteor_bitmap12, 8, 8, WHITE);
      y12++;
    }
    if (y12 > 3) {
      display.drawBitmap(xkonum13 * 8, y13 * 8, meteor_bitmap13, 8, 8, WHITE);
      y13++;
    }
    if (y13 > 3) {
      display.drawBitmap(canx * 8, ycan * 8, can_bitmap, 8, 8, WHITE);
      ycan++;
    }
    if (ycan > 3) {
      display.drawBitmap(merx * 8, ymer * 8, mermi_bitmap, 8, 8, WHITE);
      ymer++;
    }

    if (ymer > 16) {
      ymer = 0;
      ycan = 0;
      y13 = 0;
      y12 = 0;
      y11 = 0;
      y10 = 0;
      y9 = 0;
      y8 = 0;
      y7 = 0;
      y6 = 0;
      y5 = 0;
      y4 = 0;
      y3 = 0;
      y2 = 0;
      y1 = 0;
      y = 0;
    }

    //MERMİ HAKKI KULLANILDIĞINDA YAPILAN İŞLEMLER
    if (digitalRead(atis_buton) == LOW && mermihakki == 3) {
      mermi1v = true;
      mermi1x = x;
      mermihakki--;
      delay(300);
    }
    if (digitalRead(atis_buton) == LOW && mermihakki == 2) {
      mermi2v = true;
      mermihakki--;
      mermi2x = x;
      delay(300);
    }
    if (digitalRead(atis_buton) == LOW && mermihakki == 1) {
      mermi3v = true;
      mermihakki--;
      mermi3x = x;
      delay(300);
    }

    // MERMİ KULLANILDIĞINDA YAPILAN İŞLEMLER
    if (mermi1v == true) {
      display.drawBitmap(mermi1x, mermi1y - 8, mermi_bitmap, 8, 8, WHITE);
      mermi1y = mermi1y - 8;
      digitalWrite(silah3_led, LOW);
    }

    if (mermi2v == true) {
      display.drawBitmap(mermi2x, mermi2y, mermi_bitmap, 8, 8, WHITE);
      mermi2y = mermi2y - 8;
      digitalWrite(silah2_led, LOW);
    }

    if (mermi3v == true) {
      display.drawBitmap(mermi3x, mermi3y, mermi_bitmap, 8, 8, WHITE);
      mermi3y = mermi3y - 8;
      digitalWrite(silah1_led, LOW);
    }


    // MERMİ 1 İLE METEOR ÇARPIŞTIĞINDA YAPILAN İŞLEMLER
    if (mermi1x / 8 == xkonum && (mermi1y / 8) + 1 <= y) {
      //display.print("Degdi");
      y = 17;
    }
    if (mermi1x / 8 == xkonum1 && (mermi1y / 8) + 1 <= y1) {
      //display.print("Degdi");
      y1 = 17;
    }
    if (mermi1x / 8 == xkonum2 && (mermi1y / 8) + 1 <= y2) {
      //display.print("Degdi");
      y2 = 17;
    }
    if (mermi1x / 8 == xkonum3 && (mermi1y / 8) + 1 <= y3) {
      //display.print("Degdi");
      y3 = 17;
    }
    if (mermi1x / 8 == xkonum4 && (mermi1y / 8) + 1 <= y4) {
      //display.print("Degdi");
      y4 = 17;
    }
    if (mermi1x / 8 == xkonum5 && (mermi1y / 8) + 1 <= y5) {
      //display.print("Degdi");
      y5 = 17;
    }
    if (mermi1x / 8 == xkonum6 && (mermi1y / 8) + 1 <= y6) {
      //display.print("Degdi");
      y6 = 17;
    }
    if (mermi1x / 8 == xkonum7 && (mermi1y / 8) + 1 <= y7) {
      //display.print("Degdi");
      y7 = 17;
    }
    if (mermi1x / 8 == xkonum8 && (mermi1y / 8) + 1 <= y8) {
      //display.print("Degdi");
      y8 = 17;
    }
    if (mermi1x / 8 == xkonum9 && (mermi1y / 8) + 1 <= y9) {
      //display.print("Degdi");
      y9 = 17;
    }
    if (mermi1x / 8 == xkonum10 && (mermi1y / 8) + 1 <= y10) {
      //display.print("Degdi");
      y10 = 17;
    }
    if (mermi1x / 8 == xkonum11 && (mermi1y / 8) + 1 <= y11) {
      //display.print("Degdi");
      y11 = 17;
    }
    if (mermi1x / 8 == xkonum12 && (mermi1y / 8) + 1 <= y12) {
      //display.print("Degdi");
      y12 = 17;
    }
    if (mermi1x / 8 == xkonum13 && (mermi1y / 8) + 1 <= y13) {
      //display.print("Degdi");
      y13 = 17;
    }


    // MERMİ 2 İLE METEOR ÇARPIŞTIĞINDA YAPPILAN İŞLEMLER
    if (mermi2x / 8 == xkonum && (mermi2y / 8) + 1 <= y) {
      //display.print("Degdi");
      y = 17;
    }
    if (mermi2x / 8 == xkonum1 && (mermi2y / 8) + 1 <= y1) {
      //display.print("Degdi");
      y1 = 17;
    }
    if (mermi2x / 8 == xkonum2 && (mermi2y / 8) + 1 <= y2) {
      //display.print("Degdi");
      y2 = 17;
    }
    if (mermi2x / 8 == xkonum3 && (mermi2y / 8) + 1 <= y3) {
      //display.print("Degdi");
      y3 = 17;
    }
    if (mermi2x / 8 == xkonum4 && (mermi2y / 8) + 1 <= y4) {
      //display.print("Degdi");
      y4 = 17;
    }
    if (mermi2x / 8 == xkonum5 && (mermi2y / 8) + 1 <= y5) {
      //display.print("Degdi");
      y5 = 17;
    }
    if (mermi2x / 8 == xkonum6 && (mermi2y / 8) + 1 <= y6) {
      //display.print("Degdi");
      y6 = 17;
    }
    if (mermi2x / 8 == xkonum7 && (mermi2y / 8) + 1 <= y7) {
      //display.print("Degdi");
      y7 = 17;
    }
    if (mermi2x / 8 == xkonum8 && (mermi2y / 8) + 1 <= y8) {
      //display.print("Degdi");
      y8 = 17;
    }
    if (mermi2x / 8 == xkonum9 && (mermi2y / 8) + 1 <= y9) {
      //display.print("Degdi");
      y9 = 17;
    }
    if (mermi2x / 8 == xkonum10 && (mermi2y / 8) + 1 <= y10) {
      //display.print("Degdi");
      y10 = 17;
    }
    if (mermi2x / 8 == xkonum11 && (mermi2y / 8) + 1 <= y11) {
      //display.print("Degdi");
      y11 = 17;
    }
    if (mermi2x / 8 == xkonum12 && (mermi2y / 8) + 1 <= y12) {
      //display.print("Degdi");
      y12 = 17;
    }
    if (mermi2x / 8 == xkonum13 && (mermi2y / 8) + 1 <= y13) {
      //display.print("Degdi");
      y13 = 17;
    }

    // MERMİ 3 İLE METEOR ÇARPIŞTIĞINDA YAPPILAN İŞLEMLER
    if (mermi3x / 8 == xkonum && (mermi3y / 8) + 1 <= y) {
      //display.print("Degdi");
      y = 17;
    }
    if (mermi3x / 8 == xkonum1 && (mermi3y / 8) + 1 <= y1) {
      //display.print("Degdi");
      y1 = 17;
    }
    if (mermi3x / 8 == xkonum2 && (mermi3y / 8) + 1 <= y2) {
      //display.print("Degdi");
      y2 = 17;
    }
    if (mermi3x / 8 == xkonum3 && (mermi3y / 8) + 1 <= y3) {
      //display.print("Degdi");
      y3 = 17;
    }
    if (mermi3x / 8 == xkonum4 && (mermi3y / 8) + 1 <= y4) {
      //display.print("Degdi");
      y4 = 17;
    }
    if (mermi3x / 8 == xkonum5 && (mermi3y / 8) + 1 <= y5) {
      //display.print("Degdi");
      y5 = 17;
    }
    if (mermi3x / 8 == xkonum6 && (mermi3y / 8) + 1 <= y6) {
      //display.print("Degdi");
      y6 = 17;
    }
    if (mermi3x / 8 == xkonum7 && (mermi3y / 8) + 1 <= y7) {
      //display.print("Degdi");
      y7 = 17;
    }
    if (mermi3x / 8 == xkonum8 && (mermi3y / 8) + 1 <= y8) {
      //display.print("Degdi");
      y8 = 17;
    }
    if (mermi3x / 8 == xkonum9 && (mermi3y / 8) + 1 <= y9) {
      //display.print("Degdi");
      y9 = 17;
    }
    if (mermi3x / 8 == xkonum10 && (mermi3y / 8) + 1 <= y10) {
      //display.print("Degdi");
      y10 = 17;
      mermi3v = false;
    }
    if (mermi3x / 8 == xkonum11 && (mermi3y / 8) + 1 <= y11) {
      //display.print("Degdi");
      y11 = 17;
    }
    if (mermi3x / 8 == xkonum12 && (mermi3y / 8) + 1 <= y12) {
      //display.print("Degdi");
      y12 = 17;
    }
    if (mermi3x / 8 == xkonum13 && (mermi3y / 8) + 1 <= y13) {
      //display.print("Degdi");
      y13 = 17;
    }

    // METEOR İLE UZAY GEMİSİ ÇARPIŞTIĞINDA BUZZER ÖTER
    if (x == xkonum * 8 && y * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum1 * 8 && y1 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum2 * 8 && y2 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum3 * 8 && y3 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum4 * 8 && y4 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum5 * 8 && y5 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum6 * 8 && y6 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum7 * 8 && y7 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum8 * 8 && y8 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum9 * 8 && y9 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum10 * 8 && y10 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum11 * 8 && y11 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum12 * 8 && y12 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }
    if (x == xkonum13 * 8 && y13 * 8 == 128) {
      canhakki--;
      tone(buzzerPin, 1000);
      delay(1000);
      noTone(buzzerPin);
    }

    if ((x / 8) == canx && ycan * 8 == 128) {
      canhakki++;
    }
    if ((x / 8) == merx && ymer * 8 == 128) {
      mermihakki++;
      mermi1y = 128;
      mermi2y = 128;
      mermi3y = 128;
      if (mermihakki == 1) {
        mermi1v = false;
      }
      if (mermihakki == 2) {
        mermi1v = false;
        mermi2v = false;
      }
      if (mermihakki == 3) {
        mermi1v = false;
        mermi2v = false;
        mermi3v = false;
      }
    }
    if (mermihakki == 3) {
      digitalWrite(silah3_led, HIGH);
      digitalWrite(silah2_led, HIGH);
      digitalWrite(silah1_led, HIGH);
    }
    if (mermihakki == 2) {
      digitalWrite(silah1_led, HIGH);
      digitalWrite(silah2_led, HIGH);
      digitalWrite(silah3_led, LOW);
    }
    if (mermihakki == 1) {
      digitalWrite(silah1_led, HIGH);
      digitalWrite(silah2_led, LOW);
      digitalWrite(silah3_led, LOW);
    }

    if (canhakki == 3) {
      digitalWrite(can3_led, HIGH);
      digitalWrite(can2_led, HIGH);
      digitalWrite(can1_led, HIGH);
    }
    if (canhakki == 2) {
      digitalWrite(can1_led, HIGH);
      digitalWrite(can2_led, HIGH);
      digitalWrite(can3_led, LOW);
    }
    if (canhakki == 1) {
      digitalWrite(can1_led, HIGH);
      digitalWrite(can2_led, LOW);
      digitalWrite(can3_led, LOW);
    }
    if (canhakki == 0) {
      digitalWrite(can3_led, LOW);
      digitalWrite(can2_led, LOW);
      digitalWrite(can1_led, LOW);

      gameOver = true;
    }

    /*display.setCursor(20, 20);
    display.println(x);
    display.setCursor(20, 40);
    display.println(canx);*/
    //delay(300);

  } else {
    // oyun bitti, sonuç ekranını göster
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.println("GAME OVER");
    display.setTextSize(1);
    display.setCursor(0, 60);
    display.print("Skor: ");
    display.println(skorPuani);
  }
  display.display();
}

void skorPuaniYazdir(int skorPuani) {

  shiftOutBuffer[0] = skorPuani % 100 % 10;
  shiftOutBuffer[1] = skorPuani / 10 % 10;
  shiftOutBuffer[2] = skorPuani / 100;

  digitalWrite(latchPin, LOW);
  for (int i = Num_of_Display - 1; i > -1; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, digitValues[shiftOutBuffer[i]]);
    digitalWrite(latchPin, HIGH);
  }
}

void displayMenu() {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("MENU");

  for (int i = 0; i < 2; i++) {
    display.setCursor(0, 10 + i * 10);
    if (i == currentIndex) {
      display.print(">");
    }
    display.println(menuItems[i]);
  }

  display.display();
}

int menuEkrani() {

  while (sayac == 0) {
    if (digitalRead(asagi_buton) == LOW) {
      currentIndex--;
      if (currentIndex < 0) {
        currentIndex = 1;
      }
      displayMenu();
      delay(250);
    }
    if (digitalRead(yukari_buton) == LOW) {
      currentIndex++;
      if (currentIndex > 1) {
        currentIndex = 0;
      }
      displayMenu();
      delay(250);
    }
    if (digitalRead(sec_buton) == LOW) {
      sayac = 1;
    }
  }

  display.clearDisplay();
  return currentIndex;
}