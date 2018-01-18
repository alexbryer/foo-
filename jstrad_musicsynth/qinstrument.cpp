#include "qinstrument.hpp"
#include "interactive_instrument.hpp"
#include "track.hpp"
#include "signal.hpp"
#include "midi.hpp"
#include "wav.hpp"

//#include "main.cpp"
//exercise 11

//how to check if pressed or not????
//ischecked() or toggled()???
QInstrument::QInstrument() { //QWidget *parent

	QGridLayout *layout1 = setGridLayout();
	spinnerBox = new QGroupBox("Instrument Parameters", this);
	spinnerBox->setLayout(layout1);

	QGridLayout *layout2 = setMIDILayout();
	midiBox = new QGroupBox("MIDI Input", this);
	midiBox->setLayout(layout2);

	QGridLayout *layout3 = setWAVLayout();
	wavBox = new QGroupBox("WAV Output", this);
	wavBox->setLayout(layout3);

	QGridLayout *layout4 = setSYNTHLayout();
	synthBox = new QGroupBox("", this);
	synthBox->setLayout(layout4);

	//final vertical box
	QVBoxLayout * buildVbox1 = new QVBoxLayout;
	buildVbox1->addWidget(spinnerBox);
	buildVbox1->addWidget(midiBox);
	buildVbox1->addWidget(wavBox);
	buildVbox1->addWidget(synthBox);
	
	//redo
	//try making functions for each box??  getting errors for more than one layout
	this->setLayout(buildVbox1);
}

QInstrument::~QInstrument() {};

QGridLayout *QInstrument::setGridLayout() {
	QGridLayout *layout1 = new QGridLayout;

	harmonic1 = new QRadioButton("Enable First Harmonic");
	harmonic1->setAutoExclusive(false);
	harmonic1->setObjectName("harmonic1");
	layout1->addWidget(harmonic1, 0, 0, 1, 1, Qt::AlignHCenter);

	harmonic2 = new QRadioButton("Enable Second Harmonic");
	harmonic2->setAutoExclusive(false);
	harmonic2->setObjectName("harmonic2");
	layout1->addWidget(harmonic2, 0, 1, 1, 1, Qt::AlignHCenter);

	QLabel *labelVel = new QLabel;
	labelVel->setText("Velocity:");
	layout1->addWidget(labelVel, 1, 0, 1, 1, Qt::AlignLeft);

	velocity = new QDoubleSpinBox;
	velocity->setRange(0.0, 999999999999999999.0);
	velocity->setDecimals(1);
	velocity->setValue(1000.0);
	velocity->setSuffix("     ");
	velocity->setObjectName("velocity");
	layout1->addWidget(velocity, 1, 1, 1, 1, Qt::AlignLeft);

	QLabel *labelAtk = new QLabel;
	labelAtk->setText("Attack Time (s):");
	layout1->addWidget(labelAtk, 2, 0, 1, 1, Qt::AlignLeft);

	attack = new QDoubleSpinBox;
	attack->setRange(0.0, 1.0);
	attack->setDecimals(6);
	attack->setValue(0.062500);
	attack->setSingleStep(0.000005);
	attack->setSuffix("                         ");
	attack->setObjectName("attack");
	layout1->addWidget(attack, 2, 1, 1, 1, Qt::AlignLeft);

	QLabel *labelDec = new QLabel;
	labelDec->setText("Decay Time (s):");
	layout1->addWidget(labelDec, 3, 0, 1, 1, Qt::AlignLeft);

	decay = new QDoubleSpinBox;
	decay->setRange(0.0, 1.0);
	decay->setDecimals(6);
	decay->setValue(0.050000);
	decay->setSingleStep(0.000005);
	decay->setSuffix("                         ");
	decay->setObjectName("decay");
	layout1->addWidget(decay, 3, 1, 1, 1, Qt::AlignLeft);

	QLabel *labelRel = new QLabel;
	labelRel->setText("Release Time (s):");
	layout1->addWidget(labelRel, 4, 0, 1, 1, Qt::AlignLeft);

	release = new QDoubleSpinBox;
	release->setRange(0.0, 1.0);
	release->setDecimals(6);
	release->setValue(0.050000);
	release->setSingleStep(0.000005);
	release->setSuffix("                         ");
	release->setObjectName("release");
	layout1->addWidget(release, 4, 1, 1, 1, Qt::AlignLeft);

	return layout1;
}

QGridLayout *QInstrument::setMIDILayout() {
	QGridLayout *layout2 = new QGridLayout;

	inputpath = new QLineEdit;
	inputpath->setObjectName("inputpath");
	layout2->addWidget(inputpath, 0, 0, 1, 1, Qt::AlignHCenter);

	QPushButton *browse1 = new QPushButton("Browse");
	layout2->addWidget(browse1, 0, 1, 1, 1, Qt::AlignHCenter);
	QObject::connect(browse1, SIGNAL(clicked()), this, SLOT(browseMIDI()));

	return layout2;
}

QGridLayout *QInstrument::setWAVLayout() {
	QGridLayout *layout3 = new QGridLayout;

	outputpath = new QLineEdit;
	outputpath->setObjectName("outputpath");
	layout3->addWidget(outputpath, 0, 0, 1, 1, Qt::AlignHCenter);

	QPushButton *browse2 = new QPushButton("Browse");
	layout3->addWidget(browse2, 0, 1, 1, 1, Qt::AlignHCenter);
	QObject::connect(browse2, SIGNAL(clicked()), this, SLOT(browseWAV()));

	return layout3;
}

