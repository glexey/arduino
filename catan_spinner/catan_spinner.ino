#include <U8g2lib.h>

#define buttonPin 13

static const char* const values[] = {"Brigand", "Trade", "Harvest", "Celebration", "?", "?" };

char s[10];
int n, m;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  u8g2.begin();
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) return;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB18_tr);
  u8g2.drawStr(50, 40, "...");
  u8g2.sendBuffer();
  while (digitalRead(buttonPin) == LOW) {
    n = random(1, 6);
    m = random(0, 5);
    }
  u8g2.clearBuffer();
  sprintf(s, "%d", n);
  u8g2.drawStr(50, 30, s);
  sprintf(s, "%s", values[m]);
  u8g2.setFont(u8g2_font_ncenB12_tr);
  u8g2.drawStr(5, 60, s);

  u8g2.sendBuffer();
}
