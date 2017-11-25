/*#include <Arduino.h>
#include <SPI.h>*/
#include <U8g2lib.h>

#define MAX_X 127
#define MAX_Y 63
#define V 2

#define SMILE_MAX_Y (MAX_Y - 4)

#define buttonPin 13
#define speakerPin 4

int x, y, dy, tree_x, is_jumping;
int points;
char score[10];

static unsigned char smile[] = {0x12, 0x00, 0x21, 0x1E};
static unsigned char tree[] = {0x4, 0x4, 0xE, 0xE, 0x1F, 0x4, 0x4};
static unsigned char cloud[] = {0xc0, 0x01, 0xec, 0x03, 0xfe, 0x3b, 0xff, 0x7F};

#define tree_h sizeof(tree)
#define smile_h sizeof(smile)

/* Constructor */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup(void) {
  pinMode(buttonPin, INPUT_PULLUP);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  reset();
}

void reset(void) {
  tree_x = 127;
  dy = 0;
  x = 15;
  y = SMILE_MAX_Y;
  is_jumping = 0;
  points = 0;
  }

void loop(void) {
  u8g2.clearBuffer();
  u8g2.drawXBM(x, y, 8, 4, smile);
  u8g2.drawXBM(tree_x, MAX_Y - tree_h, 8, tree_h, tree);
  u8g2.drawXBM(int(tree_x+5)%128, 10, 16, 4, cloud);
  u8g2.drawXBM(int(tree_x*1.5+40)%128, 30, 16, 4, cloud);
  u8g2.drawXBM(int(tree_x*1.8+80)%128, 3, 16, 4, cloud);

  String(points).toCharArray(score, 10);
  u8g2.drawStr(100,20,score);
  u8g2.sendBuffer();
  if (x+8>=tree_x+3 && x<=tree_x+5 && y >= MAX_Y - smile_h) {
      u8g2.drawStr(5,40,"Game Over!");
      u8g2.sendBuffer();
      for (int i=0; i<10; i++) {
        tone(speakerPin, 1000-pow(1.25, i)*100);
        delay(50*pow(1.25, i));
      }
      noTone(speakerPin);
      reset();
    }
  y = y + dy;
  if (is_jumping) {
    dy += 1;
    tone(speakerPin, 500+y*10);
    if (y >= SMILE_MAX_Y) {
      is_jumping = 0;
      dy = 0;
      noTone(speakerPin);
      }
    } else {
      if (digitalRead(buttonPin) == LOW) {
          is_jumping = 1;
          dy = -10;
        }
      }
  tree_x -= 1;
  if (tree_x <= 0) {
    tree_x = 127;
    points = points + 1;
  }
  delay(10);
}
