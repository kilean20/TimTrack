#include "elepass.h"
//=========================================================================
//
//                            Element classes
//
//=========================================================================
//--------------------------------DRIFT------------------------------------
DRIFT::DRIFT( double l)
{
    L = l;
}
//-------------------------------DRIFT-Pass--------------------------------
void DRIFT::Pass (vec &x)
{
    double ips= 1.0/sqrt( BETA2*(x[dE_]+1.0/BETA2)*(x[dE_]+1.0/BETA2)
                          -1.0/BETAGAMMA2 -x[px_]*x[px_] -x[pz_]*x[pz_]  );
    x[x_] += x[px_]*ips *L;
    x[z_] += x[pz_]*ips *L;
    x[vt_] += BETA2*(x[dE_]+1/BETA2)*ips *L;
    //x[vt_] -= L;
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
    const double ds = L/(double)Nint;
    const double ds0 = ds*C0;
    const double ds1 = ds*C1;
    double iRHO=1.0/RHO;

    double onePdelta2=(x[dE_]+1.0)*(x[dE_]+1.0);
    double f = sqrt( onePdelta2 - x[pz_]*x[pz_] ) ;
    double g;

    //=============================
    //  2nd order drift-kick-drift
    //=============================
//    for (int j=0;j<Nint;j++)
//    {
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*ds*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*ds*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*ds*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*ds*iRHO+g) - RHO;
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* ds;
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*ds*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*ds*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*ds*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*ds*iRHO+g) - RHO;
//    }
    //=============================
    //  4th order drift-kick-drift
    //=============================
