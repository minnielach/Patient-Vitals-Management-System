#include "AlertLevelStrategy.h"

#include "Patient.h"
#include "Vitals.h"

// Cordyceps Brain Infection uses respritory rate to calculate
AlertLevel CordycepsAlertStrategy:: calculate(const Patient& patient, const Vitals& vitals) const {

    if (vitals.RR() > 40){
        return AlertLevel:: Red;
    }

    if (vitals.RR() > 30){
        return AlertLevel:: Orange;
    }

    if (vitals.RR() > 20){
        return AlertLevel:: Yellow;
    }

    return AlertLevel:: Green;
    
}

// Kepral's Syndrome uses heart rate and age to calculate
AlertLevel KepralsAlertStrategy:: calculate(const Patient& patient, const Vitals& vitals) const {

    if (patient.age() < 12 && vitals.HR() > 120){
        return AlertLevel:: Red;
    }

    if (patient.age() >= 12 && vitals.HR() > 100){
        return AlertLevel:: Red;
    }

    return AlertLevel:: Green;
    
}

// Andromeda Strain uses blood pressure to calculate
AlertLevel AndromedaAlertStrategy:: calculate(const Patient& patient, const Vitals& vitals) const {

    if (vitals.BP() > 140){
        return AlertLevel:: Red;
    }

    if (vitals.BP() > 130){
        return AlertLevel:: Orange;
    }

    if (vitals.BP() > 110){
        return AlertLevel:: Yellow;
    }

    return AlertLevel:: Green;
    
}