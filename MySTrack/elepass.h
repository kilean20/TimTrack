#ifndef ELEPASS_H
#define ELEPASS_H
#include <vector>
#include "global.h"
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <../include/armadillo>
#else
    #include <armadillo>
#endif

//declare of line, element, and pass method
//=========================================================================
//
//                            Element classes
//
//=========================================================================
using namespace std;
using namespace arma;

class Element
{
public:
  size_t Nint;
  double L;
  double S;
  virtual void Pass (vec &x)=0;
};
//=========================================================================
//                               elements
//=========================================================================
//--------------------------------DRIFT------------------------------------
class DRIFT:public Element
{
public:
  DRIFT (double length);
  void Pass (vec &x);  // vec x=(x, px, z, pz, beta0*ct, -delta)
};
//=========================================================================
//                           magnetic elements
//=========================================================================
//--------------------------------mBEND------------------------------------
class mBEND:public Element
{
public:
  mBEND (double l, double angle);
  void Pass (vec &x);
  double ANGLE; double RHO;
};
//---------------------------------mQUAD-----------------------------------
class mQUAD:public Element
{
public:
 mQUAD (double l, double k1);
 void Pass (vec &x);
 double K1;
};
//=========================================================================
//                              RF elements
//=========================================================================
//--------------------------------RFCAV------------------------------------
class RFCAV:public Element
{
public:
  RFCAV (double vRF, double wRF, double phase);
  void Pass (vec &x);
  double VRF, WRF, PHASE;
};
//=========================================================================
//
//                               Line  class
//
//=========================================================================
class Line
{
public:
  Line ();
  void Update ();
  void Append (Element * x);

  vector<Element * > Cell;
  double Length;		//---length of reference orbit
  size_t Ncell;			//---number of elements
};




#endif