QGridLayout *QInstrument::setSYNTHLayout() {
	QGridLayout *layout4 = new QGridLayout;

	synth = new QPushButton("Synthesize");
	synth->setObjectName("synth");
	layout4->addWidget(synth);
	QObject::connect(synth, SIGNAL(clicked()), this, SLOT(synthesize()));

	return layout4;
}
//Slot Functions

void QInstrument::browseMIDI() {
	//qDebug() << "First Browse Button Clicked";
	inFile = QFileDialog::getOpenFileName(
		this, "Open Document", QDir::currentPath(), "MIDI files (*.mid)");//All Files (*.*);; 
	
	//then do a clear of the qline edit and refresh like in the calc example to new filename
	//then maybe argc/argv the string when read in to by synthesized
	inputpath->clear();
	inputpath->setText(inFile);
	//IF NOT SELECTED??????  null or keep previous file
	
}

void QInstrument::browseWAV() {
	//qDebug() << "Second Browse Button Clicked";
	//qDebug() << "File:" << inFile;
	outFile = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath());
	

	outputpath->clear();
	outputpath->setText(outFile);
}


void QInstrument::synthesize() {
	//NEED TO FIX READING IF FILE NOT SELECTED THROUGH BROWSE
	inFile = inputpath->text();
	outFile = outputpath->text();
	if (harmonic1->isChecked()) {
		qDebug() << "Harmonic One Selected - Synth PushButton";
	}
	if (harmonic2->isChecked()) {
		qDebug() << "Harmonic Two Selected - Synth PushButton";
	}
	qDebug() << "Input File Selected: " << inFile;
	qDebug() << "Output Directory:" << outFile;
	qDebug() << "Velocity:" << velocity->value() << ".";
	qDebug() << "Attack Time (s):" << attack->value() << ".";
	qDebug() << "Decay Time (s):" << decay->value() << ".";
	qDebug() << "Release Time (s):" << release->value() << ".";
	qDebug() << "----------------------------";
	//ISSUE HERE**************************************************%^&*&^^&*
	

	returnHarmonic1();
	returnHarmonic2();
	TrackListType inputTracks;
	Signal finalSignals;
	int mycount = 0;
	std::string s;

	//trying to test if the inFile can be parsed
	inputTracks = readMIDIFromFile(returninFile());
	//try if the size of the track list is 0
	if (inputTracks.size() == 0) {
		msg.setText("Unable To Process Data.  Please Check Input. ");
		msg.exec();
	}
	else {

		//inputTracks = readMIDIFromFile(returninFile());

		std::list<Track>::iterator itend = inputTracks.end();
		for (std::list<Track>::iterator itbegin = inputTracks.begin(); itbegin != itend; itbegin++) {
			s = std::to_string(mycount);
			std::string outfileName = returnoutFile() + "-" + s + ".wav";

			//changing to qinst to use interactive instead of other way around

			finalSignals = (synthesizee(*itbegin));
			write_wav(finalSignals, outfileName);//arguments[2]->output file
			std::cout << outfileName << std::endl;/***********************/
			mycount = mycount + 1;
		}
	}//end of else
	
}

//need to make an object of interactive instrument
//pass all values here into the interactive instrument
//then do synthesize again




//attempting to follow same method as before and make small 
//functions to call the values from gui class
double QInstrument::returnVel() {
	return velocity->value();
}

double QInstrument::returnAtk() {
	return attack->value();
}

double QInstrument::returnDec() {
	return decay->value();
}

double QInstrument::returnRel() {
	return release->value();
}

//synth signal should set file names correctly
std::string QInstrument::returninFile() {
	return inFile.toStdString();
}

std::string QInstrument::returnoutFile() {
	return outFile.toStdString();
}

//harmonic issues***********************************************************************$%^&*&^%
bool QInstrument::returnHarmonic1() {
	
	if (harmonic1->isChecked()) {
		qDebug() << "Harmonic 1 Selected In QInstrument Function";
		return true;
	}
	else {
		qDebug() << "Harm 1 Not Selected In QInstrument Function";
		return false;
	}
}

bool QInstrument::returnHarmonic2() {
	if (harmonic2->isChecked()) {
		qDebug() << "Harmonic 2 Selected In QInstrument Function";
		return true;
	}
	else {
		qDebug() << "Harm 2 Not Selected in QInstrument Function";
		return false;
	}
}


Signal QInstrument::synthesizee(Track & track) {
	Signal sigT;
	InteractiveInstrument myTrack(track);

	myTrack.enableFirstHarmonic(harmonic1->isChecked());
	myTrack.enableSecondHarmonic(harmonic2->isChecked());
	myTrack.setVelocity(velocity->value());
	//qDebug() << "Vellllll: " << velocity->value();
	myTrack.setAttackTime(attack->value());
	myTrack.setDecayTime(decay->value());
	myTrack.setReleaseTime(release->value());

	sigT.push_back(myTrack.sample(0.0));
	while (!myTrack.halted()) {
		sigT.push_back(myTrack.sample(1.0 / 44100.0));
	}
	sigT.normalize();
	return sigT;
}














/*
//still need to connect signals and slots
//attempting to build boxes - NEED TEXT FOR FIRST
QHBoxLayout *buildHbox1 = new QHBoxLayout;
QButtonGroup* buttonGroup1 = new QButtonGroup(buildHbox1);
buttonGroup1->addButton(harmonic1);
buttonGroup1->addButton(harmonic2);

QAbstractButton* checked = buttonGroup1->checkedButton();
if (checked)
{
	buttonGroup1->setExclusive(false);
	checked->setChecked(false);
	buttonGroup1->setExclusive(true);
}

*/

