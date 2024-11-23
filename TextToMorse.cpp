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
