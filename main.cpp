#include <iostream>

//#include "UnitTest++.h"
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
  param.setGenePrecision(2);
  param.setNrGenerations(500);
  param.setNrChromosomes(100);
  param.setCrossoverProbability(0.90);
  param.setNrMutants(30);
  param.setNrElites(10);

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


