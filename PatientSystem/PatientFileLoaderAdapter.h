#pragma once 

#include <string>
#include <vector>

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

// adapter class which allows PatientFileLoader to be used within the ABstractPatientDatabaseLoader (adapter pattern design)
class PatientFileLoaderAdapter : public AbstractPatientDatabaseLoader {
    public:
    // stores the file name that will be loaded
    PatientFileLoaderAdapter(const std:: string& fileName);

    // functions used by AbstractPatientDatabaseLoader and overriden here
    void initialiseConnection() override;
    void loadPatients(std::vector<Patient*>& patientIn) override;
    void closeConnection() override;

    private:
    // the name of the file to be used
    std::string _fileName;
    // the patient file loader to read the file
    PatientFileLoader _fileLoader;

};
