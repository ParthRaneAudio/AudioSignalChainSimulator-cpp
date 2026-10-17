#ifndef BIQUADEQ_H
#define BIQUADEQ_H

struct BiquadFilter
{
    double b0, b1, b2, a1, a2;  // coefficients
    double x1, x2;               // input state
    double y1, y2;               // output state
};

void calculateLowShelf(BiquadFilter& filter, double gainDb, double frequency, double sampleRate);

double processSample(BiquadFilter& filter, double input);


#endif // BIQUAD_H

