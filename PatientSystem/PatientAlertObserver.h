#pragma once

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"

class Patient;
class HospitalAlertSystemFacade;
class GPNotificationSystemFacade;

// base observer class for patient alert notifications
class PatientAlertObserver {
    public:

    //virtual deconstructor to allow the object to be cleaned up 
    virtual ~PatientAlertObserver() = default;

    // this is called when a patient need to notify the observers 
    virtual void update(Patient* patient) = 0;
};  

// observer class for hospital alerts
class HospitalAlertObserver: public PatientAlertObserver {
    public:
    // stores the hospital alert system that will send the alert
    HospitalAlertObserver(HospitalAlertSystemFacade* hospitalAlertSystem);

    // sends a hospital alert for the patient when updated
    void update(Patient* patient) override;

    private:
    HospitalAlertSystemFacade* _hospitalAlertSystem;
};

// observer class for gp notifications
class GPAlertObserver : public PatientAlertObserver {
    public:
    // stores the gp notifcation system that will send a notifcation
    GPAlertObserver(GPNotificationSystemFacade* gpNotificationSystem);

    // sends a gp notification for the patient when updated
    void update(Patient* patient) override;

    private:
    GPNotificationSystemFacade* _gpNotificationSystem;
};