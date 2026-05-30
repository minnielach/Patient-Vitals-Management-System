#include "PatientLoaderComposite.h"

void PatientLoaderComposite:: addLoader(std:: unique_ptr<AbstractPatientDatabaseLoader> loader){
    // add the loader into the list of loaders
    _loaders.push_back(std:: move(loader));
}

void PatientLoaderComposite:: initialiseConnection() {
    // go through each loader and initialise the connection if necessary
    for (const auto& loader : _loaders) {
        loader-> initialiseConnection();
    }
}

void PatientLoaderComposite:: loadPatients(std::vector<Patient*>& patientIn) {

    // go through each loader and load the patients info into the same vector
    for (const auto& loader : _loaders) {
        loader-> loadPatients(patientIn);
    }
}

void PatientLoaderComposite:: closeConnection() {
    // go through each loader and close the connection if necessary
    for (const auto& loader : _loaders) {
        loader-> closeConnection();
    }
}

