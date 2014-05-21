#include "instance.h"
Instance::Instance()
{

}

Instance::Instance(unsigned int J, unsigned int T)
{
  numberOfItems = J;
  numberOfPeriods = T;
}


Instance::Instance(char* inputfilename)
{
  inputfile = fopen(inputfilename,"r");
  filename = inputfilename;
  if(!inputfile) {
    std::cerr << "Could not open file:" << inputfilename << std::endl;
  }//if


  fscanf(inputfile, "Instance parameters\n");
  fscanf(inputfile, "T=%u J=%u\n", &numberOfPeriods, &numberOfItems);

  resizeContainers();

}

Instance::~Instance()
{
  //dtor
}

void Instance::resizeContainers()
{
  demand.resize(numberOfItems, unsignedVector(numberOfPeriods));
  setupCost.resize(numberOfItems, unsignedVector(numberOfItems));
  capacity.resize(numberOfPeriods);
  requiredCapacity.resize(numberOfItems);
  holdingCost.resize(numberOfItems);
  initialSetupCost.resize(numberOfItems);
}

void Instance::readWinforData(char* inputfilename)
{

  inputfile = fopen(inputfilename,"r");
  filename = inputfilename;
  if(!inputfile) {
    std::cerr << "Could not open file:" << inputfilename << std::endl;
  }//if


  fscanf(inputfile, "Instance parameters\n");
  fscanf(inputfile, "T=%u J=%u\n", &numberOfPeriods, &numberOfItems);

  resizeContainers();

  //read demand
  for(unsigned int i = 0; i < numberOfItems; i++) {
    while(fgetc(inputfile)!='d') {
      fgetc(inputfile);
    }
    //jump to )
    while(fgetc(inputfile)!=')') {
      fgetc(inputfile);
    }

    for(int j = 0; j < numberOfPeriods; j++) {
      fscanf(inputfile, "%i|", &demand[i][j]);
    }
  }

  //read Capacity
  while(fgetc(inputfile)!='C') {
    fgetc(inputfile);
  }

  fscanf(inputfile, "_t");

  for(int i = 0; i < numberOfPeriods; i++) {
    fscanf(inputfile, "%i|", &capacity[i]);
  }
  //read setup costs
  while(fgetc(inputfile)!='s') {
    fgetc(inputfile);
  }
  while(fgetc(inputfile)!='-') {
    fgetc(inputfile);
  }
  while(fgetc(inputfile)=='-') {
    fgetc(inputfile);
  }


  for(int j = 0; j < numberOfItems; j++) {
    fscanf(inputfile, "%i", &dummy);
    for(int i = 0; i < numberOfItems; i++) {
      fscanf(inputfile, "%i|", &setupCost[j][i]);
    }
  }

  //read holding cost
  while(fgetc(inputfile)!='c') {
    fgetc(inputfile);
  }
  while(fgetc(inputfile)!=']') {
    fgetc(inputfile);
  }

  fscanf(inputfile, "c[j]");
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%i|", &holdingCost[i]);
  }

  //read requiredCapacity
  while(fgetc(inputfile)!=']') {
    fgetc(inputfile);
  }
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%i|", &requiredCapacity[i]);
  }

}


