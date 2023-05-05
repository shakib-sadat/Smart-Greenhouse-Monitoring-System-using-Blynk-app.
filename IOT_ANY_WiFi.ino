#define BLYNK_TEMPLATE_ID           "TMPL6TfFfjKU7"
#define BLYNK_TEMPLATE_NAME         "Green House"
#define BLYNK_AUTH_TOKEN            "ZHI_suvcagkv1YO2pv6pokXOfTGRfGT1"


#define BLYNK_PRINT Serial

#include <WiFiManager.h>
#ifdef ESP8266
#include <BlynkSimpleEsp8266.h>
#elif defined(ESP32)
#include <BlynkSimpleEsp32.h>
#else
#error "Board not found"
#endif

char* esp_ssid = "Green House";
char* esp_pass = "1234567890"; // 192.168.4.1

const int relay1 = D5; // D5-GPIO 14
const int relay2 = D6; // D6-GPIO 12
const int relay3 = D7; // D7-GPIO 13
const int relay4 = D8; // D8-GPIO 15
const int relay5 = D0; // D8-GPIO 15
const int Pin1 = D1;  // D1-GPIO 05
const int Pin2 = D2;  // D2-GPIO 04
const int Pin3 = D3;  // D3-GPIO 00
const int Pin4 = A0; // SD3-GPIO 10

int button1Pin, button2Pin, button3Pin, button4Pin;

int relay1State = LOW;
int relay2State = LOW;
int relay3State = LOW;
int relay4State = LOW;
int button1State = LOW;
int button2State = LOW;
int button3State = LOW;
int button4State = LOW;
int mood = LOW;


//Variables
char auth_token[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

String smss, sms, sms1, sms2, sms3, sms4, sms5, sms6;
int temp = 0, n = 0, k = 0, j = 0, jj = 0, jjj = 0, jjjj = 0, jjjjj = 0, jjjjjj = 0, asd = 0;
char str[700], msg[700];

void checkPhysicalButton();
// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  Blynk.syncVirtual(V9);
  Blynk.syncVirtual(V10);
  Blynk.syncVirtual(V11);
  Blynk.syncVirtual(V12);
  Blynk.syncVirtual(V13);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V6) {
  int relay1StateA = param.asInt();
  String smssss = "#" + String(relay1StateA) + "!";
  Serial.println(smssss);
  delay(500);

}

BLYNK_WRITE(V7) {
  int relay2StateA = param.asInt();
  String smssss = "#" + String(relay2StateA) + "&";
  Serial.println(smssss);
  delay(500);
}

BLYNK_WRITE(V8) {
  int relay3StateA = param.asInt();
  String smssss = "#" + String(relay3StateA) + "$";
  Serial.println(smssss);
  delay(500);
}

BLYNK_WRITE(V13) {
  mood = param.asInt();
  Serial.println(mood);
}

BLYNK_WRITE(V9) {
  if (mood == 1) {
    relay1State = param.asInt();
    digitalWrite(relay1, relay1State);
  }
}

BLYNK_WRITE(V10) {
  if (mood == 1) {
    relay2State = param.asInt();
    Serial.println(relay2State);
    digitalWrite(relay2, relay2State);
  }
}

// When App button is pushed - switch the state
BLYNK_WRITE(V11) {
  if (mood == 1) {
    relay3State = param.asInt();
    digitalWrite(relay3, relay3State);
  }
}

// When App button is pushed - switch the state
BLYNK_WRITE(V12) {
  if (mood == 1) {
    relay4State = param.asInt();
    digitalWrite(relay4, relay4State);
  }
}

