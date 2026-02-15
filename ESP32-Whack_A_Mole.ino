// --- PIN CONFIGURATION ---
const int numMoles = 5;
const int ledPins[] = {2, 3, 4, 5, 6};    // 5 LEDs
const int btnPins[] = {7, 8, 10, 11, 12}; // 5 Buttons 
const int buzzerPin = 9;                  // Piezo Buzzer

// --- GAME SETTINGS ---
int lives = 3;
int score = 0;
int currentMole = -1;
unsigned long moleStartTime = 0;
int moleTimeout = 1200; // 1.2 seconds to hit
bool gameActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < numMoles; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(btnPins[i], INPUT_PULLUP);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("========================================");
  Serial.println("      ARDUINO WHACK-A-MOLE: PRO");
  Serial.println("========================================");
  Serial.println("Press any button to START!");
}

void startNewGame() {
  score = 0;
  lives = 3;
  moleTimeout = 1200;
  gameActive = true;
  Serial.println("\n--- GO! 3 LIVES REMAINING ---");
  spawnMole();
}

void spawnMole() {
  // Turn off all LEDs
  for (int i = 0; i < numMoles; i++) digitalWrite(ledPins[i], LOW);
  
  // Pick a new random mole
  int nextMole = random(0, numMoles);
  while (nextMole == currentMole) nextMole = random(0, numMoles);
  currentMole = nextMole;

  digitalWrite(ledPins[currentMole], HIGH);
  moleStartTime = millis();
}

void loop() {
  if (!gameActive) {
    // Wait for any button to start
    for (int i = 0; i < numMoles; i++) {
      if (digitalRead(btnPins[i]) == LOW) {
        delay(300);
        startNewGame();
      }
    }
  } else {
    handleGame();
  }
}

void handleGame() {
  // 1. Timeout Logic (Mole moves, NO life lost)
  if (millis() - moleStartTime > moleTimeout) {
    spawnMole();
    return;
  }

  // 2. Button Check
  for (int i = 0; i < numMoles; i++) {
    if (digitalRead(btnPins[i]) == LOW) {
      delay(50); // Debounce Shield
      
      if (i == currentMole) {
        // SUCCESS HIT
        score++;
        Serial.print("HIT! Score: "); Serial.println(score);
        tone(buzzerPin, 1200, 100);
        
        // Slightly increase speed
        if (moleTimeout > 400) moleTimeout -= 20; 
        
        delay(200); // Prevent double-triggering
        spawnMole();
      } 
      else {
        // WRONG BUTTON (Lose a life)
        lives--;
        Serial.print("WRONG! Lives: "); Serial.println(lives);
        tone(buzzerPin, 200, 400); // Low error tone
        
        if (lives <= 0) {
          endGame();
        } else {
          delay(500);
          spawnMole();
        }
      }
      return;
    }
  }
}

void endGame() {
  gameActive = false;
  for (int i = 0; i < numMoles; i++) digitalWrite(ledPins[i], LOW);
  
  Serial.println("\n*************************");
  Serial.println("GAME OVER!");
  Serial.print("Final Score: "); Serial.println(score);
  Serial.println("*************************");
  
  // Game over sound
  tone(buzzerPin, 150, 800);
  delay(1000);
}
