#include "interactive_instrument.hpp"
#include "qinstrument.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>

InteractiveInstrument::InteractiveInstrument(const Track & track) {
	trackobj = track;
	std::list<MIDIEvent>::const_iterator itend = trackobj.end();
	intmax_t tickspbeat = track.getTicksPerBeat();
	intmax_t temptempo = 500000;//for later because if nothing specified then 500000
	intmax_t tickt;
	realTime = 0.0;

	for (std::list<MIDIEvent>::const_iterator it2 = trackobj.begin(); it2 != itend; it2++) {
		if (it2->isTempoEvent()) {
			temptempo = it2->asTempoEvent().getTempo();
		}
		tickt = it2->getTickTime();
		realTime = ((tickt*temptempo) / (1000000.0 * tickspbeat)); //realTime = ((tickt*temptempo) / (1000000.0 * tickspbeat));
		midivect.push_back(std::make_pair(*it2, realTime));
	}
	/*
	for (unsigned int count1 = 0; count1 < midivect.size(); count1++) {
		if ((midivect[count1].first.isNoteEvent())) {

		}//end if noteevent
	}
	*/
}
//HAS NOT BEEN MODIFIED FOR MILESTONE 2 YET - need to pass more
double InteractiveInstrument::calcEt(double tiVal) {

	double scale = 0.25;
	double etVal;
	double S = 0.8;
	double t0 = 0.0;
	double t1 = atkTime;
	double t2 = atkTime + decTime;
	//t3 must be changed
	double t3 = NoteDur;
	double t4 = t3 + relTime;
	//NoteDur = t3;

	if (t0 <= tiVal && tiVal <= t1) {//tested
		etVal = ((1.0 / t1) * tiVal);
	}
	else if (t1 < tiVal && tiVal <= t2) {//tested
		etVal = 1.0 - (tiVal - t1);
	}
	else if (t2 < tiVal && tiVal <= t3) {//tested
		etVal = S;
	}
	else if (t3 < tiVal && tiVal <= t4) {//test shows they equal the same however test fails???
		etVal = 0.8 - (0.8 / (t4 - t3)) * (tiVal - t3);
	}
	else {//tested
		etVal = 0.0;
	}
	return etVal;
}

double InteractiveInstrument::freqNoteConv(int8_t noteIndex) {
	int8_t noteI = noteIndex;
	int8_t octave = noteI % 12;
	double f = 0.0;
	//the given frequencies are the standards for those notes in HZ.  so if we want to inrease
	//or decrease our octave we want noteNum%12 because there are 0-11 notes in the standard octave
	if (octave == 0) {
		f = 261.63;
	}
	else if (octave == 1) {
		f = 277.18;
	}
	else if (octave == 2) {
		f = 293.66;
	}
	else if (octave == 3) {
		f = 311.13;
	}
	else if (octave == 4) {
		f = 329.63;
	}
	else if (octave == 5) {
		f = 349.63;
	}
	else if (octave == 6) {
		f = 369.994;
	}
	else if (octave == 7) {
		f = 392.0;
	}
	else if (octave == 8) {
		f = 415.305;
	}
	else if (octave == 9) {
		f = 440.0;
	}
	else if (octave == 10) {
		f = 466.164;
	}
	else {
		f = 493.88;
	}
	//***********************************************
	for (int8_t i = noteI; i > 71; i = i - 12) {
		f = f * 2;
	}
	for (int8_t i = noteI; i < 60; i = i + 12) {
		f = f / 2;
	}
	return f;
}

bool InteractiveInstrument::halted() {
	if (midivect[midivect.size() - 1].first.isEndTrackEvent()) {
		return (currenttime > midivect[midivect.size() - 1].second);
	}
	else {
		return false;
	}
}

