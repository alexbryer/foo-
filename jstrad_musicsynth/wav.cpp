#include "wav.hpp"
#include <iostream>
// TODO

bool write_wav(Signal & sound, const std::string &filename) {
	//some will be const because they wont change...variables w/ equations will
	int8_t   ChunkID[4] = { 'R', 'I', 'F', 'F' };        // "RIFF"
	int32_t  ChunkSize;// 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
	int8_t   Format[4] = { 'W', 'A', 'V', 'E' };         // "WAVE"
	int8_t   Subchunk1ID[4] = { 'f', 'm', 't', ' ' };   // "fmt "
	int32_t  Subchunk1Size = 16;    // 16
	int16_t  AudioFormat = 1;      // 1
	int16_t  NumChannels = 1;
	int32_t  SampleRate = 44100;       // samples per second, 44100
	int32_t  ByteRate;         // SampleRate * NumChannels * BitsPerSample/8
	int16_t  BlockAlign;       // NumChannels * BitsPerSample/8
	int16_t  BitsPerSample = 16;    // 8 bits = 8, 16 bits = 16
	int8_t   Subchunk2ID[4] = { 'd', 'a', 't', 'a' };   // "data"
	int32_t  Subchunk2Size;    // NumSamples * NumChannels * BitsPerSample/8
	int32_t  NumSamples = 0;// test
							// Mono = 1
	int16_t  myData;						//int16_t  Data[NUMSAMPLES]; // the Pulse Code Modulated data
											//.
	Signal soundobj;
	soundobj = sound;
	NumSamples = (int32_t)(soundobj.size());//(uint32_t)(soundobj.getSampleRate() * (soundobj.size()));
	Subchunk2Size = NumSamples * NumChannels * BitsPerSample / 8;
	ChunkSize = 4 + (8 + Subchunk1Size) + (8 + Subchunk2Size);
	ByteRate = SampleRate * NumChannels * BitsPerSample / 8;
	BlockAlign = NumChannels * BitsPerSample / 8;

	std::ofstream outstream(filename, std::ios::binary);
	//*****************************************************************

	for (int i = 0; i < 4; i++) {
		outstream.write(reinterpret_cast<std::fstream::char_type*>(&ChunkID[i]), sizeof ChunkID[i]);
	}

	//CHUNKSIZE
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&ChunkSize), sizeof ChunkSize);

	//Format
	for (int i = 0; i < 4; i++) {
		outstream.write(reinterpret_cast<std::fstream::char_type*>(&Format[i]), sizeof Format[i]);
	}
	//fmt - subchunk1ID
	for (int i = 0; i < 4; i++) {
		outstream.write(reinterpret_cast<std::fstream::char_type*>(&Subchunk1ID[i]), sizeof Subchunk1ID[i]);
	}
	//subchunk1size
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&Subchunk1Size), sizeof Subchunk1Size);
	//audioformat
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&AudioFormat), sizeof AudioFormat);
	//numchannels
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&NumChannels), sizeof NumChannels);
	//samplerate
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&SampleRate), sizeof SampleRate);
	//byterate
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&ByteRate), sizeof ByteRate);
	//blockallign
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&BlockAlign), sizeof BlockAlign);
	//bitspersample
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&BitsPerSample), sizeof BitsPerSample);
	//subchunk2ID
	for (int i = 0; i < 4; i++) {
		outstream.write(reinterpret_cast<std::fstream::char_type*>(&Subchunk2ID[i]), sizeof Subchunk2ID[i]);
	}
	//subchunk2size
	outstream.write(reinterpret_cast<std::fstream::char_type*>(&Subchunk2Size), sizeof Subchunk2Size);
	//*********************************

	for (unsigned int i = 0; i < soundobj.size(); i++) {
		//std::cout << soundobj.size();
		myData = (int16_t)soundobj[i];
		outstream.write(reinterpret_cast<std::fstream::char_type*>(&myData), sizeof(int16_t));
	}

	outstream.close();
	if (!outstream) {
		return false;
	}
	return true;
}