const int buttonPin = 2;// Define the pin for the button

int buttonState = 0;// Define a variable to store the button state

int lastButtonState = 0;// Define a variable to store the previous button state

int buttonCount = 0;// Define a variable to count the button presses

void setup() {
  // Set the button pin as input
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button state has changed
  if (buttonState != lastButtonState) {
    // Check if the new state is HIGH (button pressed)
    if (buttonState == HIGH) {
      buttonCount++;// Increment the button count
      // Print the button count
      Serial.print("Button press count: ");
      Serial.println(buttonCount);
    }
    // Update the last button state
    lastButtonState = buttonState;
  }
}

