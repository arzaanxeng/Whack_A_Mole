# 🔨 Arduino Whack-A-Mole

A fast-paced reflex game for Arduino. Features 5 moles (LEDs) and a dynamic speed system that gets faster as you score.

## 🕹️ Game Rules
1. **Whack:** Press the button corresponding to the lit LED to score points.
2. **Speed:** The moles stay up for shorter periods as your score increases.
3. **Lives:** You start with **3 lives**.
   - Missing a mole (timeout) does **not** cost a life.
   - Pressing the **wrong** button costs 1 life.
4. **Game Over:** Lose all 3 lives and the game ends.

## 🔌 Wiring
| Component | Pin |
|-----------|-----|
| LEDs 1-5  | 2, 3, 4, 5, 6 |
| Buttons 1-5 | 7, 8, 10, 11, 12 |
| Piezo (+) | 9 |

## 🛠️ Key Features
- **Software Debouncing:** Filters electrical noise for clean button presses.
- **Randomization:** Uses `random()` to ensure unpredictable mole patterns.
- **Progressive Difficulty:** Mole intervals shrink by 20ms per hit.
