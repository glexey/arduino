#include <U8g2lib.h>

#define buttonPin 13
#define speakerPin 4

static const char* const values[] = {"Red", "Black"};

char s[10];

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  u8g2.begin();
  u8g2.setFont(u8g2_font_fub30_tr);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) return;
  u8g2.clearBuffer();
  u8g2.drawStr(50, 40, "...");
  u8g2.sendBuffer();
  int n, m;
  unsigned int j = 0;
  while (digitalRead(buttonPin) == LOW) {
    n = random(1, 10);
    if (++j%100==0) tone(speakerPin, 1000+random(8000));
    }
  noTone(speakerPin);
  u8g2.clearBuffer();
  sprintf(s, "%d", n);
  u8g2.drawStr(50, 32, s);
  u8g2.drawStr(25-20*(n%2), 64, values[n%2]);
  u8g2.sendBuffer();
}
