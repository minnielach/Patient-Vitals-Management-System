#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

using namespace std;


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};

    std::ifstream inFile(file);
    if (inFile.is_open()) {
        std::string patientRecord; 

        // read the file one line at a time and each line resembles a patient 
        while (std:: getline(inFile, patientRecord)) {
            // if the line is empty, skip to the next line
            if (patientRecord.empty()) {
                continue;
            }

            // converts the string into a stream to be able to split the record 
            std:: stringstream patientRecordStream(patientRecord);

            // create the variables 
            std:: string id;
            std:: string name;
            std:: string birthdate;
            std:: string diagnosis; 
            std:: string vitals;

            // splitting the patient records into the variables and using | as a seprator 
            std:: getline(patientRecordStream, id, '|');
            std:: getline(patientRecordStream, name, '|');
            std:: getline(patientRecordStream, birthdate, '|');
            std:: getline(patientRecordStream, diagnosis, '|');
            std:: getline(patientRecordStream, vitals, '|');

            // enables a split in the name to store it as first name and last name
            std:: stringstream nameStream(name);

            // create the variables 
            std:: string lastName;
            std:: string firstName;

            // splitting the name into the variables and using , as a seprator 
            std:: getline(nameStream, lastName, ',');
            std:: getline(nameStream, firstName, ',');

            // convert birthday string into a date object using istringstream to split and formate
            std:: tm birthday{};
            std:: istringstream birthdayStream(birthdate);
            birthdayStream >> std:: get_time(&birthday, "%d-%m-%Y");


            // create the patient object with the firstName, name and birthday 
            Patient* patient = new Patient(firstName, lastName, birthday);
            // add the diagnosis to this patient
            patient -> addDiagnosis(diagnosis);

            // if the patient has vitals data, split and add each vitals to the record
            if(!vitals.empty()) {
                std:: stringstream vitalData(vitals);
                std:: string vitalRecord;

                // if more than one vitals are recorded, they are seperated by semicolons
                while(std:: getline(vitalData, vitalRecord, ';')) {
                    // skip if empty
                    if (vitalRecord.empty()) {
                        continue;
                    }

                    // create the variables
                    float bt;
                    int bp;
                    int hr;
                    int rr;

                    // create variables for the comma so it is easily identifyable
                    char comma1;
                    char comma2;
                    char comma3;

                    // split the one vital record 
                    std:: stringstream vitalsStream(vitalRecord);
                    
                    // read the vital record and set them directly to the number vaiables
                    if (vitalsStream >> bt >> comma1 >> bp >> comma2 >> hr >> comma3 >> rr) {

                        // create the vitals object with the body temp, blood pressure, heart rate and respirtory rate 
                        Vitals* vital = new Vitals(bt, bp, hr, rr);
                        // add the vitals to this patient
                        patient->addVitals(vital);

                    }



                }

            }

            // add the patient and their data to the vector
            patients.push_back(patient);

        }
    }

    return patients;
}
