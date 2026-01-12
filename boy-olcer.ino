#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
/* ----- SES SENSORU -----
   Trig -- 11
   Echo -- 12
   VCC Herhangi bir 5V (Yada V) Kaynagina
   GND Herhangi bir GND (Yada G) Kaynagina

   ----- LCD EKRAN -----
  VSS -- GND
  VDD -- 5V
  VO -- Potansiyometre orta
  RS -- 8
  RW -- GND
  E -- 7
  D4 -- 6
  D5 -- 5
  D6 -- 4
  D7 -- 3
  K -- GND
  A -- 3.3V



   ----- Potansiyometre -----
  BU PROJEDE POTANSIYOMETRE KULLANMA CUNKI LCD EKRANIN ARKASINDA VAR

  EGER EKRANDA YAZI GORUNMEZSE YADA COK PARLAKSA ARKADAKI POTANSIYOMETRE ILE AYARLA

*/

#define TrigPin 11
#define EchoPin 12
const float Heat = 28.0;
const float HeatVal = 331.3 * (sqrt(1 + (Heat / 273.15))) / 10000;
uint16_t sure;
int dist, cal1, cal2, cal3, kalibrasyon, uz1, son;
float dist;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print ("Program Hazirlaniyor");
  delay(1000);

  DDRB |= (1 << (TrigPin - 8));
  DDRB &= ~(1 << (EchoPin - 8));

  //digitalWrite(TrigPin, HIGH);
  PORTB |= (1 << (TrigPin - 8));
  delayMicroseconds(1000);
  //digitalWrite(TrigPin, LOW);
  PORTB &= ~(1 << (TrigPin - 8));
  sure = pulseIn(EchoPin, HIGH);
  cal1 = (sure / 2) * HeatVal;
  lcd.print(cal1);
  delay(1000);
  lcd.clear();

  //digitalWrite(TrigPin, HIGH);
  PORTB |= (1 << (TrigPin - 8));
  delayMicroseconds(1000);
  //digitalWrite(TrigPin, LOW);
  PORTB &= ~(1 << (TrigPin - 8));
  sure = pulseIn(EchoPin, HIGH);
  cal2 = (sure / 2) * HeatVal;
  lcd.print(cal2);
  delay(1000);
  lcd.clear();

  //digitalWrite(TrigPin, HIGH);
  PORTB |= (1 << (TrigPin - 8));
  delayMicroseconds(1000);
  //digitalWrite(TrigPin, LOW);
  PORTB &= ~(1 << (TrigPin - 8));
  sure = pulseIn(EchoPin, HIGH);
  cal3 = (sure / 2) * HeatVal;
  lcd.print(cal3);
  delay(1000);
  lcd.clear();

  kalibrasyon = (cal1 + cal2 + cal3) / 3;
  lcd.print(kalibrasyon);
  delay(1000);
  uz1 = kalibrasyon * 2 / 3;

}

void loop() {

  PORTB |= (1 << (TrigPin - 8));
  delayMicroseconds(1000);
  //digitalWrite(TrigPin, LOW);
  PORTB &= ~(1 << (TrigPin - 8));
  sure = pulseIn(EchoPin, HIGH);
  dist = (sure / 2) * HeatVal;
  while (dist < uz1) {
    PORTB |= (1 << (TrigPin - 8));
    delayMicroseconds(1000);
    //digitalWrite(TrigPin, LOW);
    PORTB &= ~(1 << (TrigPin - 8));
    sure = pulseIn(EchoPin, HIGH);
    dist = (sure / 2) * HeatVal;
    son = kalibrasyon - dist;
    lcd.println(son);
    delay(100);
    lcd.clear();
  }
}
