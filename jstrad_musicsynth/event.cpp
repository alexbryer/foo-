#include "event.hpp"
#include <typeinfo>

// TODO
//TempoEvent Constructor
TempoEvent::TempoEvent(intmax_t t) {
	tempTime = t;
}

//we need a union for the events?
intmax_t TempoEvent::getTempo() const {
	return tempTime;
}
//*********************************************
//EndTrackEvent Class Constructor
EndTrackEvent::EndTrackEvent() {

}
//**********************************************
//NoteEvent Class Constructor
NoteEvent::NoteEvent(bool on, int8_t notenum, int8_t notevelocity) {
	noteOF = on;
	noteMIDInum = notenum;
	notevel = notevelocity;
}

bool NoteEvent::getNoteOn() {//is this wrong?
	return noteOF;
}

int8_t NoteEvent::getNoteNumber() const {
	return noteMIDInum;
}

int8_t NoteEvent::getNoteVelocity() const {
	return notevel;
}
//***********************************************
//MIDIEvent Class
MIDIEvent::MIDIEvent(TempoEvent e, intmax_t ticktime) {
	tickT = ticktime;
	event.tempoEvent_ = e;
	eventType = tempoEvent;
}
MIDIEvent::MIDIEvent(EndTrackEvent e, intmax_t ticktime) {
	tickT = ticktime;
	event.endTrackEvent_ = e;
	eventType = endTrackEvent;
}
MIDIEvent::MIDIEvent(NoteEvent e, intmax_t ticktime) {
	tickT = ticktime;
	event.noteEvent_ = e;
	eventType = noteEvent;
}
//is runtime an issue for this code?
bool MIDIEvent::isTempoEvent() const {
	return eventType == tempoEvent;
}

bool MIDIEvent::isEndTrackEvent() const {
	return eventType == endTrackEvent;
}

bool MIDIEvent::isNoteEvent() const {
	return eventType == noteEvent;
}

intmax_t MIDIEvent::getTickTime() const {
	return tickT;
}
//need to still check if (isTempoEvent())
TempoEvent MIDIEvent::asTempoEvent() const {
	return event.tempoEvent_;
}
//need to still check if (isNoteEvent())
NoteEvent MIDIEvent::asNoteEvent() const {
	return event.noteEvent_;
}