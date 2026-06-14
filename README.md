# 🎵 DFPlayer Mini Music Player

> A compact, reliable MP3 player built with Arduino Nano and DFPlayer Mini — featuring instant-response hardware interrupt buttons for Play/Pause and Next track.

---

<h2 align="center">📌 Overview</h2>

<p>This project turns an Arduino Nano and a DFPlayer Mini module into a standalone music player. Two push buttons control playback — one to play or pause, one to skip to the next track. Songs auto-advance when a track finishes. Built with hardware interrupts for instant, lag-free button response.</p>

---

<h2>✨ Features</h2>

<ul>
  <li>▶️ Play / Pause toggle</li>
  <li>⏭️ Next track with auto loop back to track 1</li>
  <li>🔁 Auto-advance when track finishes</li>
  <li>⚡ Hardware interrupt buttons — zero lag</li>
  <li>🔇 Non-blocking code — no delay() in main loop</li>
</ul>

---

<h2>🛒 Hardware Required</h2>

<table>
  <tr><th>Component</th><th>Quantity</th></tr>
  <tr><td>Arduino Nano</td><td>1</td></tr>
  <tr><td>DFPlayer Mini</td><td>1</td></tr>
  <tr><td>Push buttons</td><td>2</td></tr>
  <tr><td>1kΩ resistor</td><td>1</td></tr>
  <tr><td>Speaker 4Ω or 8Ω (0.5W – 2W)</td><td>1</td></tr>
  <tr><td>MicroSD card (FAT32, max 32GB)</td><td>1</td></tr>
  <tr><td>100µF capacitor (optional, reduces audio noise)</td><td>1</td></tr>
</table>

---

<h2>🔌 Wiring</h2>

<h3>DFPlayer Mini → Arduino Nano</h3>

<table>
  <tr><th>DFPlayer Pin</th><th>Arduino Nano</th><th>Note</th></tr>
  <tr><td>VCC</td><td>5V</td><td></td></tr>
  <tr><td>GND</td><td>GND</td><td></td></tr>
  <tr><td>TX</td><td>D10</td><td>DFPlayer sends to Nano</td></tr>
  <tr><td>RX</td><td>D11</td><td><b>Via 1kΩ resistor</b></td></tr>
  <tr><td>SPK_1</td><td>Speaker +</td><td></td></tr>
  <tr><td>SPK_2</td><td>Speaker −</td><td></td></tr>
</table>

<h3>Buttons</h3>

<table>
  <tr><th>Button</th><th>Arduino Pin</th><th>Other Leg</th></tr>
  <tr><td>Play / Pause</td><td>D2 (INT0)</td><td>GND</td></tr>
  <tr><td>Next</td><td>D3 (INT1)</td><td>GND</td></tr>
</table>

<blockquote>No external pull-up resistors needed — code uses INPUT_PULLUP. D2 and D3 are hardware interrupt pins for instant response.</blockquote>

---

<h2>💾 SD Card Setup</h2>

<p>DFPlayer reads files by <b>file system write order</b>, not filename. The order you copy files onto the card is what matters.</p>

<h3>Folder Structure</h3>

```
SD Card (FAT32)
└── 01/
    ├── 001.mp3
    ├── 002.mp3
    ├── 003.mp3
    └── 004.mp3
```

<h3>Steps — Windows CMD</h3>

<ol>
  <li>Format SD card as FAT32 — full format, not quick</li>
  <li>Create folder <code>01</code></li>
  <li>Copy songs one by one in order — never drag and drop all at once</li>
</ol>

```cmd
format D: /FS:FAT32 /V:MUSIC
md D:\01
copy "song1.mp3" D:\01\001.mp3
copy "song2.mp3" D:\01\002.mp3
copy "song3.mp3" D:\01\003.mp3
copy "song4.mp3" D:\01\004.mp3
```

<ol start="4">
  <li>Verify write order: <code>dir D:\01 /OD</code> — must show 001 → 002 → 003 → 004</li>
</ol>

---

<h2>⚙️ Configuration</h2>

<table>
  <tr><th>Setting</th><th>Default</th><th>Description</th></tr>
  <tr><td><code>TOTAL_TRACKS</code></td><td>4</td><td>Total songs on SD card</td></tr>
  <tr><td><code>VOLUME</code></td><td>25</td><td>Volume, range 0–30</td></tr>
  <tr><td><code>DEBOUNCE_MS</code></td><td>300</td><td>Button debounce in milliseconds</td></tr>
  <tr><td><code>AUTOADVANCE_COOLDOWN</code></td><td>3000</td><td>Delay before auto-next triggers (ms)</td></tr>
</table>

---

<h2>📦 Library</h2>

<p>Install via Arduino Library Manager:<br>
<b>Sketch → Include Library → Manage Libraries → search: DFRobotDFPlayerMini</b></p>

---

<h2>🛠️ Troubleshooting</h2>

<table>
  <tr><th>Problem</th><th>Fix</th></tr>
  <tr><td>DFPlayer not found</td><td>Check TX→D10, RX→D11 via 1kΩ, VCC=5V, SD inserted</td></tr>
  <tr><td>Songs in wrong order</td><td>Reformat SD and recopy one by one via CMD</td></tr>
  <tr><td>First song skipped</td><td>File system order wrong — redo SD card setup</td></tr>
  <tr><td>Buttons laggy</td><td>Increase DEBOUNCE_MS to 350</td></tr>
  <tr><td>Audio crackling</td><td>Add 100µF capacitor between DFPlayer VCC and GND</td></tr>
  <tr><td>No sound</td><td>Check SPK_1 and SPK_2, speaker must be 4Ω or 8Ω not piezo</td></tr>
  <tr><td>Song plays twice</td><td>Increase AUTOADVANCE_COOLDOWN to 4000</td></tr>
</table>

---

<h2>📄 License</h2>

<p>MIT — free to use, modify, and share.</p>
