#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <math.h>       /* pow */

namespace BRKGA {

class Parameters {
public:
  Parameters() {}
  //sets the precision of the genome encoding
  //Random-Keys are bound between [0,1] and implemented as integers
  void setGenePrecision(int i = 2) {
    minGene = 0;
    if(i < 2) {
      maxGene = 100;
    } else if(i > 8) {
      maxGene = 10000000;
    } else {
      maxGene = pow(10,i);
    }
  }
  //setters
  void setNrGenerations(int i) {numGens = i;};
  void setNrChromosomes(int i) {numC = i;};
  void setNrMutants(int i) {numM = i;};
  void setNrElites(int i) {numE = i;};
  void setNrGenes(int i) {numGenes = i;};
  void setCrossoverProbability(int i) {pc = i;};
  //getters
  int maxGen() {return numGens;};
  int nrChromosomes() {return numC;};
  int nrMutants() {return numM;};
  int nrElites() {return numE;};
  int nrOffspring() {return (numC - numE - numM);};
  int nrGenes() {return numGenes;};
  int minGeneValue() {return minGene;};
  int maxGeneValue() {return maxGene;};
  int pC() {return pc;};

private:
  int minGene;
  int maxGene;

  int numGens; //number of Generations
  int numC; //number of Chromosomes in a Generation
  int numM; //number of Mutants in a Generation
  int numE; //number of Elites in a Generation
  int pc; // threshold for Crossover decision
  int numGenes; //number of genes in a chromosome
};

}

#endif // PARAMETERS_H
