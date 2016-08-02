/************************************************************************************************************
 Kalman.cpp
 MAJ 02/07/2015
 christoph guillermet / karistouf@yahoo.fr /
 from: https://malcolmmielle.wordpress.com/2015/04/29/kalman-filter/
 ************************************************************************************************************/

#include <Kalman.h>

Kalman::Kalman()
{
}

void Kalman::setFactors(double q, double r, double p)
{
   _q=q;
   _q_init=q;
   _r=r;
   _r_init=0;
   _x=0;
   _p=p;
   _p_init=p;
   _k= (_p / (_p + _r)) ;
}

void Kalman::init(double x)
{ _x = x ;}

void Kalman::setProcessNoiseCovariance(double i)
{ _q = i; _q_init = i;}

void Kalman::setMeasurementNoiseCovariance(double i)
{_r = i; _r_init = i ;}

void Kalman::setEstimatiomErrorCovariance(double i)
{_p = i; _p_init = i ;}

void Kalman::reset()
{_q = _q_init; _r = _r_init ; _p = _p_init;};

double Kalman::kalmanUpdate(double measurement)
{
//prediction update
//omit _x = _x
_p = _p + _q;

//measurement update
_k = _p / (_p + _r);
_x = _x + _k * (measurement - _x);
_p = (1 - _k) * _p;
return _x;
}



