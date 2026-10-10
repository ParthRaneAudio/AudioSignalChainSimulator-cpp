// Signal_chain.cpp
// All the function defs for main go here

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sndfile.h>
#include "signal_chain.h"
#include "audio_io.h"

// Function definitions for the signal processing chain

// Apply a noise gate to the signal
double applyNoiseGate(double signal, double gateThreshold)
{
	if (signal < gateThreshold)
	{
		return 0.0; // Signal is below the gate threshold, so it's muted
	}
	return signal; // Signal is above the gate threshold, so it's passed through
}

// Apply a compressor to the signal
double applyCompressor(double signal, double threshold, double ratio)
{
	if (signal > threshold)
	{
		return threshold + (signal - threshold) / ratio; // Compress the signal
	}
	return signal; // Signal is not above the threshold, so it's passed through
}

// Apply a low-shelf EQ to the signal
double applyLowShelfEQ(double signal, double gainDb, double frequency)
{
	return signal * pow(10.0, gainDb / referenceDb);
}

// Apply a limiter to the signal
double applyLimiter(double signal, double limitThreshold)
{
	if (signal > limitThreshold)
	{
		return limitThreshold; // Limit the signal to the threshold
	}
	if (signal < -limitThreshold)
	{
		return -limitThreshold; // Limit the signal to the negative threshold
	}
	return signal; // Signal is within the limit thresholds, so it's passed through
}

// Convert linear signal level to dB
double linearToDb(double linear)
{
	if (linear > 0.0)
	{
		return referenceDb * log10(abs(linear)); // Convert linear to dB
	}
	else
	{
		std::cout << "Invalid input for linear to dB conversion." << "\n"; // Return negative infinity for non-positive values
		return -std::numeric_limits<double>::infinity();
	}
}

//Stage wise output report function
void printStageReport(std::string_view stageName, double inputLevel, double outputLevel)
{ 
	std::cout << "[ " << stageName << " ]" << "\n" << "------------------------" << "\n";
	std::cout << "Input: " << inputLevel << "\n";
	std::cout << "Output: " << outputLevel << "\n";
	std::cout << "Change: " << outputLevel - inputLevel << "\n" << "------------------------" << "\n";
}

// Final output report function
void printFinalReport(double originalSignal, double finalSignal, bool gated, bool compressed, bool limited)
{
	std::cout << "=== FINAL OUTPUT REPORT ===" << "\n";
	std::cout << "Original Signal: " << originalSignal << "\n";
	std::cout << "Final Signal: " << finalSignal << "\n";
	if (gated)
	{
		std::cout << "Gate Triggered: Yes" << "\n";
	}
	else
	{
		std::cout << "Gate Triggered: No" << "\n";
	}
	if (compressed)
	{
		std::cout << "Compressed: Yes" << "\n";
	}
	else
	{
		std::cout << "Compressed: No" << "\n";
	}
	if (limited)
	{
		std::cout << "Limited: Yes" << "\n";
	}
	else
	{
		std::cout << "Limited: No" << "\n";
	}

}