//WILL NEED TO BE CHANGED TO ACCOUNT FOR NEW E(T) AND FUNCTION N
double InteractiveInstrument::sample(double deltaT) {
	
	//naming variables inside function because i dont need them anywhere else
	double totalSignalOut = 0.0;
	//now that we have parsed through the events, we have all note events left so they will always have a velocity
	for (unsigned int count1 = 0; count1 < midivect.size(); count1++) {
		if ((midivect[count1].first.isNoteEvent())) {//isnotevent()
			if (midivect[count1].first.asNoteEvent().getNoteOn())//why does this not think the note is on???
			{
				//WALKER SAID THERE IS A REAL NOTE OFF EVENT NEED TO ADD SOMETHING
				for (unsigned int counter1 = 0; counter1 < midivect.size(); counter1++) {
					if (!midivect[counter1].first.asNoteEvent().getNoteOn()) {
						if (midivect[count1].first.asNoteEvent().getNoteNumber() == midivect[counter1].first.asNoteEvent()
							.getNoteNumber()) {
							NoteDur = midivect[counter1].second - midivect[count1].second;
						}
					}
				}
				//NEED TO CHANGE FROM 0.25 TO AN ACTUAL CALCULATED NOTE TIME
				if ((currenttime >= midivect[count1].second) && (currenttime < (midivect[count1].second + (NoteDur + relTime)))) {//+reltime
					ti = currenttime - midivect[count1].second;
					//CHANGE VI TO SLOT?
					Vi = velTime;//midivect[count1].first.asNoteEvent().getNoteVelocity();
					//std::cout << "velTime: " << atkTime << std::endl;
					noteNum = midivect[count1].first.asNoteEvent().getNoteNumber();
					Fi = freqNoteConv(noteNum);//tested
					Et = calcEt(ti);//tested
					ni = functionN();
					/*
					std::cout << "Vi :" << velTime << std::endl;
					std::cout << "Atk :" << atkTime << std::endl;
					std::cout << "Dec :" << decTime << std::endl;
					std::cout << "Rel :" << relTime << std::endl;
					std::cout << "Fi: " << Fi << std::endl;
					std::cout << "ti: " << ti << std::endl;
					*/

					//-
					signalOut = (Vi * Et * ni);
					//std::cout << "Vi: " << Vi << std::endl;
					//std::cout << "Et: " << Et << std::endl;
					//std::cout << "ni: " << ni << std::endl;
					totalSignalOut = totalSignalOut + signalOut;
				}
			}
		}
	}

	currenttime = currenttime + deltaT;
	return totalSignalOut;//abs()
}


//FUNCTIONS NOT OPERATING CORRECTLY
void InteractiveInstrument::enableFirstHarmonic(bool value) {
	if (value) {
		harm1 = true;
		std::cout << "Interactive Instrument Harm1 Set To True" << std::endl;
	}
	else {
		harm1 = false;
		std::cout << "Interactive Instrument Harm1 Set To False" << std::endl;
	}
	
}


void InteractiveInstrument::enableSecondHarmonic(bool value) {
	
	if (value) {
		harm2 = true;
		std::cout << "Interactive Instrument Harm2 Set To True" << std::endl;
	}
	else {
		harm2 = false;
		std::cout << "Interactive Instrument Harm2 Set To False" << std::endl;
	}
	
}

//VALUE THAT IS READ IN FROM THE GUI??
void InteractiveInstrument::setVelocity(double value) {
	velTime = value;
	//std::cout << "Read in: " << value << std::endl;
	//std::cout << "velTime: " << velTime << std::endl;
}

//GUI VAL
void InteractiveInstrument::setAttackTime(double value) {
	atkTime = value;
}

//GUI VAL
void InteractiveInstrument::setDecayTime(double value) {
	decTime = value;
}

//GUI VAL
void InteractiveInstrument::setReleaseTime(double value) {
	relTime = value;
}

//just clear the sum of the notes currently stored???
void InteractiveInstrument::reset() {

}

//function n - NOT READING HARM1 AND HARM2 CORRECTLY???
double InteractiveInstrument::functionN() {
	//none
	
	//if ti is neg why mult? sin always return pos?
	if (harm1 == false && harm2 == false) {
		n = sin(2.0 * M_PI*Fi*ti);
		//std::cout << "Interactive Inst. Both off" << std::endl;
	}
	//1 and not 2
	else if (harm1 == true && harm2 == false) {
		n = (1.0 / 2.0)*(sin(2.0 * M_PI*Fi*ti) + sin(2.0 * M_PI*2.0*Fi*ti));
		//std::cout << "n: " << n << std:: endl;
		//std::cout << "Fi: " << Fi << std::endl;
		//std::cout << "ti: " << ti << std::endl;
		//std::cout << "Pi: " << M_PI << std::endl;
		//std::cout << "Interactive Inst. 1 on" << std::endl;
		//std::cout << "Should SHOW" << std::endl;
	}
	//2 and not 1
	else if (harm1 == false && harm2 == true) {
		n = (1.0 / 2.0)*(sin(2.0 * M_PI*Fi*ti) + sin(2.0 * M_PI* 3.0 * Fi *ti));
		//std::cout << "Interactive Inst. 2 on" << std::endl;
	}
	//both
	else {
		n = (1.0 / 3.0)*(sin(2.0 * M_PI*Fi*ti) + sin(2.0 * M_PI* 2.0 * Fi *ti) + sin(2.0 * M_PI* 3.0 * Fi *ti));
		//std::cout << "Interactive Inst. Both on" << std::endl;
		//std::cout << "n: " << n << std::endl;
	}

	return n;
}
