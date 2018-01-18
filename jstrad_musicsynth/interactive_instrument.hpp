/** \file The InteractiveInstrument Module
 */
#ifndef INTERACTIVE_INSTRUMENT_HPP
#define INTERACTIVE_INSTRUMENT_HPP

#include "event.hpp"
#include "track.hpp"
#include "qinstrument.hpp"

/** The interactive instrument.
 */
class InteractiveInstrument{
public:

  /** No default constructor. A InteractiveInstrument must have an associated 
   * track. 
   */
  InteractiveInstrument() = delete;

  /** Cannot be copied. 
   */
  InteractiveInstrument(const InteractiveInstrument & ) = delete;

  /** Cannot be assigned.
   */
  InteractiveInstrument & operator=(const InteractiveInstrument & ) = delete;

  /** Construct a Interactive Instrument using the specified track.
   * \param track the track to read events from. 
   */
  InteractiveInstrument(const Track & track);

  /** Returns true of the InteractiveInstrument has stopped processing events.
   * This can occu e.g. if all events have been consumed or a EndTrackEvent
   * has been processed.
   */
  bool halted();

  /** Enables the addition of a first harmonic to the instrument notes 
   * \param value true if enabled, false if not
   */
  void enableFirstHarmonic(bool value);

  /** Enables the addition of a second harmonic to the instrument notes 
   * \param value true if enabled, false if not
   */
  void enableSecondHarmonic(bool value);

  /** Sets the velocity of the notes.
   * \param value the new velocity
   */
  void setVelocity(double value);

  /** Sets the attack time of the envelope function.
   * \param value the new attack time
   */
  void setAttackTime(double value);

  /** Sets the decay time of the envelope function.
   * \param value the new decay time
   */
  void setDecayTime(double value);

  /** Sets the release time of the envelope function.
   * \param value the new release time
   */
  void setReleaseTime(double value);

  /** Resets the instrument to a default state.*/
  void reset();
  
  /** Return the sample after the (real) time increment. Samples the 
   * instrument based on its state after processing all events prior 
   * to this time.
   * \param deltaT the time increment in seconds.
   */
  double sample(double deltaT);
  double freqNoteConv(int8_t noteIndex);
  double calcEt(double Etval);
  double functionN();

private:

	// TODO
	Track trackobj;
	//NoteEvent noteEv;
	std::vector<std::pair<MIDIEvent, double>> midivect;
	double realTime = 0.0;
	double Et = 0.0;
	double signalOut;
	double Vi = 0.0;
	double Fi = 0.0;
	double ti = 0.0;
	//new
	double velTime = 0.0;
	double atkTime = 0.0;
	double decTime = 0.0;
	double relTime = 0.0;
	
	double currenttime = 0.0;
	int8_t noteNum = 0;
	double NoteDur = 0.0;
	bool harm1;
	bool harm2;
	double ni = 0.0;
	double n = 0.0;
	double saveOnFreq;
	double saveOffFreq;

	/*
	static constexpr int NUM_NOTES = 128;

	struct noteInfo {
		double realStart;
		double realEnd;
		int noteNum;
	}; note[NUM_NOTES];
	*/

};


#endif
