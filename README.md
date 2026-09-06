# Audio Signal Chain Simulator

A terminal-based C++ simulation of a five-stage audio signal processing chain, modelling the mathematical behaviour of core dynamic and tonal processing concepts. Built as part of a self-directed study in DSP and audio programming.

NOTE:
This is not a real-time audio processor, it simulates signal flow using normalised double-precision floating point values (0.0 to 1.0) representing linear amplitude, with dB conversion for human-readable output.

---

## Signal Flow

```
Input → Noise Gate → Compressor → Low Shelf EQ → Limiter → Output Report
```

Each stage processes the output of the previous one, modelling a typical gain-staging chain used in game audio and music production.

---

## Stages

**Noise Gate** — Silences any signal below a user-defined threshold. Models the behaviour of a gate used to eliminate low-level noise or bleed between signals.

**Compressor** — Reduces the dynamic range of signals that exceed a threshold, applying a user-defined ratio. Implements the standard `threshold + (input - threshold) / ratio` gain reduction formula.

**Low Shelf EQ** — Applies a gain boost or cut to the signal using a simplified shelf model. Demonstrates the dB-to-linear conversion (`pow(10.0, gainDb / 20.0)`) used in real audio gain calculations.

**Limiter** — Hard clips the signal at a user-defined ceiling, handling both positive and negative signal boundaries. Models a brick-wall limiter used to prevent clipping at the output stage.

**Output Report** — Converts final linear amplitude to dB and prints a full chain summary including which stages were active.

---

## Building and Running

Requires a C++17 compatible compiler.

**Using g++:**
```bash
g++ -std=c++17 main.cpp signal_chain.cpp -o signal_chain
./signal_chain
```

**Using Visual Studio:**
Open the solution file and build with Ctrl+B, then run with Ctrl+F5.

---

## Example Output

```
=== AUDIO SIGNAL CHAIN ===
[ Noise Gate ]
------------------------
Input:  0.8
Output: 0.8
Change: 0.0
------------------------
[ Compressor ]
------------------------
Input:  0.8
Output: 0.575
Change: -0.225
------------------------
[ EQ ]
------------------------
Input:  0.575
Output: 0.724
Change: +0.149
------------------------
[ Limiter ]
------------------------
Input:  0.724
Output: 0.724
Change: 0.0
------------------------
=== FINAL OUTPUT REPORT ===
Original Signal: -1.94 dB
Final Signal:    -2.80 dB
Gate Triggered:  No
Compressed:      Yes
Limited:         No
```

---

## Input Validation

The program validates the following on entry:
- Input signal level must be between 0.0 and 1.0
- Compressor ratio must be greater than 0 (prevents division by zero)
- EQ frequency must be greater than 0

---

## Author

**Parth Rane** | Technical Sound Designer  
[Portfolio](https://parthraneaudio.github.io/) · [LinkedIn](https://uk.linkedin.com/in/parthraneprofile) · [YouTube](https://www.youtube.com/@ParthRaneAudio)
