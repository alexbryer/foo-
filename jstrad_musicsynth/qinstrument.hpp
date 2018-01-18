#ifndef QINSTRUMENT_HPP
#define QINSTRUMENT_HPP
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout> 
#include <QVBoxLayout>
#include <QLayout>
#include <QRadioButton>
#include <QWidget>
#include <iostream>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QDebug>
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include <iostream>

#include "signal.hpp"
#include "track.hpp"
#include "interactive_instrument.hpp"
#include "midi.hpp"




// TODO 
class QRadioButton;

class QInstrument: public QWidget {
	Q_OBJECT

public:
	QInstrument(); //QWidget * parent = 0
	virtual ~QInstrument();
	double returnVel();
	double returnAtk();
	double returnDec();
	double returnRel();

	Signal synthesizee(Track & track);

	std::string returninFile();
	std::string returnoutFile();
	//need to add a harmonic counter function->then have a function for n in
	//instrument to decide which form of function n should be used
	bool returnHarmonic1();
	bool returnHarmonic2();



protected slots:
	void browseMIDI();
	void browseWAV();
	void synthesize();




private:
	//radio buttons
	QRadioButton *harmonic1;
	QRadioButton *harmonic2;
	//double spin boxes
	QDoubleSpinBox *velocity;
	QDoubleSpinBox *attack;
	QDoubleSpinBox *decay;
	QDoubleSpinBox *release;
	//line Edit
	QLineEdit *inputpath;
	QLineEdit *outputpath;
	//push button
	QPushButton *synth;

	QGridLayout *setGridLayout();
	QGridLayout *setMIDILayout();
	QGridLayout *setWAVLayout();
	QGridLayout *setSYNTHLayout();
	QGroupBox *spinnerBox;
	QGroupBox *midiBox;
	QGroupBox *wavBox;
	QGroupBox *synthBox;
	QString inFile;
	QString outFile;
	//attempting to fix harmonic->ischecked() issue
	bool flag1;
	bool flag2;

	QMessageBox msg;

	

	//InteractiveInstrument interA;

	//file dialog buttons
	//QFileDialog *browsein;
	//QFileDialog *browseout;
	//try two vertical boxes in a horizontal box
	
};


#endif
