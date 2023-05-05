#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN  4
#define DHTTYPE DHT11   // DHT 11

#define fire    2
#define ldr     3
#define MOS     A0

#define relay1  5
#define relay2  6
#define relay3  7
#define relay4  8
#define buzzer  13

#define bottom1 9
#define bottom2 10
#define bottom3 11
#define bottom4 12
#define bottom5 A1

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int moisture = 80, h = 0, Humidity = 50, Temperature = 25, MOSTURE = 0, mood = 0;
float t = 0;
int asdfg = 0;

String smss, sms, sms1, sms2, sms3, sms4, sms5;
int temp = 0, n = 0, k = 0, j = 0, jj = 0, jjj = 0, jjjj = 0, jjjjj = 0, jjjjjj = 0, asd = 0;
char str[700], msg[700];

#define REPORTING_PERIOD_MS 1500
uint32_t tsLastReport = 0;

void setup() {
  pinMode(fire, INPUT);
  pinMode(ldr, INPUT);
  pinMode(MOS, INPUT);
  pinMode(bottom1, INPUT);
  pinMode(bottom2, INPUT);
  pinMode(bottom3, INPUT);
  pinMode(bottom4, INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(buzzer, LOW);

  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 2);
  lcd.print((char)223);
  lcd.print("C,H:");
  lcd.print(h);
  lcd.print("%   ");
  lcd.setCursor(0, 1);
  lcd.print("M_LVL:");
  lcd.print(MOSTURE);
  lcd.print("%");
  lcd.print("    ");
}

void loop() {
  serialEvent();
  h = dht.readHumidity();
  t = dht.readTemperature();
  int FIRE = digitalRead(fire);
  int LDR = digitalRead(ldr);
  MOSTURE = analogRead(MOS);
  MOSTURE = map(MOSTURE, 520, 1010, 100, 0);
  if (MOSTURE <= 2) {
    MOSTURE = 0;
  }
  if (MOSTURE >= 100) {
    MOSTURE = 100;
  }

  if (FIRE == 0) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
  int BBB = digitalRead(bottom5);
  if (BBB == 1) {
    mood = 1;
  }
  else {
    mood = 0;
  }

  if (mood == 1) {
    int Ba = digitalRead(bottom1);
    int Bb = digitalRead(bottom2);
    int Bc = digitalRead(bottom3);
    int Bd = digitalRead(bottom4);
    if (Ba == 1) {
      digitalWrite(relay1, LOW);
    }
    else {
      digitalWrite(relay1, HIGH);
    }

    if (Bb == 1) {
      digitalWrite(relay2, LOW);
    }
    else {
      digitalWrite(relay2, HIGH);
    }

    if (Bc == 1) {
      digitalWrite(relay3, LOW);
    }
    else {
      digitalWrite(relay3, HIGH);
    }

    if (Bd == 1) {
      digitalWrite(relay4, LOW);
    }
    else {
      digitalWrite(relay4, HIGH);
    }
  }
  else {
    if (LDR == 1) {
      digitalWrite(relay1, LOW);
    }
    else {
      digitalWrite(relay1, HIGH);
    }

    if (MOSTURE >= moisture) {
      digitalWrite(relay2, HIGH);
    }
    else {
      digitalWrite(relay2, LOW);
    }

    if (t >= Temperature) {
      digitalWrite(relay3, LOW);
    }
    else {
      digitalWrite(relay3, HIGH);
    }

    if (h <= Humidity) {
      digitalWrite(relay4, LOW);
    }
    else {
      digitalWrite(relay4, HIGH);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 2);
  lcd.print((char)223);
  lcd.print("C,H:");
  lcd.print(h);
  lcd.print("%   ");
  lcd.setCursor(0, 1);
  lcd.print("M_LVL:");
  lcd.print(MOSTURE);
  lcd.print("%");
  lcd.print("    ");

//  Serial.print(FIRE);
//  Serial.print("\t");
//  Serial.print(LDR);
//  Serial.print("\t");
//  Serial.print(MOSTURE);
//  Serial.print("\t");
//  Serial.print(t);
//  Serial.print("\t");
//  Serial.println(h);

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    if (asdfg == 3) {
      asdfg = 0;
      String sms = "#" + String(t) + "@" + String(h) + "@" + String(MOSTURE) + "@" + String(moisture)  + "@" + String(Temperature) + "@" + String(Humidity) + "*";
      Serial.println(sms);
    }
    else {
      asdfg++;
    }
    tsLastReport = millis();
  }
}


void serialEvent() {
  while (Serial.available()) {
    char ch = (char)Serial.read();
    str[n++] = ch;
    if (ch == '!') {
      temp = 1;
      break;
    }
    if (ch == '&') {
      temp = 2;
      break;
    }

    if (ch == '$') {
      temp = 3;
      break;
    }
  }
  if (temp == 1) {
    for (int i = 0; i < n; i++) {
      if (str[i] == '#') {
        j = i;
      }
      if (str[i] == '!') {
        k = i;
        break;
      }
    }
    int l = 0;
    sms = String(str);
    sms1 = sms.substring(j + 1, k);
    Temperature = sms1.toInt();
    Serial.println(sms1);
    Serial.println(Temperature);
    temp = 0;
    n = 0;
  }
  if (temp == 2) {
    for (int i = 0; i < n; i++) {
      if (str[i] == '#') {
        j = i;
      }
      if (str[i] == '&') {
        k = i;
        break;
      }
    }
    int l = 0;
    sms = String(str);
    sms1 = sms.substring(j + 1, k);
    Humidity = sms1.toInt();
    Serial.println(sms1);
    Serial.println(Humidity);
    temp = 0;
    n = 0;
  }

  if (temp == 3) {
    for (int i = 0; i < n; i++) {
      if (str[i] == '#') {
        j = i;
      }
      if (str[i] == '$') {
        k = i;
        break;
      }
    }
    int l = 0;
    sms = String(str);
    sms1 = sms.substring(j + 1, k);
    moisture = sms1.toInt();
    Serial.println(sms1);
    Serial.println(moisture);
    temp = 0;
    n = 0;
  }
}
