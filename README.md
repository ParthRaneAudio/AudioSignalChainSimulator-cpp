# Audio Signal Chain Simulator

A C++ command line tool that processes WAV audio files through a five-stage signal processing chain. Built as part of a self-directed study in DSP and audio programming, working toward a mathematically-driven reverb system in Unreal Engine 5.

---

## Signal Flow

```
Input WAV → Noise Gate → Compressor → Low Shelf EQ → Limiter → Output WAV
```

Each stage processes the output of the previous one sample by sample, modelling a typical gain-staging chain used in game audio and music production.

---

## Stages

**Noise Gate** — Silences any sample below a user-defined threshold. Models hard gating behaviour used to eliminate low-level noise or bleed between signals.

**Compressor** — Reduces dynamic range of samples exceeding a threshold, applying a user-defined ratio. Implements the standard gain reduction formula: `threshold + (input - threshold) / ratio`.

**Low Shelf EQ** — Applies a flat gain boost or cut using the dB-to-linear conversion `pow(10.0, gainDb / 20.0)`. Currently a simplified gain model — biquad filter implementation planned.

**Limiter** — Hard clips at a user-defined ceiling, handling both positive and negative signal boundaries. Models a brick-wall limiter used to prevent clipping at the output stage.

**Output** — Writes the processed sample buffer back to a WAV file using libsndfile, preserving the original sample rate, channel count, and format.

---

## Dependencies

- [libsndfile](http://libsndfile.github.io/libsndfile/) for WAV file reading and writing

---

## Building and Running

Requires a C++17 compatible compiler and libsndfile installed and linked.

**Using Visual Studio:** Open the solution file, ensure libsndfile is linked in project properties, build with Ctrl+B, run with Ctrl+F5.

**Using g++:**
```bash
g++ -std=c++17 main.cpp signal_chain.cpp audio_io.cpp -o signal_chain -lsndfile
./signal_chain
```

---

## Usage

Run the program and enter when prompted:

```
Input WAV file path     — full path to the source file
Output WAV file path    — full path for the processed output
Gate threshold          — 0.0 to 1.0, samples below this are silenced
Compressor threshold    — 0.0 to 1.0, compression kicks in above this
Compressor ratio        — e.g. 4.0 for 4:1 compression
EQ gain (dB)            — positive for boost, negative for cut
EQ frequency (Hz)       — reference frequency for the shelf
Limiter threshold       — 0.0 to 1.0, hard ceiling for output samples
```

**Recommended starting values for subtle processing:**
```
Gate threshold:       0.001
Compressor threshold: 0.8
Compressor ratio:     2.0
EQ gain:              0.0
EQ frequency:         1000.0
Limiter threshold:    0.95
```

---

## Input Validation

- Compressor ratio must be greater than 0 (prevents division by zero)
- EQ frequency must be greater than 0

---

## Roadmap

- Biquad filter implementation to replace simplified EQ gain model
- Attack and release times for the noise gate and compressor
- Peak analysis reporting — input and output peak levels in dB
- Multi-band processing

---

## Context

This project is part of a broader self-directed study in C++ and DSP, working toward a Schroeder reverb algorithm implemented in C++ and integrated with Unreal Engine 5's native audio component system. Room dimensions will feed Sabine's formula to calculate physically-based reverb parameters dynamically.

---

## Author

**Parth Rane** — Technical Sound Designer  
[Portfolio](https://parthraneaudio.github.io/) · [LinkedIn](https://uk.linkedin.com/in/parthraneprofile) · [YouTube](https://www.youtube.com/@ParthRaneAudio) · [GitHub](https://github.com/ParthRaneAudio)
