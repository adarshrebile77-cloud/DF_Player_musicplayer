DFPlayer Mini Music Player — Arduino Nano

HARDWARE
- Arduino Nano x1
- DFPlayer Mini x1
- Push buttons x2
- 1k ohm resistor x1
- Speaker 4ohm or 8ohm x1
- MicroSD card FAT32 x1

WIRING
DFPlayer VCC  -> Arduino 5V
DFPlayer GND  -> Arduino GND
DFPlayer TX   -> Arduino D10
DFPlayer RX   -> Arduino D11 (via 1k ohm resistor)
DFPlayer SPK1 -> Speaker +
DFPlayer SPK2 -> Speaker -
Play button   -> D2 and GND
Next button   -> D3 and GND

SD CARD SETUP
1. Format as FAT32 (full format)
2. Create folder named 01
3. Copy songs one by one in CMD in order

CMD commands:
format D: /FS:FAT32 /V:MUSIC
md D:\01
copy "song1.mp3" D:\01\001.mp3
copy "song2.mp3" D:\01\002.mp3
copy "song3.mp3" D:\01\003.mp3
copy "song4.mp3" D:\01\004.mp3

SD card structure:
D:\
└── 01\
    ├── 001.mp3
    ├── 002.mp3
    ├── 003.mp3
    └── 004.mp3

CODE SETTINGS
TOTAL_TRACKS         4     change if you add more songs
VOLUME              25     range 0 to 30
DEBOUNCE_MS        300     increase if buttons double trigger
AUTOADVANCE_COOLDOWN 3000  ms before auto next kicks in

TROUBLESHOOTING
DFPlayer not found   -> check TX->D10, RX->D11 via 1k ohm, VCC=5V, SD inserted
Songs in wrong order -> reformat SD and recopy one by one in CMD
Buttons laggy        -> increase DEBOUNCE_MS to 350
Audio crackling      -> add 100uF capacitor between DFPlayer VCC and GND
No sound             -> check SPK1 and SPK2, speaker must be 4ohm or 8ohm not piezo
Song plays twice     -> increase AUTOADVANCE_COOLDOWN to 4000
