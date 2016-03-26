#include <iostream>
#include <vector>
#include "elepass.h"
#include "fodo.h"

int main()
{
    cout.precision(15);
    //Define the ring
    Line FODO;    fodo(FODO);    FODO.Update();

    //add cavity
    double revFreq = (BETA*datum::c_0)/FODO.Length;
    cout << "length=" << FODO.Length << endl;
    cout << "revFreq=" << revFreq << endl;

    Element * temp;
    temp = new RFCAV(1000.0, 3.0*revFreq, 0.0);
    //FODO.Append(temp);

    size_t nParticle=1, nTurn=2048;
    vec x(10);
    mat data(10,nParticle*nTurn ); data.zeros();

    for(size_t n=0;n<nParticle;n++){
        x.zeros();
        //initialization
        //x(dE_)=((double)n+1.0)*1.0e-3;
        //x(x_)=((double)n+1.0)*1.0e-4;
        //x(z_)=((double)n+1.0)*1.0e-4;
        for(size_t i=0;i<nTurn;i++){
            for(size_t j=0;j!=FODO.Ncell;j++) FODO.Cell[j]->Pass(x);
            x[vt_]-= FODO.Length;
            data.col(n*nTurn+i) = x;
        }
    }

    data=data.st();
    mat xData = data.cols(x_,px_);
    mat zData = data.cols(z_,pz_);
    mat sData = data.cols(vt_,dE_);
    xData.save("xDataMyS",raw_ascii);
    zData.save("zDataMyS",raw_ascii);
    sData.save("sDataMyS",raw_ascii);



    return 0;
}

