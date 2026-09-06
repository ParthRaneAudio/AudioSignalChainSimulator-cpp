// AudioSignalChainSimulator.cpp 
// Signal Flow: Input → Noise Gate → Compressor → EQ → Limiter → Output Report
//

#include <iostream>
#include <cmath>
#include "signal_chain.h"
#include <string>

int main()
{
	double inputSignalLevel_User{}; // User input for the input signal level
	std::cout << "Enter the input signal level (between 0.0 and 1.0): " << "\n";
	std::cin >> inputSignalLevel_User;
	if (inputSignalLevel_User > 1.0 || inputSignalLevel_User < 0.0)
	{
		std::cout << "Invalid input signal level. Please enter a value between 0.0 and 1.0." << "\n";
		return 1; // Exit the program with an error code
	}

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

	std::cout << "=== AUDIO SIGNAL CHAIN ===" << "\n"; 

	//Process the signal through the chain
	double signalLevelAfterNoiseGate{ applyNoiseGate(inputSignalLevel_User, gateThreshold_User) };
	printStageReport("Noise Gate", inputSignalLevel_User, signalLevelAfterNoiseGate);
	bool isSignalMuted{ signalLevelAfterNoiseGate == 0.0 };

	double signalLevelAfterCompressor{ applyCompressor(signalLevelAfterNoiseGate, compressorThreshold_User, compressorRatio_User) };
	printStageReport("Compressor", signalLevelAfterNoiseGate, signalLevelAfterCompressor);
	bool isSignalCompressed{ signalLevelAfterCompressor < signalLevelAfterNoiseGate };

	double signalLevelAfterEQ{ applyLowShelfEQ(signalLevelAfterCompressor, eqGain_User, eqFrequency_User) };
	printStageReport("EQ", signalLevelAfterCompressor, signalLevelAfterEQ);

	double signalLevelAfterLimiter{ applyLimiter(signalLevelAfterEQ, limiterThreshold_User) };
	printStageReport("Limiter", signalLevelAfterEQ, signalLevelAfterLimiter);
	bool isSignalLimited{ signalLevelAfterLimiter != signalLevelAfterEQ };

	double inputSignalLevelDb{ linearToDb(inputSignalLevel_User) };
	double finalOutputLevelDb{ linearToDb(signalLevelAfterLimiter) };
	
	// Print the final report
	printFinalReport(inputSignalLevelDb, finalOutputLevelDb, isSignalMuted, isSignalCompressed, isSignalLimited);
	

	return 0;
}


