const int buttonPin = 5;
const int longThreshold = 200;
const int newLetterTime = 500;
const int newWordTime;

unsigned long start = 0;
unsigned long end = 0;
unsigned long currentTime = millis();
unsigned long elapsedTime = 0;

int turn = 0;
int letter[5] = {0, 0, 0, 0, 0}; // 0 er ingenting, 1 er en prik og 2 er en streng

bool isPressed = false;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  currentTime = millis();

  if(buttonState == 0 && !isPressed) {
    start = millis();
    isPressed = true;

  } else if(buttonState == 1 && isPressed) {
    end = millis();
    elapsedTime = end - start;
    
    if(elapsedTime > 10 && turn < 5) {
      if(elapsedTime < longThreshold) {
        letter[turn] = 1;
      } else {
        letter[turn] = 2;
      }

      turn += 1;
    }

    isPressed = false;
  }

  if(newLetterTime < (currentTime - end) && buttonState == 1) {
      turn = 0;
    }

}
