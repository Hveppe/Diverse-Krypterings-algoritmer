const int buttonPin = 5;
unsigned long start = millis();
unsigned long end = 0;
unsigned long elapsedTime = 0;

bool isPressed = false;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if(buttonState == 0 && !isPressed) {
    start = millis();
    isPressed = true;

  } else if(buttonState == 1 && isPressed) {
    end = millis();
    elapsedTime = end - start;
    
    if(elapsedTime > 10) {
      Serial.println(elapsedTime);
    }

    isPressed = false;
  }

}
