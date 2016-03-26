#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>
//=========================================================================
//                           Global  constants 
//=========================================================================
//const double light_speed =  299792458;
//--------------------------spin-parameters--------------------------------
const double MDM = 0.00115965218;  // anormalous magnetic momentum
const double EDM = 7.3E-17;  // electric momentum g-factor
//-------------------------------------------------------------------------
const double C1 = 1.0 / (2.0 - pow(2.0, 1.0/3.0));
const double C0 = 1.0 - 2.0*C1;
//-----------relativistic parameters for electron magic energy-------------
const double GAMMA=29.3603438609;
const double BETA=0.99941980533;
const double BETA2=BETA*BETA;
const double BETAGAMMA=GAMMA*BETA; // beta_0 gamma_0
const double BETAGAMMA2=BETAGAMMA*BETAGAMMA; // beta_0 gamma_0
const double magicENERGY = 15.0031037101; //MeV
//-------------------------state-vector-index------------------------------
enum x_index {x_=0, px_=1, z_= 2, pz_=3, vt_=4, dE_=5};
#endif
                
