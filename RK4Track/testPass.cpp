
#include <iostream>
#include <armadillo>
#include "elepass.h"

using namespace std;


int main()
{

	//Define the ring
cout.precision(15);


    Line FODO;

    Element * temp;
    temp = new DRIFT(0.2);
    FODO.Append(temp);
    FODO.Append(temp);

    DRIFT testDrift(1.0);
    mBEND testmBend(1.0,0.0000001);
    mQUAD testmQuad(1.0,0.0000001);

    //test
    vec x(8);
    for(int i=0;i<8;i++)
        x(i)=0.0;
    x(px_)=1e-6;
    testDrift.Pass(x);
    cout << x(0) << "\t" << x(1) << "\t" << x(2) << "\t" << x(3) << "\t" << x(4) << "\t" << x(5) << "\t" << x(6) << "\t" << x(7) << endl;
    //test2
    for(int i=0;i<8;i++)
        x(i)=0.0;
    x(px_)=1e-6;
    testmBend.Pass(x);
    cout << x(0) << "\t" << x(1) << "\t" << x(2) << "\t" << x(3) << "\t" << x(4) << "\t" << x(5) << "\t" << x(6) << "\t" << x(7) << endl;
    //test3
    for(int i=0;i<8;i++)
        x(i)=0.0;
    x(px_)=1e-6;
    testmQuad.Pass(x);
    cout << x(0) << "\t" << x(1) << "\t" << x(2) << "\t" << x(3) << "\t" << x(4) << "\t" << x(5) << "\t" << x(6) << "\t" << x(7) << endl;


	return 0;
}

