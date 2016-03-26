#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "efodo.h"
#include "line.h"
#include "global.h"
//#include <armadillo>


using namespace std;


int main(int argc, char *argv[])
{
    cout.precision(15);
    //Define the ring
    LINE FODO;    efodo(FODO);

    unsigned nTurn;
    stringstream(argv[3]) >> nTurn;

    unsigned nSkip;
    stringstream(argv[4]) >> nSkip;

    vector<double> x(10); std::fill(x.begin(), x.end(), 0.0);
    stringstream(argv[2]) >>  x[dE_];
    cout << "deltaE = " << x[dE_] << endl;

    cout << "LastElemType = " << FODO.Cell[FODO.Ncell-1].Type << endl;
    cout << "beforeWrf = " << FODO.Cell[FODO.Ncell-1].RFcav.Wrf << endl;
    FODO.Cell[FODO.Ncell-1].RFcav.Wrf*= 1.0-x[dE_]/3.0;
    cout << "afterWrf = " << FODO.Cell[FODO.Ncell-1].RFcav.Wrf << endl;
    cout << "DesignLegnth = " << FODO.Length << endl;
    const double cSpeed=299792458.0;
    cout << "RFLegnth = " << 6.0*M_PI*BETA*cSpeed/FODO.Cell[FODO.Ncell-1].RFcav.Wrf << endl;


    ofstream xData,zData,sData,spinData;
    stringstream ss;
    ss<<"xData_dE"<<stringstream(argv[1]).str()<<".dat";
    xData.open(ss.str().c_str());

    ss.clear();ss.str("");
    ss<<"zData_dE"<<stringstream(argv[1]).str()<<".dat";
    zData.open(ss.str().c_str());

    ss.clear();ss.str("");
    ss<<"sData_dE"<<stringstream(argv[1]).str()<<".dat";
    sData.open(ss.str().c_str());

    ss.clear();ss.str("");
    ss<<"spinData_dE"<<stringstream(argv[1]).str()<<".dat";
    spinData.open(ss.str().c_str());


    for(unsigned i=0;i<nTurn;i++){
        if (i%nSkip==0)
        {
            xData << x[x_] << " " << x[px_] << endl;
            zData << x[z_] << " " << x[pz_] << endl;
            sData << x[vt_] << " " << x[dE_] << endl;
            spinData << x[Sx_] << " " << x[Ss_] << endl;
        }
        for(unsigned j=0;j!=FODO.Ncell;j++) FODO.Cell[j].Pass(x);
    }
    zData << x[z_] << " " << x[pz_] << endl;
    sData << x[vt_] << " " << x[dE_] << endl;
    spinData << x[Sx_] << " " << x[Ss_] << endl;

    return 0;
}
