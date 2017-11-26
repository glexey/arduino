#include <U8g2lib.h>

#define buttonPin 13
#define changeGamePin 12
#define speakerPin 4

struct Game {
  const char* gname;
  int num_max;
  int num_str;
  const char* const* str_table;
  };

const char* const life_strs[] = {"Red", "Black"};
const char* const catan_strs[] = {"Brigand", "Trade", "Harvest", "Celebration", "?", "?"};

Game games[] = {
  {"Life", 10, 2, life_strs},
  {"Catan", 6, 6, catan_strs},
};

const uint8_t* fonts[] = {
  u8g2_font_fub30_tr,
  u8g2_font_fub20_tr,
  u8g2_font_crox5tb_tr,
  };

#define num_games 2
#define num_fonts 3

static const char* const values[] = {"Red", "Black"};

char s[10];
char ngame = 0;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void showname() {
    Game game = games[ngame];
    u8g2.clearBuffer();
    u8g2.setFont(fonts[0]);
    u8g2.drawStr(64-u8g2.getStrWidth(game.gname)/2, 40, game.gname);
    u8g2.sendBuffer();
  }

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(changeGamePin, INPUT_PULLUP);
  u8g2.begin();
  showname();
}

void loop() {
  if (digitalRead(changeGamePin) == LOW) {
    ngame = ++ngame % num_games;
    showname();
    while(digitalRead(changeGamePin) == LOW) delay(50);
    }
  if (digitalRead(buttonPin) == HIGH) return;
  u8g2.clearBuffer();
  u8g2.setFont(fonts[0]);
  u8g2.drawStr(50, 40, "...");
  u8g2.sendBuffer();
  int n;
  unsigned int j = 0;
  Game game = games[ngame];
  while (digitalRead(buttonPin) == LOW) {
    n = 1 + random(game.num_max);
    if (++j%100==0) tone(speakerPin, 1000+random(8000));
    }
  noTone(speakerPin);
  u8g2.clearBuffer();
  sprintf(s, "%d", n);
  u8g2.drawStr(50, 32, s);
  int m = random(game.num_str);
  int ifont = -1;
  do {
    ifont++;
    u8g2.setFont(fonts[ifont]);
  } while (u8g2.getStrWidth(game.str_table[m]) > 128 && ifont < num_fonts-1);
  u8g2.drawStr(64-u8g2.getStrWidth(game.str_table[m])/2, 64, game.str_table[m]);
  u8g2.sendBuffer();
}
