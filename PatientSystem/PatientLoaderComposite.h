#pragma once

#include <vector>
#include <memory>

#include "AbstractPatientDatabaseLoader.h"

// Composite class which allows mutiple loaders to be used as one
class PatientLoaderComposite : public AbstractPatientDatabaseLoader {
public:

// adds a loader to the composite
 void addLoader(std:: unique_ptr<AbstractPatientDatabaseLoader> loader);

// functions used by AbstractPatientDatabaseLoader and overriden here
    void initialiseConnection() override;
    void loadPatients(std::vector<Patient*>& patientIn) override;
    void closeConnection() override;

private:
// stores the loaders used by the composite
std:: vector<std:: unique_ptr<AbstractPatientDatabaseLoader> > _loaders;

};