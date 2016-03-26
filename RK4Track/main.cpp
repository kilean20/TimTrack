#include <iostream>
#include <vector>
#include "efodo.h"
#include "elepass.h"

int main()
{
    cout.precision(15);
    //Define the ring
    Line FODO;    efodo(FODO);    FODO.Update();

    //add cavity
    double revFreq = (BETA*datum::c_0)/FODO.Length;
    cout << "length=" << FODO.Length << endl;
    cout << "revFreq=" << revFreq << endl;

    Element * temp;
    temp = new RFCAV(1000.0, 3.0*revFreq, 0.0);
    FODO.Append(temp);

    size_t nParticle=6, nTurn=2048;
    vec x(10);
    mat data(10,nParticle*nTurn ); data.zeros();

    for(size_t n=0;n<nParticle;n++){
        x.zeros();
        //initialization
        x(dE_)=((double)n+1.0)*1.0e-3;
        //x(x_)=((double)n+1.0)*1.0e-4;
        //x(z_)=((double)n+1.0)*1.0e-4;
        for(size_t i=0;i<nTurn;i++){
            for(size_t j=0;j!=FODO.Ncell;j++) FODO.Cell[j]->Pass(x);
            data.col(n*nTurn+i) = x;
        }
    }

    data=data.st();
    mat xData = data.cols(x_,px_);
    mat zData = data.cols(z_,pz_);
    mat sData = data.cols(vt_,dE_);
    xData.save("xDataRK4",raw_ascii);
    zData.save("zDataRK4",raw_ascii);
    sData.save("sDataRK4",raw_ascii);

    return 0;
}

