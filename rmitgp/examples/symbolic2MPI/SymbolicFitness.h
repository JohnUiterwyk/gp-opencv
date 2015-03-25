#ifndef _SYMBOLICFITNESS_H_
#define _SYMBOLICFITNESS_H_

/******************************************************************************
 Header file
 Class:        SymbolicFitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 A symbolic regression fitness class
******************************************************************************/

#include <vector>
#include <opencv2/opencv.hpp>
#include "GeneticProgram.h"
#include "Fitness.h"
#include "GPConfig.h"
#include "ImageCase.h"

#define TARPEIAN true // QCS 20120917
#define DDL true //  QCS 20120930

#ifndef MPI_ENABLED
#define MPI_ENABLED
#endif

class SymbolicFitness : public Fitness
{
   private:
      //This constant controls the number of points to use for
      //training the programs
      static const int FITNESS_CASES;

  	vector<ImageCase > cases;

      
      int generationCounter; // Used only to print out the progress

      ImageCase loadimage(std::string path, std::string filename);

	void EvaluateProg(GeneticProgram* prog, bool isTraining, int rank);
	double TestProg(GeneticProgram* prog, ImageCase image);
   protected:

   public:
      SymbolicFitness(GPConfig *conf);
      virtual ~SymbolicFitness();
      virtual void initFitness();
      virtual void assignFitness(GeneticProgram* pop[], int popSize);
      virtual bool solutionFound(GeneticProgram* pop[], int popSize);
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

      virtual double best();
      virtual double worst();

		#ifdef MPI_ENABLED
		void slaveProcess(GeneticProgram* pop);
		void masterProcess(GeneticProgram* pop[], int popSize);
		void slaveProcessMessage(GeneticProgram* prog, char* message, int msg_size, int rank);
		void formatSlaveMessage(GeneticProgram* pop[], char* message, int msg_size, int popNum);
		void parseSlaveResponse(GeneticProgram* pop[], char* message, int& process);
		#endif
	  
      /******************************************
       Writes out the results of executing a 
       program to the file. Along with the 
       desired results. 
      *******************************************/
      void outputResults(GeneticProgram *program, const char *filename);


};

#endif
