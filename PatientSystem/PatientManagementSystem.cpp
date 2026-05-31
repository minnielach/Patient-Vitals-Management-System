#include "PatientManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"

#include "PatientFileLoaderAdapter.h"
#include "PatientLoaderComposite.h"

#include "AlertLevelStrategy.h"

using namespace std;


PatientManagementSystem::PatientManagementSystem() :
	_hospitalAlertSystem(std::make_unique<HospitalAlertSystemFacade>()),
	_gpNotificationSystem(std::make_unique<GPNotificationSystemFacade>())
{
	// create the composite loader
	PatientLoaderComposite* patientLoaderComposite = new PatientLoaderComposite();
	// add the database loader first
	patientLoaderComposite->addLoader(std::make_unique<PatientDatabaseLoader>());
	// add the file loader second 
	patientLoaderComposite->addLoader(std::make_unique<PatientFileLoaderAdapter>("patients.txt"));
	
	// store the composite loader as the system's one patient loader
	_patientDatabaseLoader.reset(patientLoaderComposite);
	_patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
	_patientDatabaseLoader->closeConnection();

	// clear patient memory
	for (Patient* p : _patients) {
		delete p;
	}
}

void PatientManagementSystem::init()
{
	_patientDatabaseLoader->loadPatients(_patients);
	for (Patient* p : _patients) {
		_patientLookup[p->uid()] = p;
	}

	for (Patient* p : _patients) {
		// TODO: do any processing you need here
	}
}

void PatientManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		cin >> option;

		// handle basic errors
		if (cin.bad()) {
			cin.clear();
			cin.ignore();
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printPatients();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		}
	}
}

void PatientManagementSystem::addVitalsRecord()
{
	cout << "Patients" << endl;
	printPatients();
	cout << endl;
	cout << "Enter the patient ID to declare vitals for > ";
	
	string pid { "" };
	cin >> pid;
	if (_patientLookup.count(pid)) {
		float bodyTemperature;
		int bloodPressure;
		int heartRate;
		int respitoryRate;

		cout << "enter body temperature: ";
		cin >> bodyTemperature;
		cout << "enter blood pressure: ";
		cin >> bloodPressure;
		cout << "enter heart rate: ";
		cin >> heartRate;
		cout << "enter respitory rate: ";
		cin >> respitoryRate;

		Vitals* v = new Vitals(bodyTemperature, bloodPressure, heartRate, respitoryRate);
		_patientLookup[pid]->addVitals(v);
		calculateAlertLevel(_patientLookup[pid], v);
	}
	else {
		cout << "Patient not found" << endl;
	}
}

void PatientManagementSystem:: calculateAlertLevel(Patient* patient, const Vitals* vitals){
	std:: unique_ptr<AlertLevelStrategy> strategy;
	
	// if patient's diagnosis is Cordyceps Brain Infection then use the necessary strategy to calculate
	if (patient->primaryDiagnosis() == Diagnosis:: CORDYCEPS_BRAIN_INFECTION){
		strategy = std:: make_unique<CordycepsAlertStrategy>();
	}

	// if patient's diagnosis is Kerpal's Syndrome then use the necessary strategy to calculate
	if (patient->primaryDiagnosis() == Diagnosis:: KEPRALS_SYNDROME){
		strategy = std:: make_unique<KepralsAlertStrategy>();
	}

	// if patient's diagnosis is Andromeda Strain then use select the strategy to use to calculate
	if (patient->primaryDiagnosis() == Diagnosis:: ANDROMEDA_STRAIN){
		strategy = std:: make_unique<AndromedaAlertStrategy>();
	}

	// if a strategy is selected, calculate and set the alert level
	if (strategy != nullptr) {
		AlertLevel alertLevel = strategy->calculate(*patient, *vitals);
		patient->setAlertLevel(alertLevel);
	}
}

void PatientManagementSystem::printWelcomeMessage() const
{
	cout << "WELCOME TO HEALTHCO 3000" << endl;
	cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
	cout << endl << "Select an option:" << endl;
	cout << "1. List patients" << endl;
	cout << "2. Add vitals record" << endl;
	cout << "3. Quit" << endl;
	cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
	for (Patient* p : _patients) {
		std::cout << *p << std::endl;
	}
}
