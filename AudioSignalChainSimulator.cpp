// AudioSignalChainSimulator.cpp 
// Signal Flow: Input → Noise Gate → Compressor → EQ → Limiter → Output Report
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sndfile.h>
#include "signal_chain.h"
#include "audio_io.h"

int main()
{
	//Asking the user for input and output file paths
	std::string inputFilePath; // User input for the audio file path
	std::cout << "Enter the path to the audio file: " << "\n";
	std::getline(std::cin >> std::ws, inputFilePath);

	std::string outputFilePath; // User input for the output audio file path
	std::cout << "Enter the path for the output audio file: " << "\n";
	std::getline(std::cin >> std::ws, outputFilePath);


	//Asking the user for signal processing parameters
	double gateThreshold_User{}; // User input for the noise gate threshold
	std::cout << "Enter the gate threshold: " << "\n";
	std::cin >> gateThreshold_User;

	double compressorThreshold_User{}; // User input for the compressor threshold
	std::cout << "Enter the compressor threshold: " << "\n";
	std::cin >> compressorThreshold_User;

	double compressorRatio_User{}; // User input for the compressor ratio
	std::cout << "Enter the compressor ratio: " << "\n";
	std::cin >> compressorRatio_User;
	if (compressorRatio_User <= 0.0)
	{
		std::cout << "Invalid compressor ratio. Please enter a value greater than 0." << "\n";
		return 1; // Exit the program with an error code
	}

	double eqGain_User{}; // User input for the EQ gain
	std::cout << "Enter the EQ gain in dB (3.0 for boost, -3.0 for cut): " << "\n";
	std::cin >> eqGain_User;

	double eqFrequency_User{}; // User input for the EQ frequency
	std::cout << "Enter the EQ frequency in Hz: " << "\n";
	std::cin >> eqFrequency_User;
	if (eqFrequency_User <= 0.0)
	{
		std::cout << "Invalid EQ frequency. Please enter a value greater than 0." << "\n";
		return 1; // Exit the program with an error code
	}

	double limiterThreshold_User{}; // User input for the limiter threshold
	std::cout << "Enter the limiter threshold: " << "\n";
	std::cin >> limiterThreshold_User;

	//Loading WAV file
	SF_INFO fileInfo{};
	std::vector<double> buffer;

	if (!loadWav(inputFilePath, buffer, fileInfo))
	{
		std::cout << "Failed to load file, Exiting." << "\n"; 
		return 1;
	}

	std::cout << "Format: " << fileInfo.format << "\n";
	std::cout << "Sample rate: " << fileInfo.samplerate << "\n";
	std::cout << "Channels: " << fileInfo.channels << "\n";

	// Process buffer through signal chain
	std::cout << "Processing " << buffer.size() << " samples..." << "\n";
	processBuffer(buffer, gateThreshold_User, compressorThreshold_User, compressorRatio_User, eqGain_User, eqFrequency_User, limiterThreshold_User, fileInfo.samplerate);

	// Save output WAV
	if (!saveWav(outputFilePath, buffer, fileInfo))
	{
		std::cout << "Failed to save file.\n";
		return 1;
	}

	std::cout << "Done. Output written to: " << outputFilePath << "\n";

	return 0;
}


  