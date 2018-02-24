#define REDLED 2
#define GREENLED 4
#define BLUELED 3

void setup() {
  // put your setup code here, to run once:
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
}

void blink(int pin) {
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
  }

void loop() {
  // put your main code here, to run repeatedly:
  blink(REDLED);
  blink(GREENLED);
  blink(BLUELED);
  delay(1000);
}
