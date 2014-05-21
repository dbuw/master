/* ----------------------------------------------------------------------------
  instance.h
  @author David Bachtenkirch

DESCRIPTION:
  This class just reads and stores instance data. There are three methods to call
  to read a different set of instances.
  - readWinforData
  - readFleischmanData
  - readBachtenkirchData

  Access to this class is granted by friendship.
---------------------------------------------------------------------------- */

#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>



class Instance {
public:

  typedef std::vector<unsigned> unsignedVector;
  typedef std::vector<unsignedVector> unsigned2dMatrix;
  Instance();
  Instance(unsigned int, unsigned int);
  Instance(char*);

  virtual ~Instance();

  void resizeContainers();
  //read instance data
  void readWinforData(char*);
  void readFleischmanData(char*);
  void readBachtenkirchData(char*);

  unsigned int numberOfItems;
  unsigned int numberOfPeriods;

  unsigned2dMatrix demand;
  unsigned2dMatrix setupCost;
  unsignedVector capacity;
  unsignedVector requiredCapacity;
  unsignedVector holdingCost;
  unsignedVector initialSetupCost;

  char* filename;
private:
  //File handling
  FILE*       inputfile; // file to read
  FILE*       outputfile; // file to write
  int       dummy; // dummy variable reads not needed information

};

#endif // INSTANCE_H
