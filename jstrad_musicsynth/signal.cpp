#include "signal.hpp"
#include <cmath>
// TODO
//Signals Class
//Signal Class Constructor 
Signal::Signal(unsigned int sampleRate) {
	sampR = sampleRate;
}

unsigned int Signal::getSampleRate() {
	return sampR;
}

void Signal::normalize() {
	maxNumber = 0.0;
	minNumber = 0.0;
	reScale = 0.0;
	//check.. . suggested by professor in piazza
	//int16_t intmax = std::numeric_limits<int16_t>::max();
	//int16_t intmin = std::numeric_limits<int16_t>::min();
	//find largest val
	for (unsigned int i = 0; i < sampVect.size(); i++) {
		if (sampVect[i] > maxNumber) {
			maxNumber = sampVect[i];
		}
	}
	for (unsigned int i = 0; i < sampVect.size(); i++) {
		if (sampVect[i] < minNumber) {
			minNumber = sampVect[i];
		}
	}
	//scale
	if (std::abs(minNumber) > maxNumber && std::abs(minNumber) > 32767.0) {
		reScale = (32767.0 / std::abs(minNumber));
		for (unsigned int i = 0; i < sampVect.size(); i++) {
			sampVect[i] = (sampVect[i] * reScale);
		}
	}
	else if (std::abs(minNumber) < maxNumber && maxNumber > 32767.0) {
		reScale = (32767.0 / maxNumber);
		for (unsigned int i = 0; i < sampVect.size(); i++) {
			sampVect[i] = (sampVect[i] * reScale);
		}
	}


}

void Signal::push_back(double value) {
	sampVect.push_back(value);
}

std::size_t Signal::size() {
	return sampVect.size();
}

double Signal::operator[](std::size_t index) {
	return sampVect[index];
}