//    for (size_t j=0;j<Nint;j++)
//    {
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*ds1*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*ds1*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*ds1*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*ds1*iRHO+g) - RHO;
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* ds1;
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*(ds1+ds0)*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*(ds1+ds0)*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*(ds1+ds0)*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*(ds1+ds0)*iRHO+g) - RHO;
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* ds0;
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*(ds1+ds0)*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*(ds1+ds0)*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*(ds1+ds0)*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*(ds1+ds0)*iRHO+g) - RHO;
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* ds1;
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(0.5*ds1*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(0.5*ds1*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(0.5*ds1*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(0.5*ds1*iRHO+g) - RHO;
//    }
    //=============================
    //  2nd order kick-drift-kick
    //=============================
//    for (int j=0;j<Nint;j++)
//    {
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*ds;
//        //drift
//        g = asin(x[px_]/f);
//        x[px_] = f*sin(ds*iRHO+g);
//        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(ds*iRHO+g)-tan(g));
//        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(ds*iRHO+g)-tan(g));
//        x[x_] = (RHO+x[x_]) * cos(g) /cos(ds*iRHO+g) - RHO;
//        //kick
//        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*ds;
//    }
    //=============================
    //  4th order kick-drift-kick
    //=============================
    for (size_t j=0;j<Nint;j++)
    {
        //kick
        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*ds1;
        //drift
        g = asin(x[px_]/f);
        x[px_] = f*sin(ds1*iRHO+g);
        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(ds1*iRHO+g)-tan(g));
        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(ds1*iRHO+g)-tan(g));
        x[x_] = (RHO+x[x_]) * cos(g) /cos(ds1*iRHO+g) - RHO;
        //kick
        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*(ds1+ds0);
        //drift
        g = asin(x[px_]/f);
        x[px_] = f*sin(ds0*iRHO+g);
        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(ds0*iRHO+g)-tan(g));
        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(ds0*iRHO+g)-tan(g));
        x[x_] = (RHO+x[x_]) * cos(g) /cos(ds0*iRHO+g) - RHO;
        //kick
        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*(ds1+ds0);
        //drift
        g = asin(x[px_]/f);
        x[px_] = f*sin(ds1*iRHO+g);
        x[z_] += (RHO + x[x_])/f*x[pz_]*cos(g)*(tan(ds1*iRHO+g)-tan(g));
        x[vt_] += (RHO+x[x_])/f*sqrt(onePdelta2)*cos(g)*(tan(ds1*iRHO+g)-tan(g));
        x[x_] = (RHO+x[x_]) * cos(g) /cos(ds1*iRHO+g) - RHO;
        //kick
        x[px_] -= (iRHO+x[x_]*iRHO*iRHO)* 0.5*ds1;
    }
    //x[vt_] -= L;
}
//---------------------------------mQUAD-----------------------------------
//---------------------------mQUAD-constructor-----------------------------
mQUAD::mQUAD ( double l, double k1)
{
    L=l; K1=k1;
    Nint = 100;
}
//-------------------------------mQUAD-Pass--------------------------------
void mQUAD::Pass (vec &x)
{
    double ds = 0.5*L/(double)Nint;
    const double ds0 = ds*C0;
    const double ds1 = ds*C1;
    double onePdelta2=(x[dE_]+1.0)*(x[dE_]+1.0);
    double iDriftH;
    //=========
    //2nd order
    //=========
//    for (int j=0;j<Nint;j++)
//    {
//        iDriftH = 1/sqrt(onePdelta2 - x[px_]*x[px_] -x[pz_]*x[pz_]); //inverse drift Hamilt.
//        //drift
//        x[x_] += iDriftH * x[px_] * ds;
//        x[z_] += iDriftH * x[pz_] * ds;
//        x[vt_] += iDriftH * sqrt(onePdelta2) * ds;
//        //kick
//        x[px_] += -K1*x[x_] *2.0*ds;
//        x[pz_] +=  K1*x[z_] *2.0*ds;
//        //drift
//        iDriftH = 1/sqrt(onePdelta2 - x[px_]*x[px_] -x[pz_]*x[pz_]); //inverse drift Hamilt.
//        x[x_] += iDriftH * x[px_] * ds;
//        x[z_] += iDriftH * x[pz_] * ds;
//        x[vt_] += iDriftH * sqrt(onePdelta2) * ds;
//    }
    //=========
    //4th order
    //=========
    for (size_t j=0;j<Nint;j++)
    {
        iDriftH = 1/sqrt(onePdelta2 - x[px_]*x[px_] -x[pz_]*x[pz_]); //inverse drift Hamilt.
        //drift
        x[x_] += iDriftH * x[px_] * ds1;
        x[z_] += iDriftH * x[pz_] * ds1;
        x[vt_] += iDriftH * sqrt(onePdelta2) * ds1;
        //kick
        x[px_] += -K1*x[x_] *2.0*ds1;
        x[pz_] +=  K1*x[z_] *2.0*ds1;
        //drift
        iDriftH = 1/sqrt(onePdelta2 - x[px_]*x[px_] -x[pz_]*x[pz_]); //inverse drift Hamilt.
        x[x_] += iDriftH * x[px_] * (ds1+ds0);
        x[z_] += iDriftH * x[pz_] * (ds1+ds0);
        x[vt_] += iDriftH * sqrt(onePdelta2) * (ds1+ds0);
        //kick
        x[px_] += -K1*x[x_] *2.0*ds0;
        x[pz_] +=  K1*x[z_] *2.0*ds0;
        //drift
        iDriftH = 1/sqrt(onePdelta2 - x[px_]*x[px_] -x[pz_]*x[pz_]); //inverse drift Hamilt.
        x[x_] += iDriftH * x[px_] * (ds1+ds0);
        x[z_] += iDriftH * x[pz_] * (ds1+ds0);
        x[vt_] += iDriftH * sqrt(onePdelta2) * (ds1+ds0);
        //kick
        x[px_] += -K1*x[x_] *2.0*ds1;
        x[pz_] +=  K1*x[z_] *2.0*ds1;
        //drift
        x[x_] += iDriftH * x[px_] * ds1;
        x[z_] += iDriftH * x[pz_] * ds1;
        x[vt_] += iDriftH * sqrt(onePdelta2) * ds1;
    }

//    vec xTemp(6), kg1(6), kg2(6), kg3(6), kg4(6);
//    for (int j=0;j<Nint;j++){
//        kg1 = dH_mQUAD(x,K1);
//        for (int i=0;i<6;i++)
//            xTemp[i]=x[i]+ 0.5*ds*kg1[i];
//        kg2 = dH_mQUAD(xTemp,K1);
//        for (int i=0;i<6;i++)
//            xTemp[i]=x[i]+ 0.5*ds*kg2[i];
//        kg3 = dH_mQUAD(xTemp,K1);
//        for (int i=0;i<6;i++)
//            xTemp[i]=x[i]+ ds*kg3[i];
//        kg4 = dH_mQUAD(xTemp,K1);
//        for (int i=0;i<6;i++)
//            x[i] += (kg1[i]+2.0*kg2[i]+2.0*kg3[i]+kg4[i])*ds/6.0;
//    }
    //x[vt_] -= L;
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
    double t = x[vt_]/(BETA*datum::c_0);
    double delta = -VRF*1.0E-6/(BETA2*magicENERGY)*sin( WRF*t + PHASE);
    x[dE_] += delta;
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
