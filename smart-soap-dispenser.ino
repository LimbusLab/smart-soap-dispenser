const int handSensor = A0;
const int doorSensor = A1;
const int speakerPin = 9;
const int ledPin = 5;

int handThreshold = 500;
int doorThreshold = 400;
boolean washed = false;
boolean resetIt = true;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int handReading = analogRead(handSensor);
  int doorReading = analogRead(doorSensor);
  unsigned long currentMillis = millis();
  //Serial.println(handReading);
  Serial.println(doorReading);

  if (handReading > handThreshold) {
    Serial.println("infectant activated");
    resetIt = false;
    digitalWrite(ledPin, HIGH);
    previousMillis = currentMillis;
    washed = true;
  }

  else digitalWrite(ledPin, LOW);

  if (currentMillis - previousMillis >= 60000 && resetIt == false) {
    resetAll();
  }

  while (washed == true && doorReading > doorThreshold) {
    Serial.println("Good job!");
    doorReading = analogRead(doorSensor);
    //Serial.println(doorReading);
    if (doorReading < doorThreshold) {
      resetAll();
    }
  }

  boolean onlyOnce = false;
  while (washed == false && doorReading > doorThreshold) {
    resetIt = false;
    Serial.println("BAD");
    if (onlyOnce == false) {
      for(int i = 200; i<2000; i=i+5){
      tone(speakerPin, i);
      delay(1);
      }
      //digitalWrite(ledPin, HIGH);
      //delay(100);
      noTone(speakerPin);
      //digitalWrite(ledPin, LOW);
    }
    onlyOnce = true;
    doorReading = analogRead(doorSensor);
    //Serial.println(doorReading);
    if (doorReading < doorThreshold) {
      resetAll();
      onlyOnce = false;
    }
  }
}

void resetAll() {
  washed = false;
  Serial.println("RESET ALL");
  resetIt = true;
  noTone(speakerPin);
  //delay(100);
}


