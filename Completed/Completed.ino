const int buttonPin = 8;            // Define the pin for the button
const int ledPin = 2;              // Define the pin for the LED
int buttonState = LOW;              // Define a variable to store the button state
int lastButtonState = LOW;          // Define a variable to store the previous button state
unsigned long lastPressTime = 0;    // Store the time of the last button press
float buttonRate = 0.0;             // Button press rate
const unsigned long ledTimeout = 1000; // Timeout duration for turning off LED in milliseconds (5 seconds)
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor
  pinMode(ledPin, OUTPUT);          // Set the LED pin as an output
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

      // If the button is pressed (LOW)
      if (buttonState == LOW) {
        unsigned long currentTime = millis();
        // Calculate time difference since last press
        unsigned long timeDiff = currentTime - lastPressTime;
        // Update last press time
        lastPressTime = currentTime;
        // Calculate button press rate (presses per minute)
        buttonRate = 60000.0 / timeDiff;
        Serial.print("Button press rate (presses per minute): ");
        Serial.println(buttonRate, 2); // Print button press rate with 2 decimal places

        // Check if button rate is within the desired range
        if (buttonRate <= 100 || buttonRate >= 120) {
          digitalWrite(ledPin, HIGH);  // Turn on the LED
        } else {
          digitalWrite(ledPin, LOW);   // Turn off the LED if button rate is not in the desired range
        }
      }
    }
  }

  // Check if LED has been on for more than the timeout duration
  if (digitalRead(ledPin) == HIGH && millis() - lastPressTime >= ledTimeout) {
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  // Update lastButtonState
  lastButtonState = reading;
}
