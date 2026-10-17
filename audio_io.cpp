#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sndfile.h>
#include "signal_chain.h"
#include "audio_io.h"
#include <cstddef>
#include "biquadEq.h"


bool loadWav(const std::string& filePath, std::vector<double>& buffer, SF_INFO& fileInfo)
{
    // Open the file
    SNDFILE* file = sf_open(filePath.c_str(), SFM_READ, &fileInfo);
    if (!file)
    {
        std::cout << "Error opening file: " << sf_strerror(file) << "\n";
        return false;
    }

    // Calculate total samples
    sf_count_t totalSamples = fileInfo.frames * fileInfo.channels;

    // Resize buffer to fit all samples
    buffer.resize(totalSamples);

    // Read all samples into buffer — once only
    sf_read_double(file, buffer.data(), totalSamples);

    // Close the file
    sf_close(file);

    // Confirm load
    std::cout << "Loaded: " << filePath << "\n";
    std::cout << "Sample rate: " << fileInfo.samplerate << "\n";
    std::cout << "Channels: " << fileInfo.channels << "\n";
    std::cout << "Frames: " << fileInfo.frames << "\n";

    return true;
}

void processBuffer(std::vector<double>& buffer, double gateThreshold, double compThreshold, double compRatio, double eqGain, double eqFreq, double limitThreshold, int sampleRate)
{
    // Create and calculate the filter once before the loop
    BiquadFilter eqFilter;
    calculateLowShelf(eqFilter, eqGain, eqFreq, sampleRate);

    for (std::size_t i{ 0 }; i < buffer.size(); ++i)
    {
        buffer[i] = applyNoiseGate(buffer[i], gateThreshold);
        buffer[i] = applyCompressor(buffer[i], compThreshold, compRatio);
        buffer[i] = processSample(eqFilter, buffer[i]);  // replaces applyLowShelfEQ
        buffer[i] = applyLimiter(buffer[i], limitThreshold);
    }
}

bool saveWav(const std::string& filePath, std::vector<double>& buffer, SF_INFO& fileInfo)
{
	// Writing samples  
	SNDFILE* file = sf_open(filePath.c_str(), SFM_WRITE, &fileInfo);
	if (!file)
	{
		std::cout << "Error Opening File: " << sf_strerror(file) << "\n";
		return false;
	}
	sf_write_double(file, buffer.data(), buffer.size());

	// Always close
	sf_close(file);
	std::cout << "Saved: " << filePath << "\n";

	return true;
}