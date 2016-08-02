/************************************************************************************************************
 Kalman.h -
 MAJ 02/07/2015
 christoph guillermet / karistouf@yahoo.fr /
 from: https://malcolmmielle.wordpress.com/2015/04/29/kalman-filter/
 ************************************************************************************************************/

#ifndef Kalman_h
#define Kalman_h


class Kalman {

public :
/*
* Need to tweak value of sensor and process noise
* arguments :
* process noise covariance
* measurement noise covariance
* estimation error covariance */
    Kalman();
    void setFactors(double q, double r, double p);
    void init(double x);
    void setProcessNoiseCovariance(double i);
    void setMeasurementNoiseCovariance(double i);
    void setEstimatiomErrorCovariance(double i);
    double kalmanUpdate(double measurement);
    void reset();

private :
    double _q; //process noise covariance
    double _q_init;
    double _r; //measurement noise covariance
    double _r_init;
    double _x; //value
    double _p; //estimation error covariance
    double _p_init;
    double _k; //kalman gain

};

#endif

