#include "elepass.h"
//=========================================================================
//
//                            Element classes
//
//=========================================================================
//=========================================================================
//                           electric elements
//=========================================================================
//--------------------------------DRIFT------------------------------------
DRIFT::DRIFT( double l)
{
    L = l;
}
//-------------------------------DRIFT-Pass--------------------------------
void DRIFT::Pass (vec &x)
{
    double ips= 1.0/sqrt( BETA2*(x(dE_)+1.0/BETA2)*(x(dE_)+1.0/BETA2)
                          -1.0/BETAGAMMA2 -x(px_)*x(px_) -x(pz_)*x(pz_)  );
    x(x_) += x(px_)*ips *L;
    x(z_) += x(pz_)*ips *L;
    x(vt_) += BETA2*(x(dE_)+1/BETA2)*ips *L;
    x(vt_) -= L;
}
//---------------------------------eBEND-----------------------------------
eBEND::eBEND ( double l, double angle)
{
    L=l; ANGLE=angle; RHO=l/angle;
    Nint = 80;
}
//-------------------------------eBEND-Pass--------------------------------
void eBEND::Pass (vec &x)
{
    double ds = L/(double)Nint;
    vec xTemp(8), kg1(8), kg2(8), kg3(8), kg4(8);
    for (size_t j=0;j<Nint;j++){
        kg1 = dH_eBEND(x,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg1[i];
        kg2 = dH_eBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg2[i];
        kg3 = dH_eBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ ds*kg3[i];
        kg4 = dH_eBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            x[i] += (kg1[i]+2.0*kg2[i]+2.0*kg3[i]+kg4[i])*ds/8.0;
    }
    x(vt_) -= L;
}
vec dH_eBEND(vec x, double rho)
{
    double iRHO=1.0/rho;
    vec dH = zeros<vec>(8);
    double hs = 1.0+x(x_)*iRHO;
    double phi= log(hs);
    double dummy = x[dE_]*BETA2 +1.0 -phi*BETA2;
    double ps = sqrt( dummy*dummy/BETA2 -1.0/BETAGAMMA2  -x(px_)*x(px_) -x(pz_)*x(pz_)  );
    double ips= 1.0/ps;
    dH(x_) = x(px_)*hs*ips;
    dH(z_) = x(pz_)*hs*ips;
    dH(vt_) = dummy*hs*ips;
    dH(px_) = ( (x[dE_]-phi)*(2.0-BETA2-BETA2*x[dE_]-BETA2*phi) -x(px_)*x(px_) -x(pz_)*x(pz_))*ips*iRHO;

    vec Lambda(3);
    Lambda[0] = -0.5*BETAGAMMA*EDM*dummy/iRHO/hs;
    Lambda[1] = -x[pz_]*BETA2*GAMMA*( MDM + 1.0/(1.0+GAMMA*dummy) )*iRHO/hs;
    Lambda[2] = -ps*iRHO/hs*(1.0-1.0/GAMMA)*(1.0-1.0/GAMMA)*(1.0+GAMMA)*(x[dE_]-phi)/(1.0+GAMMA*dummy);
    dH(xi_) = Lambda[1] - tan(x[zeta_]) *( Lambda[2]*cos(x[xi_]) + Lambda[0]*sin(x[xi_]) );
    dH(zeta_) = Lambda[2]*sin(x[xi_]) - Lambda[0]*cos(x[xi_]);
    return dH;
}
//---------------------------------eQUAD-----------------------------------
eQUAD::eQUAD (double l, double K1)
{
    L=l; K1=K1;
    Nint = 20;
}
//-------------------------------eQUAD-Pass--------------------------------
void eQUAD::Pass (vec &x)
{
    double ds = L/(double)Nint;
    vec xTemp(8), kg1(8), kg2(8), kg3(8), kg4(8);
    for (size_t j=0;j<Nint;j++){
        kg1 = dH_eQUAD(x,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg1[i];
        kg2 = dH_eQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg2[i];
        kg3 = dH_eQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ ds*kg3[i];
        kg4 = dH_eQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            x[i] += (kg1[i]+2.0*kg2[i]+2.0*kg3[i]+kg4[i])*ds/8.0;
    }
    x(vt_) -= L;
}
vec dH_eQUAD(vec x, double K1)
{
    vec dH = zeros<vec>(8);
    double phi= 0.5*K1*( x(x_)*x(x_) - x(z_)*x(z_) );
    double p0 = x(dE_) +1.0/BETA2 -phi;
    double ps = sqrt( BETA2*p0*p0 -1.0/BETAGAMMA2  -x(px_)*x(px_) -x(pz_)*x(pz_)  );
    double ips= 1.0/ps;
    dH(x_) = x(px_)*ips;
    dH(z_) = x(pz_)*ips;
    dH(vt_) = BETA2*p0*ips;
    dH(px_) = -K1*x(x_)*BETA2*p0*ips;
    dH(pz_) =  K1*x(z_)*BETA2*p0*ips;

    vec Lambda(3);
    phi = x[dE_]*BETA2 +1.0 -phi*BETA2;//dummy variable for fast track
    Lambda[0] = BETAGAMMA*K1*( -0.5*x[x_]*EDM*phi + ps*x[z_]*BETA*( MDM+1.0/(1.0+GAMMA*phi) )  );
    Lambda[1] = -BETA2*GAMMA*K1*( x[pz_]*x[x_] + x[px_]*x[z_]  )*( MDM+1.0/(1.0+GAMMA*phi) );
    Lambda[2] = BETAGAMMA*K1*( 0.5*x[z_]*EDM*phi + ps*x[x_]*BETA*( MDM+1.0/(1.0+GAMMA*phi) )  );
    dH(xi_) = Lambda[1] - tan(x[zeta_]) *( Lambda[2]*cos(x[xi_]) + Lambda[0]*sin(x[xi_]) );
    dH(zeta_) = Lambda[2]*sin(x[xi_]) - Lambda[0]*cos(x[xi_]);
    return dH;
}
//=========================================================================
//                           magnetic elements
//=========================================================================
//--------------------------------mBEND------------------------------------
//---------------------------mBEND-Constructor-----------------------------
mBEND::mBEND ( double l, double angle)
{
    L=l; ANGLE=angle; RHO=l/angle;
    Nint = 100;
}
//-------------------------------mBEND-Pass--------------------------------
void mBEND::Pass (vec &x)
{
    double ds = L/(double)Nint;
    vec xTemp(8), kg1(8), kg2(8), kg3(8), kg4(8);
    for (size_t j=0;j<Nint;j++){
        kg1 = dH_mBEND(x,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg1[i];
        kg2 = dH_mBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg2[i];
        kg3 = dH_mBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ ds*kg3[i];
        kg4 = dH_mBEND(xTemp,RHO);
        for (size_t i=0;i<8;i++)
            x[i] += (kg1[i]+2.0*kg2[i]+2.0*kg3[i]+kg4[i])*ds/8.0;
    }
    x(vt_) -= L;
}
vec dH_mBEND(vec x, double rho)
{
    vec dH = zeros<vec>(8);
    double ips= 1.0/sqrt( BETA2*(x(dE_)+1.0/BETA2)*(x(dE_)+1.0/BETA2)
                          -1.0/BETAGAMMA2 -x(px_)*x(px_) -x(pz_)*x(pz_)  );
    double iRHO = 1/rho;
    double hs = 1.0+x(x_)*iRHO;
    dH(x_) = x(px_)*hs*ips;
    dH(z_) = x(pz_)*hs*ips;
    dH(vt_) = (BETA2*x(dE_)+1.0)*hs*ips;
    dH(px_) = -(1.0+x(x_)*iRHO-1.0/ips)*iRHO;
    return dH;
}
//---------------------------------mQUAD-----------------------------------
//---------------------------mQUAD-constructor-----------------------------
mQUAD::mQUAD ( double l, double K1)
{
    L=l; K1=K1;
    Nint = 100;
}
//-------------------------------mQUAD-Pass--------------------------------
void mQUAD::Pass (vec &x)
{
    double ds = L/(double)Nint;
    vec xTemp(8), kg1(8), kg2(8), kg3(8), kg4(8);
    for (size_t j=0;j<Nint;j++){
        kg1 = dH_mQUAD(x,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg1[i];
        kg2 = dH_mQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ 0.5*ds*kg2[i];
        kg3 = dH_mQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            xTemp[i]=x[i]+ ds*kg3[i];
        kg4 = dH_mQUAD(xTemp,K1);
        for (size_t i=0;i<8;i++)
            x[i] += (kg1[i]+2.0*kg2[i]+2.0*kg3[i]+kg4[i])*ds/8.0;
    }
    x(vt_) -= L;
}
vec dH_mQUAD(vec x, double K1)
{
    vec dH = zeros<vec>(8);
    double ips= 1.0/sqrt( BETA2*(x(dE_)+1.0/BETA2)*(x(dE_)+1.0/BETA2)
                          -1.0/BETAGAMMA2 -x(px_)*x(px_) -x(pz_)*x(pz_)  );
    dH(x_) = x(px_)*ips;
    dH(z_) = x(pz_)*ips;
    dH(vt_) = (BETA2*x(dE_)+1.0)*ips;
    dH(px_) = -K1*x(x_);
    dH(pz_) =  K1*x(z_);
    return dH;
}
//=========================================================================
//                              RF elements
//=========================================================================
//--------------------------------RFCAV------------------------------------
//---------------------------RFCAV-constructor-----------------------------
RFCAV::RFCAV (double vRF, double fRF, double phase)
{
    VRF = vRF; // [Voltage]
    WRF = 2*datum::pi*fRF;
    PHASE = phase;
}
//-------------------------------RFCAV-Pass--------------------------------
void RFCAV::Pass (vec &x)
{
    double t = x(vt_)/(BETA*datum::c_0);
    double delta = -VRF*1.0E-6/(BETA2*magicENERGY)*sin( WRF*t + PHASE);
    x(dE_) += delta;
}
//=========================================================================
//
//                               Line  class
//
//=========================================================================
Line::Line ()
{
    Ncell = 0;
    Length = 0;
}

void Line::Update ()
{
    size_t i;
    double sPointer = 0.;
    for (i = 0; i < Cell.size (); i++)
    {
        Cell[i]->S = sPointer;
        sPointer = Cell[i]->L + sPointer;
    }
    Ncell = Cell.size ();
    Length = sPointer;
}

void Line::Append (Element * elem)
{
    Cell.push_back (elem);
    Update ();
}
