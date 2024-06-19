const int buttonPin = 2;        // Define the pin for the button
const int ledPin = 12;          // Define the pin for the LED
int buttonState = LOW;          // Define a variable to store the button state
int lastButtonState = LOW;      // Define a variable to store the previous button state
int buttonCount = 0;            // Define a variable to count the button presses
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long totalTime = 0;         // Total time elapsed
unsigned long ledOnTime = 0;         // Time when LED was turned on
float buttonRate = 0.0;               // Button press rate
const unsigned long ledTimeout = 5000; // Timeout duration for turning off LED in milliseconds (5 seconds)

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

      // If the button is pressed (LOW), increment the button count
      if (buttonState == LOW) {
        buttonCount++;
        totalTime = millis();  // Update total time
        buttonRate = (float)buttonCount / (totalTime / 1000.0) * 60; // Calculate button press rate (presses per minute)
        Serial.print("Button press count: ");
        Serial.println(buttonCount);
        Serial.print("Button press rate (presses per minute): ");
        Serial.println(buttonRate, 2); // Print button press rate with 2 decimal places

        // Check if button rate is within the desired range
        if (buttonRate >= 100 && buttonRate <= 120) {
          digitalWrite(ledPin, HIGH);  // Turn on the LED
          ledOnTime = millis(); // Note the time when LED was turned on
        } else {
          digitalWrite(ledPin, LOW);   // Turn off the LED if button rate is not in the desired range
        }
      }
    }
  }

  // Check if LED has been on for more than the timeout duration
  if (digitalRead(ledPin) == HIGH && millis() - ledOnTime >= ledTimeout) {
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  // Update lastButtonState
  lastButtonState = reading;
}