void Instance::readFleischmanData(char* inputfilename)
{
filename = inputfilename;
  inputfile = fopen(inputfilename,"r");


  if(!inputfile) {
    std::cerr << "Could not open file:" << inputfilename << std::endl;
  }//if

  //read no. items, periods
  fscanf(inputfile, "NProducts = %u;\n", &numberOfItems);
  fscanf(inputfile, "NPeriods = %u;\n", &numberOfPeriods);
  fscanf(inputfile, "\n");

  resizeContainers();

  //read holding costs
  fscanf(inputfile, "h = [");
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%u ", &holdingCost[i]);
  }//for
  fscanf(inputfile, "];\n");
  //read Required Capacity
  fscanf(inputfile, "p = [");
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%u ", &requiredCapacity[i]);
  }//for
  fscanf(inputfile, "];\n");

  //skip Setup Times
  fscanf(inputfile, "stimes = [");
  for(int i = 0; i < numberOfItems-1; i++) {
    fscanf(inputfile, "[");
    for(int j = 0; j < numberOfItems-1; j++) {
      fscanf(inputfile, "%u ", &dummy);
    }//for
    fscanf(inputfile, "%u", &dummy);
    fscanf(inputfile, "],");
  }
  fscanf(inputfile, "[");
  for(int j = 0; j < numberOfItems-1; j++) {
    fscanf(inputfile, "%u ", &dummy);
  }//for
  fscanf(inputfile, "%u]];\n\n", &dummy);

  //read Capacity
  fscanf(inputfile, "Cap = [");
  for(int i = 0; i < numberOfPeriods; i++) {
    fscanf(inputfile, "%u ", &capacity[i]);
  }//for
  fscanf(inputfile, "];\n");

  //read demand
  fscanf(inputfile, "d = [");
  for(int i = 0; i < numberOfItems-1; i++) {
    fscanf(inputfile, "[");
    for(int j = 0; j < numberOfPeriods-1; j++) {
      fscanf(inputfile, "%u ", &demand[i][j]);
    }//for
    fscanf(inputfile, "%u", &demand[i][numberOfPeriods-1]);
    fscanf(inputfile, "],");
  }
  fscanf(inputfile, "[");
  for(int j = 0; j < numberOfPeriods-1; j++) {
    fscanf(inputfile, "%u ", &demand[numberOfItems-1][j]);
  }//for
  fscanf(inputfile, "%u]];\n\n", &demand[numberOfItems-1][numberOfPeriods-1]);

  //skip max production cap
  fscanf(inputfile, "M = [");
  for(int i = 0; i < numberOfItems-1; i++) {
    fscanf(inputfile, "[");
    for(int j = 0; j < numberOfItems-1; j++) {
      fscanf(inputfile, "%u ", &dummy);
    }//for
    fscanf(inputfile, "%u", &dummy);
    fscanf(inputfile, "],");
  }
  fscanf(inputfile, "[");
  for(int j = 0; j < numberOfItems-1; j++) {
    fscanf(inputfile, "%u ", &dummy);
  }//for
  fscanf(inputfile, "%u]];\n\n", &dummy);

  //read demand
  fscanf(inputfile, "scosts = [");
  for(int i = 0; i < numberOfItems-1; i++) {
    fscanf(inputfile, "[");
    for(int j = 0; j < numberOfItems-1; j++) {
      fscanf(inputfile, "%u ", &setupCost[i][j]);
    }//for
    fscanf(inputfile, "%u", &setupCost[i][numberOfItems-1]);
    fscanf(inputfile, "],");
  }
  fscanf(inputfile, "[");
  for(int j = 0; j < numberOfItems-1; j++) {
    fscanf(inputfile, "%u ", &setupCost[numberOfItems-1][j]);
  }//for
  fscanf(inputfile, "%u]];\n\n", &setupCost[numberOfItems-1][numberOfItems-1]);
}
void Instance::readBachtenkirchData(char* inputfilename)
{
  filename = inputfilename;
  inputfile = fopen(inputfilename,"r");

  if(!inputfile) {
    std::cerr << "Could not open file:" << inputfilename << std::endl;
  }//if

  fscanf(inputfile,"%u %u\n",&numberOfItems, &numberOfPeriods);
  resizeContainers();
  //read holding costs, production quantity and required capacity
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%u %u %u\n", &holdingCost[i], &dummy, &requiredCapacity[i]);
  }//for

  //read number of sub-periods and capacity
  for(int i = 0; i < numberOfPeriods; i++) {
    fscanf(inputfile, "%u %u\n", &dummy, &capacity[i]);
  }//for

  fscanf(inputfile, "Sinit\n");
  //read initial setup costs
  for(int i = 0; i < numberOfItems; i++) {
    fscanf(inputfile, "%u\n", &initialSetupCost[i]);
  }//for

  fscanf(inputfile, "SDS\n");
  //read setup costs
  for(int i = 0; i < numberOfItems; i++) {
    for(int j = 0; j < numberOfItems; j++) {
      fscanf(inputfile, "%u ", &setupCost[i][j]);
    }//for
    fscanf(inputfile, "\n");
  }//for

  fscanf(inputfile, "DEMAND\n");
  //read setup costs
  for(int i = 0; i < numberOfItems; i++) {
    for(int j = 0; j < numberOfPeriods; j++) {
      fscanf(inputfile, "%u ", &demand[i][j]);
    }//for
    fscanf(inputfile, "\n");
  }//for
}


