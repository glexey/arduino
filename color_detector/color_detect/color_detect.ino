#include <Wire.h>

// Illumination LEDs connected to these digital output pins:
#define REDLED 2
#define GREENLED 4
#define BLUELED 3

// Time for LED output to stabilize and for the color sensor
// to perform 2 measurements
#define MEASUREMENT_TIME 400

// Calibration values: BLACK and WHITE level
#define R_BLACK 59
#define G_BLACK 90
#define B_BLACK 37
//
#define R_WHITE 560
#define G_WHITE 900
#define B_WHITE 350

int BH1750_address = 0x23; // i2c address of light sensor 

byte buff[2]; // buffer for capturing sensor output

void setup(){
    // Set up i2c interface, the sensor, and the serial port
    Wire.begin();
    BH1750_Init(BH1750_address);
    delay(200);
    Serial.begin(9600);
}

int sense_one_color(int pin) {
    // Turn the LED ON
    digitalWrite(pin, HIGH);
    // Wait for output to stabilize and give sensor time to measure
    delay(MEASUREMENT_TIME);
    // Read the output of the sensor
    int value = 0;
    if(BH1750_Read(BH1750_address)==2){
        value = (buff[0]<<8) | buff[1];
    }
    // Turn the LED OFF
    digitalWrite(pin, LOW);
    return value;
}


void loop(){
    // Perform the measurement cycle
    int r = sense_one_color(REDLED);
    int g = sense_one_color(GREENLED);
    int b = sense_one_color(BLUELED);
    
    // Write raw readings to serial port (for calibration)
    Serial.print(r,DEC); Serial.print(" "); 
    Serial.print(g,DEC); Serial.print(" "); 
    Serial.print(b,DEC); Serial.print(" "); 

    // Scale the readings so that BLACK becomes (0, 0, 0)
    // and WHITE becomes (1.0, 1.0, 1.0)
    float rf = min(1.0, max(0.0, 1.0 * (r - R_BLACK) / (R_WHITE - R_BLACK)));
    float gf = min(1.0, max(0.0, 1.0 * (g - G_BLACK) / (G_WHITE - G_BLACK)));
    float bf = min(1.0, max(0.0, 1.0 * (b - B_BLACK) / (B_WHITE - B_BLACK)));

    // Multiply by 255 and write to serial COM port
    Serial.print(int(255 * rf), DEC); Serial.print(" ");
    Serial.print(int(255 * gf), DEC); Serial.print(" ");
    Serial.print(int(255 * bf), DEC); Serial.println("");
    
    // Light up diagnostic RGB LED
    diag_out_color(rf, gf, bf);

    // Delay between the measurement cycles
    delay(1000);
}

void BH1750_Init(int address){
    Wire.beginTransmission(address);
    // Configure light sensor:
    //   1lux resolution, 120uS measurement period
    Wire.write(0x10);
    Wire.endTransmission();
}

void diag_out_color(float rf, float gf, float bf) {
    // Diagnostic RBG LED output
    int scale = 150;
    analogWrite(10, int(rf * scale));
    analogWrite( 9, int(gf * scale));
    analogWrite(11, int(bf * scale));
}

byte BH1750_Read(int address){
    byte i=0;
    Wire.beginTransmission(address);
    Wire.requestFrom(address, 2);
    while (Wire.available()){
        buff[i] = Wire.read(); 
        i++;
    }
    Wire.endTransmission();  
    return i;
}
