
#include "biquadEq.h"
#include <cmath>

void calculateLowShelf(BiquadFilter& filter, double gainDb, double frequency, double sampleRate)
{
    constexpr double PI{ 3.14159265358979323846 };
    double A = pow(10.0, gainDb / 40.0);
    double w0 = 2.0 * PI * frequency / sampleRate;
    double cosw0 = cos(w0);
    double sinw0 = sin(w0);
    double alpha = sinw0 / 2.0 * sqrt((A + 1.0 / A) * (1.0 / 0.707 - 1.0) + 2.0);

    double b0 = A * ((A + 1) - (A - 1) * cosw0 + 2 * sqrt(A) * alpha);
    double b1 = 2 * A * ((A - 1) - (A + 1) * cosw0);
    double b2 = A * ((A + 1) - (A - 1) * cosw0 - 2 * sqrt(A) * alpha);
    double a0 = (A + 1) + (A - 1) * cosw0 + 2 * sqrt(A) * alpha;
    double a1 = -2 * ((A - 1) + (A + 1) * cosw0);
    double a2 = (A + 1) + (A - 1) * cosw0 - 2 * sqrt(A) * alpha;

    // Normalise by a0 then store in the filter struct
    filter.b0 = b0 / a0;
    filter.b1 = b1 / a0;
    filter.b2 = b2 / a0;
    filter.a1 = a1 / a0;
    filter.a2 = a2 / a0;

    // Initialise state variables to zero
    filter.x1 = filter.x2 = 0.0;
    filter.y1 = filter.y2 = 0.0;

}

double processSample(BiquadFilter& filter, double input)
{
    double output = filter.b0 * input
        + filter.b1 * filter.x1
        + filter.b2 * filter.x2
        - filter.a1 * filter.y1
        - filter.a2 * filter.y2;

    // Update state
    filter.x2 = filter.x1;
    filter.x1 = input;
    filter.y2 = filter.y1;
    filter.y1 = output;

    return output;
}

