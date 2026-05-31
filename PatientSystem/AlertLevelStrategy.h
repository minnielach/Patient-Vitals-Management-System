#pragma once 

#include "PatientAlertLevels.h"

class Patient;
class Vitals;

// base class for alert level calculation 
class AlertLevelStrategy {
    public:
    
    //virtual deconstructor to allow the object to be cleaned up 
    virtual ~AlertLevelStrategy() = default;

    // each digagnosis calculates the alert level in its own way
    virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const = 0;

};

// strategy for Cordyceps Brain Infection
class CordycepsAlertStrategy : public AlertLevelStrategy {
    public: 
    AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

// strategy for Kepral's Syndrome
class KepralsAlertStrategy : public AlertLevelStrategy {
    public: 
    AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

// strategy for Andromeda Strain
class AndromedaAlertStrategy : public AlertLevelStrategy {
    public: 
    AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};