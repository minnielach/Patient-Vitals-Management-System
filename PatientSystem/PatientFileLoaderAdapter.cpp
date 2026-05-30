#include "PatientFileLoaderAdapter.h"

// constructor stores the file name to be used to load patients and their data
PatientFileLoaderAdapter:: PatientFileLoaderAdapter(const std:: string& fileName) : _fileName(fileName){

}

void PatientFileLoaderAdapter:: initialiseConnection() {
    // not required when using a loader
}

void PatientFileLoaderAdapter:: loadPatients(std::vector<Patient*>& patientIn) {

    // use the PatientFileLoader to load the patients from the file
    std:: vector<Patient*> loadThePatients = _fileLoader.loadPatientFile(_fileName);

    // add the loaded patients into vector that is used by PatientManagementSystem
    for (Patient* patient: loadThePatients) {
        patientIn.push_back(patient);
    }
}

void PatientFileLoaderAdapter:: closeConnection() {
    // not required when using a loader
}