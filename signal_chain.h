//signal_chain.h

#ifndef SIGNAL_CHAIN_H
#define SIGNAL_CHAIN_H
#include <string_view>
#include "biquadEq.h"

//constexpr variables for signal processing
constexpr double maxSignalLevel{ 1.0 };
constexpr double minSignalLevel{ -1.0 };
constexpr double referenceDb{ 20.0 };

//forward declarations of the signal processing functions
double applyNoiseGate(double signal, double gateThreshold);
double applyCompressor(double signal, double threshold, double ratio);
double applyLowShelfEQ(double signal, double gainDb, double frequency);
double applyLimiter(double signal, double limitThreshold);
double linearToDb(double linear);
void printStageReport(std::string_view stageName, double inputLevel, double outputLevel);
void printFinalReport(double originalSignal, double finalSignal, bool gated, bool compressed, bool limited);

#endif // SIGNAL_CHAIN_H