void sendSensor()
{
  if (mood == 1) {
    digitalWrite(relay5, HIGH);
    button1Pin = digitalRead(Pin1);
    button2Pin = digitalRead(Pin2);
    button3Pin = digitalRead(Pin3);
    button4Pin = analogRead(Pin4);
    if (button4Pin < 200) {
      button4Pin = LOW;
    }
    else {
      button4Pin = HIGH;
    }

    //button1
    if (button1Pin == 0) {
      if (button1State != LOW) {
        relay1State = !relay1State;
        digitalWrite(relay1, relay1State);
        Blynk.virtualWrite(V9, relay1State);
      }
      button1State = LOW;
    } else {
      button1State = HIGH;
    }

    //button2
    if (button2Pin == 0) {
      if (button2State != LOW) {
        relay2State = !relay2State;
        digitalWrite(relay2, relay2State);
        Blynk.virtualWrite(V10, relay2State);
      }
      button2State = LOW;
    } else {
      button2State = HIGH;
    }

    //button3
    if (button3Pin == 0) {
      if (button3State != LOW) {
        relay3State = !relay3State;
        digitalWrite(relay3, relay3State);
        Blynk.virtualWrite(V11, relay3State);
      }
      button3State = LOW;
    } else {
      button3State = HIGH;
    }

    //button4
    if (button4Pin == 0) {
      if (button4State != LOW) {
        relay4State = !relay4State;
        digitalWrite(relay4, relay4State);
        Blynk.virtualWrite(V12, relay4State);
      }
      button4State = LOW;
    } else {
      button4State = HIGH;
    }
  }
  else {
    digitalWrite(relay5, LOW);
  }
}


const int Erasing_button = 0;

void configModeCallback(WiFiManager* myWiFiManager) {
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  Serial.begin(9600);
  pinMode(Erasing_button, INPUT);
  pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  pinMode(Pin3, INPUT);
  pinMode(Pin4, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);

  for (uint8_t t = 4; t > 0; t--) {
    digitalWrite(D4, LOW);
    delay(500);
    Serial.println(t);
    digitalWrite(D4, HIGH);
    delay(500);
  }

  // Press and hold the button to erase all the credentials
  if (digitalRead(Erasing_button) == LOW) {
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    ESP.restart();
    delay(1000);
  }

  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if (!wifiManager.autoConnect(esp_ssid, esp_pass)) {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.println("connected...yeey :)");
  digitalWrite(D4, LOW);
  Blynk.config(auth_token);
  timer.setInterval(100L, sendSensor);
}

void loop() {
  serialEvent();
  Blynk.run();
  timer.run();
}

void serialEvent() {
  while (Serial.available()) {
    char ch = (char)Serial.read();
    str[n++] = ch;
    if (ch == '*') {
      temp = 1;
      break;
    }
  }
  if (temp == 1) {
    for (int i = 0; i < n; i++) {
      if (str[i] == '#') {
        j = i;
      }

      if (str[i] == '@') {
        if (asd == 0) {
          jj = i;
          asd++;
        }
        else if (asd == 1) {
          jjj = i;
          asd++;
        }
        else if (asd == 2) {
          jjjj = i;
          asd++;
        }
        else if (asd == 3) {
          jjjjj = i;
          asd++;
        }
        else if (asd == 4) {
          jjjjjj = i;
          asd++;
        }
      }

      if (str[i] == '*') {
        k = i;
        break;
      }
    }
    int l = 0;
    sms = String(str);
    sms1 = sms.substring(j + 1, jj);
    sms2 = sms.substring(jj + 1, jjj);
    sms3 = sms.substring(jjj + 1, jjjj);
    sms4 = sms.substring(jjjj + 1, jjjjj);
    sms5 = sms.substring(jjjjj + 1, jjjjjj);
    sms6 = sms.substring(jjjjjj + 1, k);
    Blynk.virtualWrite(V0, sms1);
    Blynk.virtualWrite(V1, sms2);
    Blynk.virtualWrite(V2, sms3);
    Blynk.virtualWrite(V3, sms4);
    Blynk.virtualWrite(V4, sms5);
    Blynk.virtualWrite(V5, sms6);
    Serial.print(sms1);
    Serial.print("\t");
    Serial.print(sms2);
    Serial.print("\t");
    Serial.print(sms3);
    Serial.print("\t");
    Serial.print(sms4);
    Serial.print("\t");
    Serial.print(sms5);
    Serial.print("\t");
    Serial.println(sms6);
    temp = 0;
    n = 0;
    asd = 0;
  }
}
