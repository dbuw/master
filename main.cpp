#include <iostream>

#include "UnitTest++.h"
#include "test/initialsequencertest.h"
#include "test/repairsequencetest.h"
//#include "test/populationtest.h"
//#include "test/evolvertest.h"
//#include "test/clsddecodertest.h"
//#include "test/chromosomedecodertest.h"
//#include "test/encodingtest.h"
#include "brkga.h"
#include "CLSD/Solution.h"
#include "FileReader/instance.h"
#include "FileReader/instanceToData.h"

using namespace BRKGA;
#define private public
int main()
{

////////////////////////////////////////////////////////////////////////////////
////  READ FILE
////////////////////////////////////////////////////////////////////////////////
  Instance i;
  i.readWinforData("instance_174");

  Data d;

  InstanceToData iConvertD;
  iConvertD.convert(&i,&d);

////////////////////////////////////////////////////////////////////////////////
////  SET PARAMETERS
////////////////////////////////////////////////////////////////////////////////

  BRKGA::Parameters param;
  param.setNrGenes(d.getJ() * d.getT() * 2);
  param.setGenePrecision(4);
  param.setNrGenerations( 500 );
  param.setNrChromosomes((d.getJ() * d.getT() * 2) * 3);
  param.setCrossoverProbability(0.70);
  param.setNrMutants( ((d.getJ() * d.getT() * 2) * 3 ) * 0.3);
  param.setNrElites( ((d.getJ() * d.getT() * 2) * 3 ) * 0.1);

////////////////////////////////////////////////////////////////////////////////
////  USE CUSTOM INITIALIZER AND DECODER
////////////////////////////////////////////////////////////////////////////////

  BRKGA::Initializer init(&param);

  CLSDdecoder clsd(d);

  BRKGA::BRKGA brkga(&param, &init, &clsd);

////////////////////////////////////////////////////////////////////////////////
////  RUN GA
////////////////////////////////////////////////////////////////////////////////

  brkga.run();


  //return UnitTest::RunAllTests();


  return 0;
}


