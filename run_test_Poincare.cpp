#include <iostream>
#include <vector>
#include "efodo.h"
#include "line.h"
#include "global.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <include/armadillo>
#else
    #include <armadillo>
#endif


using namespace arma;


int main()
{
    cout.precision(15);
    //Define the ring
    LINE FODO;    efodo(FODO);    //FODO.Update();

    unsigned nParticle=4, nTurn=2048, nSkip=1;
    vector<double> x(10);
    mat xData(nParticle*nTurn/nSkip,6);
    mat sData(nParticle*nTurn/nSkip,6);
    for(unsigned n=0;n<nParticle;n++){
        std::fill(x.begin(), x.end(), 0.0);
        x[x_]=((double)n+1.0)*2.5e-3;
        for(unsigned i=0;i<nTurn;i++){
            for(unsigned j=0;j<FODO.Ncell;j++) {FODO.Cell[j].Pass(x);}
            if (i%nSkip==0) {
                xData(n*nTurn/nSkip+i/nSkip,0)=x[x_];
                xData(n*nTurn/nSkip+i/nSkip,1)=x[px_];
                sData(n*nTurn/nSkip+i/nSkip,0)=x[vt_];
                sData(n*nTurn/nSkip+i/nSkip,1)=x[dE_];
            }
        }
    }
    xData.save("xDataTim",raw_ascii);
    sData.save("sDataTim",raw_ascii);
    return 0;
}
