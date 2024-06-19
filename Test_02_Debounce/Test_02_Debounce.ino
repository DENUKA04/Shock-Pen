const int buttonPin = 2;        // Define the pin for the button
int buttonState = LOW;          // Define a variable to store the button state
int lastButtonState = LOW;      // Define a variable to store the previous button state
int buttonCount = 0;            // Define a variable to count the button presses
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor
  Serial.begin(9600);
}

void loop() {
  // Read the state of the button
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    // Update the debounce timer
    lastDebounceTime = millis();
  }

  // Check if enough time has passed since the last change
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update buttonState
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed (LOW), increment the button count
      if (buttonState == LOW) {
        buttonCount++;
        Serial.print("Button press count: ");
        Serial.println(buttonCount);
      }
    }
  }

  // Update lastButtonState
  lastButtonState = reading;
}
