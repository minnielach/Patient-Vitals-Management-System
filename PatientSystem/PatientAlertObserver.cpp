#include "PatientAlertObserver.h"

#include "Patient.h"
#include "HospitalAlertSystemFacade.h"
#include "GPNotificationSystemFacade.h"

// constructor which stores the hospital alert sysem facade and allows the observer to send hopsital alerts when update() is called
HospitalAlertObserver:: HospitalAlertObserver(HospitalAlertSystemFacade* hospitalAlertSystem) : _hospitalAlertSystem(hospitalAlertSystem) {
}

void HospitalAlertObserver:: update(Patient* patient) {
    // use the exisiting hospital facade to send an alert
    _hospitalAlertSystem->sendAlertForPatient(patient);
}

// constructor which stores the gp notification system facade and allows the observer to send gp notifcations when update() is called
GPAlertObserver:: GPAlertObserver(GPNotificationSystemFacade* gpNotificationSystem) :_gpNotificationSystem(gpNotificationSystem) {
}

void GPAlertObserver:: update(Patient* patient) {
    // use the exisiting gp facade to send an alert
    _gpNotificationSystem->sendGPNotificationForPatient(patient);
}
