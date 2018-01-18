// TODO: implement your entry point here
#include "qinstrument.hpp"
#include <QApplication>
#include "event.hpp"
#include "midi.hpp"
#include "signal.hpp"
#include "track.hpp"
#include "wav.hpp"

//sounds the same
#include <iostream>
#include <fstream>
#include <string>
//overall velocity for all of the notes 0.0 through 1000.0
//how to add groupings
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QInstrument instrumentDialog;

	instrumentDialog.show();

	return app.exec();
}
