/*
 * DFPlayer Mini - Arduino Nano
 * Play/Pause : D2 (INT0)
 * Next       : D3 (INT1)
 * DFPlayer TX -> D10 | DFPlayer RX -> D11 (via 1kΩ resistor)
 * Speaker    -> SPK_1 and SPK_2
 * SD Card    -> FAT32, folder "01", files: 001.mp3 002.mp3 003.mp3 004.mp3
 */

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// ── Pins ─────────────────────────────────────────────────────
#define PLAY_PIN     2
#define NEXT_PIN     3
#define DFPLAYER_RX  10
#define DFPLAYER_TX  11

// ── Settings ─────────────────────────────────────────────────
#define TOTAL_TRACKS  4
#define VOLUME       25    // 0–30
#define DEBOUNCE_MS  300
#define AUTOADVANCE_COOLDOWN 3000  // ms after track starts before auto-advance allowed

// ── Objects ──────────────────────────────────────────────────
SoftwareSerial playerSerial(DFPLAYER_RX, DFPLAYER_TX);
DFRobotDFPlayerMini player;

// ── State ────────────────────────────────────────────────────
int  currentTrack    = 1;
bool isPlaying       = false;
unsigned long trackStartTime = 0;

// ── ISR Flags ────────────────────────────────────────────────
volatile bool playPressed = false;
volatile bool nextPressed = false;
unsigned long lastPlayTime = 0;
unsigned long lastNextTime = 0;

// ── ISRs ─────────────────────────────────────────────────────
void ISR_play() {
  unsigned long now = millis();
  if (now - lastPlayTime > DEBOUNCE_MS) {
    playPressed  = true;
    lastPlayTime = now;
  }
}

void ISR_next() {
  unsigned long now = millis();
  if (now - lastNextTime > DEBOUNCE_MS) {
    nextPressed  = true;
    lastNextTime = now;
  }
}

// ── Play a specific track ─────────────────────────────────────
void playTrack(int track) {
  player.play(track);
  isPlaying      = true;
  trackStartTime = millis();
  Serial.print(F("▶ Playing track "));
  Serial.print(track);
  Serial.print(F(" / "));
  Serial.println(TOTAL_TRACKS);
}

// ── Play / Pause ─────────────────────────────────────────────
void handlePlayPause() {
  if (!isPlaying) {
    playTrack(currentTrack);
  } else {
    player.pause();
    isPlaying = false;
    Serial.println(F("⏸ Paused"));
  }
}

// ── Next Track ───────────────────────────────────────────────
void handleNext() {
  currentTrack++;
  if (currentTrack > TOTAL_TRACKS) currentTrack = 1;
  Serial.print(F("⏭ Next -> track "));
  Serial.println(currentTrack);
  playTrack(currentTrack);
}

// ── Auto-advance when track finishes ─────────────────────────
void checkTrackFinished() {
  if (!isPlaying) return;

  // Ignore finish signals too soon after a track starts (avoids double-trigger)
  if (millis() - trackStartTime < AUTOADVANCE_COOLDOWN) return;

  if (playerSerial.available()) {
    if (player.available()) {
      uint8_t type = player.readType();
      if (type == DFPlayerPlayFinished) {
        Serial.println(F("✓ Track finished — auto next"));
        handleNext();
      }
    }
  }
}

// ── Setup ────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  playerSerial.begin(9600);

  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(NEXT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PLAY_PIN), ISR_play, FALLING);
  attachInterrupt(digitalPinToInterrupt(NEXT_PIN), ISR_next, FALLING);

  Serial.println(F("Initializing DFPlayer..."));

  if (!player.begin(playerSerial)) {
    Serial.println(F("ERROR: DFPlayer not found!"));
    Serial.println(F("Check wiring: TX->D10, RX->D11 via 1kΩ, VCC=5V, SD inserted"));
    while (true);
  }

  delay(1000);  // Let DFPlayer fully read the SD card
  player.volume(VOLUME);
  player.EQ(DFPLAYER_EQ_NORMAL);
  player.stop();

  currentTrack = 1;
  isPlaying    = false;

  Serial.println(F("✓ Ready!"));
  Serial.println(F("D2 = Play/Pause   D3 = Next"));
}

// ── Loop ─────────────────────────────────────────────────────
void loop() {
  if (playPressed) {
    playPressed = false;
    handlePlayPause();
  }

  if (nextPressed) {
    nextPressed = false;
    handleNext();
  }

  checkTrackFinished();
}