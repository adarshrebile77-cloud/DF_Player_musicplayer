🎵 DFPlayer Mini Music Player

A compact, reliable MP3 player built with Arduino Nano and DFPlayer Mini — featuring instant-response hardware interrupt buttons for Play/Pause and Next track.


Overview
This project turns an Arduino Nano and a DFPlayer Mini module into a standalone music player. Two push buttons control playback — one to play or pause, one to skip to the next track. Songs auto-advance when a track finishes. Built with hardware interrupts for instant, lag-free button response.

Features

▶️ Play / Pause toggle
⏭️ Next track with auto loop back to track 1
🔁 Auto-advance when track finishes
⚡ Hardware interrupt buttons — zero lag
🔇 Non-blocking code — no delay() in main loop


Hardware Required
ComponentQuantityArduino Nano1DFPlayer Mini1Push buttons21kΩ resistor1Speaker 4Ω or 8Ω (0.5W – 2W)1MicroSD card (FAT32, max 32GB)1100µF capacitor (optional, reduces audio noise)1

Wiring
DFPlayer Mini → Arduino Nano
DFPlayer PinArduino NanoNoteVCC5VGNDGNDTXD10DFPlayer sends to NanoRXD11Via 1kΩ resistorSPK_1Speaker +SPK_2Speaker −
Buttons
ButtonArduino PinOther LegPlay / PauseD2 (INT0)GNDNextD3 (INT1)GND

No external pull-up resistors needed — code uses INPUT_PULLUP. D2 and D3 are hardware interrupt pins for instant response.


SD Card Setup
DFPlayer reads files by file system write order, not filename. The order you copy files onto the card is what matters.
Folder structure
SD Card (FAT32)
└── 01/
    ├── 001.mp3
    ├── 002.mp3
    ├── 003.mp3
    └── 004.mp3
Steps (Windows CMD)

Format SD card as FAT32 — full format, not quick
Create folder 01
Copy songs one by one in order — never drag and drop all at once

cmdformat D: /FS:FAT32 /V:MUSIC
md D:\01
copy "song1.mp3" D:\01\001.mp3
copy "song2.mp3" D:\01\002.mp3
copy "song3.mp3" D:\01\003.mp3
copy "song4.mp3" D:\01\004.mp3

Verify write order: dir D:\01 /OD — must show 001 → 002 → 003 → 004


Configuration
SettingDefaultDescriptionTOTAL_TRACKS4Total songs on SD cardVOLUME25Volume, range 0–30DEBOUNCE_MS300Button debounce in millisecondsAUTOADVANCE_COOLDOWN3000Delay before auto-next triggers (ms)

Library
Install via Arduino Library Manager:

Sketch → Include Library → Manage Libraries → search: DFRobotDFPlayerMini

Troubleshooting
ProblemFixDFPlayer not foundCheck TX→D10, RX→D11 via 1kΩ, VCC=5V, SD insertedSongs in wrong orderReformat SD and recopy one by one via CMDFirst song skippedFile system order wrong — redo SD card setupButtons laggyIncrease DEBOUNCE_MS to 350Audio cracklingAdd 100µF capacitor between DFPlayer VCC and GNDNo soundCheck SPK_1 and SPK_2, speaker must be 4Ω or 8Ω not piezoSong plays twiceIncrease AUTOADVANCE_COOLDOWN to 4000

License
MIT — free to use, modify, and share.
