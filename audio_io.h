#ifndef AUDIO_IO_H
#define AUDIO_IO_H

#include <string>
#include <vector>
#include <sndfile.h>
#include "biquadEq.h"

bool loadWav(const std::string& filePath, std::vector<double>& buffer, SF_INFO& fileInfo);
bool saveWav(const std::string& filePath, std::vector<double>& buffer, SF_INFO& fileInfo);
void processBuffer(std::vector<double>& buffer, double gateThreshold, double compThreshold, double compRatio, double eqGain, double eqFreq, double limitThreshold, int sampleRate);

#endif // AUDIO_IO_H