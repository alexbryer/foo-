#include "track.hpp"

// TODO

//Track Class
//Track Constructor 
Track::Track(intmax_t ticks_per_beat) {
	tickspbeat = ticks_per_beat;
}

intmax_t Track::getTicksPerBeat() const {
	return tickspbeat;
}
//returns the iterator defined in private of class
Track::ConstIteratorType Track::begin() const {
	return midilist.begin();
}

/** Get iterator to end of event sequence. */
Track::ConstIteratorType Track::end() const {
	//for (ConstIteratorType iterator = midilist.begin(), end = midilist.end(); iterator != end; ++iterator) {
	//	
	//}
	return midilist.end();
}

void Track::addEndEvent(intmax_t tick_time) {
	EndTrackEvent e = EndTrackEvent();
	MIDIEvent tempEE = MIDIEvent(e, tick_time);
	midilist.push_back(tempEE);
}

void Track::addTempoEvent(intmax_t tempo, intmax_t tick_time) {
	TempoEvent e = TempoEvent(tempo);
	MIDIEvent tempTE = MIDIEvent(e, tick_time);
	midilist.push_back(tempTE);
}

void Track::addNoteEvent(uint8_t code, uint8_t data1, uint8_t data2, intmax_t tick_time)
{
	bool eventONOF;
	//need other vars read into out constructor
	if (code == 9 && data2 != 0) {
		eventONOF = true;
	}
	else {
		eventONOF = false;
	}
	NoteEvent e = NoteEvent(eventONOF, data1, data2);
	MIDIEvent midiE = MIDIEvent(e, tick_time);
	midilist.push_back(midiE);

}