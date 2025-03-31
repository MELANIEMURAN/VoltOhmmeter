#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int VoltMeter = 2;
float V = 0.00;
void calculate_voltage() {
  float R1 = 10000.00;
  float R2 = 4700.00;
  float v_ref = 5.00;
  float resistor_ratio = 0.00;
  float adc_value = 0.00;
  float voltage = 0.00;
  resistor_ratio = (R2 / (R1 + R2));
  for (int i = 0; i < 20; i++) {
    adc_value = adc_value + analogRead(VoltMeter);
    delay(3);
  }
  adc_value = adc_value / 20;
  voltage = ((adc_value * v_ref) / 1023);
  V = voltage / resistor_ratio;

  Serial.print(V);
  Serial.println(" v");
  lcd.setCursor(0, 0);
  lcd.print(V);
  lcd.print(" volt        ");
}

const int OhmMeter = 0;
const int R3 = 5;
const int R2 = 4;
const int R1 = 3;
float R = 0.00;
void calculate_resistor() {
  float v_ref = 5.00;
  float r1 = 0.00;
  float r_ref1 = 985.00;
  float adc_value1 = 0.00;
  float voltage1 = 0.00;
  float r2 = 0.00;
  float r_ref2 = 10000.00;
  float adc_value2 = 0.00;
  float voltage2 = 0.00;
  float r3 = 0.00;
  float r_ref3 = 100000.00;
  float adc_value3 = 0.00;
  float voltage3 = 0.00;

  pinMode(R1, OUTPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  digitalWrite(R1, HIGH);
  for (int i = 0; i < 20; i++) {
    adc_value1 = adc_value1 + analogRead(OhmMeter);
    delay(3);
  }
  adc_value1 = adc_value1 / 20;
  voltage1 = ((adc_value1 * v_ref) / 1023);
  r1 = (voltage1 * r_ref1) / (v_ref - voltage1);

  pinMode(R1, INPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, INPUT);
  digitalWrite(R2, HIGH);
  for (int i = 0; i < 20; i++) {
    adc_value2 = adc_value2 + analogRead(OhmMeter);
    delay(3);
  }
  adc_value2 = adc_value2 / 20;
  voltage2 = ((adc_value2 * v_ref) / 1023);
  r2 = (voltage2 * r_ref2) / (v_ref - voltage2);

  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, OUTPUT);
  digitalWrite(R3, HIGH);
  for (int i = 0; i < 20; i++) {
    adc_value3 = adc_value3 + analogRead(OhmMeter);
    delay(3);
  } 
  adc_value3 = adc_value3 / 20;
  voltage3 = ((adc_value3 * v_ref) / 1023);
  r3 = (voltage3 * r_ref3) / (v_ref - voltage3);

  pinMode(R3, INPUT);

  r1 = r1 / 1000;
  r2 = r2 / 1000;
  r3 = r3 / 1000;

  if (r1 < 2 && r2 < 101 && r3 < 1001) R = r1 * 1000;
  else if (r1 > 2 && r2 < 101 && r3 < 1001) R = r2;
  else if (r1 > 2 && r2 > 101 && r3 < 2000) R = r3;
  else R = 0.00;

  Serial.print("R = ");
  Serial.println(R, 2);

  lcd.setCursor(0, 1);

  if (R == r1 * 1000) {
    lcd.print(R);
    lcd.print(" ohm          ");
  } else if (R == r2 || R == r3) {
    lcd.print(R);
    lcd.print(" kohm          ");
  } else {
    lcd.print("> 2 Mohm        ");
  }
}


void setup() {

  Serial.begin(9600);

  lcd.init();
  lcd.clear();
  lcd.backlight();
}
void loop() {

  calculate_voltage();
  calculate_resistor();
  delay(2000);
}
