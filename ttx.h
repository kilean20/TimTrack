#include "elepass.h"

void ttx(Line & TTX)
{
    const double ang = 2*datum::pi/4;
    const double quadK = 30.0;
    const double edgeAngle = 0.506145483078356;

    const double lBend = 0.4;
    const double lQuad = 0.1;
    const double lDrift = 0.5;

  Element * temp;
  for(int i=0;i<2;i++){
      temp = new DRIFT(lDrift);
      TTX.Append(temp);
      temp = new mBEND_EDGE(edgeAngle, lBend/ang);
      TTX.Append(temp);
      temp = new mBEND(lBend, ang);
      TTX.Append(temp);
      temp = new mBEND_EDGE(edgeAngle, lBend/ang);
      TTX.Append(temp);
      temp = new DRIFT(lDrift);
      TTX.Append(temp);
      temp = new mQUAD(lQuad, quadK);
      TTX.Append(temp);
      temp = new DRIFT(lDrift);
      TTX.Append(temp);
      temp = new mBEND_EDGE(edgeAngle, lBend/ang);
      TTX.Append(temp);
      temp = new mBEND(lBend, ang);
      TTX.Append(temp);
      temp = new mBEND_EDGE(edgeAngle, lBend/ang);
      TTX.Append(temp);
  }
}
