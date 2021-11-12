//#https://www.youtube.com/thongminhvo
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 20, 4);
const int stepPin = 7;//clk+
const int dirPin = 6;//cw+
#define startt 4
#define stopp 3
#define relay 5
#define counter 8
int amount = 0;
//..............................
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(startt, INPUT_PULLUP);
  pinMode(stopp, INPUT_PULLUP);
  pinMode(counter, INPUT_PULLUP);
  digitalWrite(relay, LOW);
}
//.................................
void loop () {
sett:
  int i = 0;
  int j = 0;
  long bb = analogRead(A0);
  long aa = analogRead(A1);
  long cc = analogRead(A2);
  double b = map(bb, 0, 1023, 1, 50) ;//speed
  double a = map(aa, 0, 1023, 1, 20);//distance
  double c = map(cc, 0, 1023, 2, 15);//delay
  //serial.println(bb);
  //lcd.clear ();
  //..............................
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.setCursor(10, 0);
  lcd.print(b / 10);
  lcd.setCursor(15, 0);
  lcd.print("(v/s)");

  lcd.setCursor(0, 1);
  lcd.print("Interval:");
  lcd.setCursor(10, 1);
  lcd.print(a / 10);
  lcd.setCursor(15, 1);
  lcd.print("(v)");

  lcd.setCursor(0, 2);
  lcd.print("Timer:");
  lcd.setCursor(10, 2);
  lcd.print(c / 10);
  lcd.setCursor(15, 2);
  lcd.print("(s)");
  lcd.setCursor(0, 3);
  lcd.print("");
  lcd.setCursor(10, 3);
  lcd.print("");
  lcd.setCursor(0, 3);
  lcd.print("Count:              "); lcd.setCursor(12, 3);
  lcd.print(amount);
  //.............................
  if (digitalRead(counter) == 0) {
    amount = amount + 50;
    lcd.setCursor(12, 3);
    lcd.print(amount);
    delay(500);
  }
  //................................
  if ((digitalRead(startt) == 0) && (amount > 0))
  {
    while (j < amount)
    {
      Serial.println("ON");
      digitalWrite(dirPin, HIGH);
      for (int x = 0; x < a * 160 ; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3125 / b);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(3125 / b);
        if (digitalRead (stopp) == 0)
        {
          amount = 0;
          Serial.println("stop");
          goto sett;
        }
      }
      digitalWrite(relay, HIGH);
      delay(c * 100);
      digitalWrite(relay, LOW);
      i++;
      lcd.setCursor(7, 3);
      lcd.print(i);
      if (digitalRead(stopp) == 0)
      {
        amount = 0;
        Serial.println("stop");
        goto sett;
      }
      j++;
    }
    amount = 0;
  }
}
