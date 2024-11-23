# Arduino Morse Code Converter
This project converts text entered through the Serial Monitor of the Arduino IDE into Morse code. The Morse code is displayed using the onboard LED of the Arduino Uno R3.

## Features
- Converts letters (A-Z) and numbers (0-9) into Morse code.
- Uses the onboard LED (connected to pin 13) to blink the Morse code.
- Accepts text input via the Serial Monitor.
- Implements appropriate delays for dots, dashes, and spaces for readability.

## Components Required
1. **Arduino Uno R3**
2. USB Cable for programming and power
3. Arduino IDE for coding and accessing the Serial Monitor

## How It Works
1. Enter a text string (letters and numbers) in the Serial Monitor.
2. The Arduino processes each character in the string:
   - **Dot (.)**: A short blink (500 ms ON, 50 ms OFF).
   - **Dash (-)**: A long blink (1000 ms ON, 50 ms OFF).
   - **Space between symbols in a character:** 50 ms OFF.
   - **Space between characters:** 50 ms OFF.
   - **Space between words:** 1500 ms OFF.
3. The onboard LED blinks to represent the Morse code sequence.

## Code
Below is the Arduino code used for this project:

```cpp
// Morse code mapping for each character
String morseCodeMap[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",  // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                         // U-Z
  "-----", ".----", "..---", "...--", "....-",                         // 0-4
  ".....", "-....", "--...", "---..", "----."                          // 5-9
};

#define LED_PIN 13 // Built-in LED on Arduino Uno R3

// Morse code timing in milliseconds
const int dotDuration = 500;    // Duration of a dot (.)
const int dashDuration = 1000;   // Duration of a dash (-)
const int gapBetweenSymbols = 50;  // Gap between dot and dash of the same character
const int gapBetweenCharacters = 50; // Gap between characters
const int gapBetweenWords = 1500;     // Gap between words (space)

void setup() {
  pinMode(LED_PIN, OUTPUT);   // Set LED pin as output
  digitalWrite(LED_PIN, LOW); // Turn off LED
  Serial.begin(9600);         // Start serial communication
  Serial.println("Enter text to convert to Morse code:");
}

void loop() {
  // Wait for input from the Serial Monitor
  if (Serial.available() > 0) {
    String inputText = Serial.readStringUntil('\n'); // Read the input text
    inputText.trim(); // Remove any leading/trailing spaces
    inputText.toUpperCase(); // Convert text to uppercase

    Serial.println("Morse Code Translation:");
    for (int i = 0; i < inputText.length(); i++) {
      char c = inputText[i];
      
      if (c >= 'A' && c <= 'Z') { // For alphabets
        blinkMorseCode(morseCodeMap[c - 'A']);
      } else if (c >= '0' && c <= '9') { // For digits
        blinkMorseCode(morseCodeMap[c - '0' + 26]);
      } else if (c == ' ') { // For space (word gap)
        delay(gapBetweenWords);
      } else {
        // Ignore unsupported characters
        Serial.println("Unsupported character: " + String(c));
      }

      // Add a gap between characters (except for spaces)
      if (c != ' ') {
        delay(gapBetweenCharacters);
      }
    }
    Serial.println("Done!");
  }
}

// Function to blink Morse code for a given character
void blinkMorseCode(String morseCode) {
  Serial.print(morseCode + " "); // Print the Morse code to the Serial Monitor
  
  for (int i = 0; i < morseCode.length(); i++) {
    if (morseCode[i] == '.') {
      digitalWrite(LED_PIN, HIGH);
      delay(dotDuration);
    } else if (morseCode[i] == '-') {
      digitalWrite(LED_PIN, HIGH);
      delay(dashDuration);
    }
    digitalWrite(LED_PIN, LOW);
    delay(gapBetweenSymbols); // Gap between symbols in the same character
  }
}
```

## Setup Instructions
1. Connect the Arduino Uno:
   - Plug the Arduino Uno R3 into your computer using a USB cable.
2. Install the Arduino IDE:
   - Download and install the Arduino IDE.
3. Upload the Code:
   - Copy the above code into the Arduino IDE.
   - Select the correct Board (Arduino Uno) and Port under the Tools menu.
   - Click Upload to flash the code to the Arduino.
4. Open the Serial Monitor:
   - Set the baud rate to 9600.
   - Type a text string and press Enter.
5. Observe the LED:
   - The onboard LED will blink the Morse code corresponding to your input.

## Morse Code Reference
| Character |	Morse Code |
|-----------|------------|
|     A     |    .-      |
|     B     |    -...    |
|     C     |    -.-.    |
|     D     |    -..     |
|     E     |    .       |
|     F     |    ..-.    |
|     G     |    --.     |
|     H     |    ....    |
|     I     |    ..      |
|     J     |    .---    |
|     K     |    -.-     |
|     L     |    .-..    |
|     M     |    --      |
|     N     |    -.      |
|     O     |    ---     |
|     P     |    .--.    |
|     Q     |    --.-    |
|     R     |    .-.     |
|     S     |    ...     |
|     T     |    -       |
|     U     |    ..-     |
|     V     |    ...-    |
|     W     |    .--     |
|     X     |    -..-    |
|     Y     |    -.--    |
|     Z     |    --..    |
|     0     |    -----   |
|     1     |    .----   |
|     2     |    ..---   |
|     3     |    ...--   |
|     4     |    ....-   |
|     5     |    .....   |
|     6     |    -....   |
|     7	    |    --...   |
|     8     |    ---..   |
|     9     |    ----.   |

## Example
Input (via Serial Monitor):

## Copy code
```cpp
HELLO WORLD
```

## Output (on LED):
```
.... . .-.. .-.. ---   .-- --- .-. .-.. -..
```

## Notes
Special characters and punctuation are not supported in this version.
Ensure the input is kept short for easier testing.
