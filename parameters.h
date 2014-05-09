#ifndef PARAMETERS_H
#define PARAMETERS_H


class Parameters
{
    public:
        Parameters();
        //sets the precision of the genome encoding
        //Random-Keys are bound between [0,1] and implemented as integers
        void setGenePrecision(int i = 2){
            if (i < 1){
                precision = 1;
            }
            else if (i > 8){
                precision = 8;
            }
            else{
                precision = i;
            }
        }
        //setters
        void setNrGenerations(int i){numGens = i;};
        void setNrChromosomes(int i){numC = i;};
        void setNrMutants(int i){numM = i;};
        void setNrElites(int i){numE = i;};
        void setNrGenes(int i){numGenes = i;};
        //getters
        int maxGen(){return numGens;};
        int nrChromosomes(){return numC;};
        int nrMutants(){return numM;};
        int nrElites(){return numE;};
        int nrOffspring(){return (numC - numE - numM);};
        int nrGenes(){return numGenes;};

    private:
        int precision; //number of decimal positions for gene encoding
        int numGens; //number of Generations
        int numC; //number of Chromosomes in a Generation
        int numM; //number of Mutants in a Generation
        int numE; //number of Elites in a Generation
        int pc; // threshold for Crossover decision
        int numGenes; //number of genes in a chromosome
};

#endif // PARAMETERS_H
