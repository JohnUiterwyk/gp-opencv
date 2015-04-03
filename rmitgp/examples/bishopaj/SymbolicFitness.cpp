/******************************************************************************
 Definition file
 Class:        SymbolicFitness
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <float.h> //for DBL_MAX
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <ctime>

#include "SymbolicFitness.h"
#include "ReturnDouble.h"
#include "symbols.h"

#include <opencv2/opencv.hpp>
#include "XDouble.h"

#include "CVDebug.h"
#include "LoggingNode.h"
#include "ImageCase.h"
#include "popen2.h"
#include <sys/wait.h>

#ifdef MPI_ENABLED
#include "mpi.h"

#define MPI_MESSAGE_SIZE 1000000

#endif
#include <time.h>

#define TRAINING_SPLIT (0.7)


SymbolicFitness::SymbolicFitness(GPConfig *conf) : Fitness(conf)
{





   generationCounter = 0;
}


ImageCase SymbolicFitness::loadimage(std::string path, std::string filename)
{
	string fname = path + filename;
	Mat img=cv::imread(fname, CV_LOAD_IMAGE_COLOR);
	Mat img2;

	img.convertTo(img2, CV_32F);

	cv::cvtColor(img2, img, CV_BGR2HSV);

	vector<Mat> channels(3);
	cv::split(img, channels);

	//cv::imwrite("c99.png", img2);
	//cv::imwrite("c0.png", channels[0]);
	//cv::imwrite("c1.png", channels[1]);
	//cv::imwrite("c2.png", channels[2]);



	//float t1=img.at<float>(0,0);
	//float t2=img.at<float>(31,31);


	ImageCase result;
	result.brightness=channels[2]/255;
	result.saturation =channels[1]/255;
	result.hue =channels[0]/255;

	result.filename=filename;

	return result;
}


SymbolicFitness::~SymbolicFitness() 
{
}

void SymbolicFitness::initFitness()
{
	std::string path = "";
	std::ifstream  data((path + "goodbad.csv").c_str());

	std::string line;
	//skip header
	std::getline(data,line);

	while(std::getline(data,line))
	{
		std::stringstream  lineStream(line);
		std::string        fname;
		if(0>=std::getline(lineStream,fname,','))
			throw std::string("CSV parse error");

		if(fname[0]=='"')
			fname=fname.erase(0,1);
		if(fname[fname.length()-1]=='"')
			fname=fname.erase(fname.length()-1, 1);
		cases.push_back(loadimage(path + "imagene-unrated/", fname));
	}
}

double SymbolicFitness::TestProg(GeneticProgram* prog, ImageCase image)
{
	CVDebug::logstream << endl << "-------------------------" <<  endl << CVDebug::index <<  endl ;

	ReturnDouble rval;

	ImageBrightness::setValue(image.brightness);
	ImageHue::setValue(image.hue);
	ImageSaturation::setValue(image.saturation);
	prog->evaluate(&rval);
	double result = rval.getData();

	if (!isfinite(result))
		throw string("not finite");


	CVDebug::logstream << " Got: " << result;

	CVDebug::incrementIndex();

	return result;
}

void SymbolicFitness::EvaluateProg(GeneticProgram* prog, bool isTraining, int rank)
{
	try
	{

	prog->setFitness(worst());

		double fitness=worst();

		CVDebug::setIndex(0);


	    for (int i=0;i<cases.size();i++)
		{

	    	try {
	    		cases[i].result = TestProg(prog, cases[i]);

	    	} catch (string& s) {

	    		cerr << s << endl;
	    	    return;

	    	} catch(...){

	    		cerr << "exception in evaluation" << endl;
	    	    return;
	    	}

		}

		std::ostringstream evalfile;
		evalfile << "eval" << rank << ".csv";
		std::ostringstream resultfile;
		resultfile << "result" << rank << ".csv";

		remove(evalfile.str().c_str());
		remove(resultfile.str().c_str());

		ofstream feval;
		feval.open(evalfile.str().c_str());

		for(int i=0;i<cases.size();i++)
	    {
			feval << cases[i].filename << "," <<  cases[i].result << endl;
	    }

		feval.close();

		std::string command = std::string("./evaluate.sh ") + evalfile.str() + " " + resultfile.str();
		if(0>system(command.c_str()))
			throw string("error launching process");

		ifstream fresult;
		fresult.open(resultfile.str().c_str());
		std::istreambuf_iterator<char> eos;
		std::string sresult(std::istreambuf_iterator<char>(fresult), eos);
		fresult.close();

		if(1!=sscanf(sresult.c_str(), "%lf", &fitness))
		{
			cerr << "error reading result" << endl;
			throw string("error reading result");
		}

		CVDebug::logstream << "Fitness: " << fitness <<  endl ;
		prog->setFitness(fitness);
	}
	catch(const string& s)
	{
		cout << "EvaluateProg: " << s << endl;
		cerr << "EvaluateProg: " << s << endl;
		exit(-1);
	}


}

void SymbolicFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
	   CVDebug::setEnabled(false);


#ifdef MPI_ENABLED // If MPI is enabled this will change to a master/slave process as below

	int MPI_count = 0;
	MPI_Comm_size(MPI_COMM_WORLD,&MPI_count);
	if(MPI_count > 1)
	{
		masterProcess(pop, popSize);
		return;
	}
	else
	{
		//debug MPI
	   int i;
	   char message[MPI_MESSAGE_SIZE];
	   int process=1;

	   for(i=0; i<popSize; i++)
	   {
		   formatSlaveMessage(pop, message, MPI_MESSAGE_SIZE, i);

		   GeneticProgram tmp(config);

		   slaveProcessMessage(&tmp, message, MPI_MESSAGE_SIZE, process);

		   parseSlaveResponse(pop, message, process);
	   }
	}
#else

   int i,j;

   for(i=0; i<popSize; i++)
   {
		EvaluateProg(pop[i], true, 0);
   }
#endif
}

void SymbolicFitness::outputResults(GeneticProgram *program, const char *filename)
{
   int i;
   double xDouble;
   ofstream outputFile;
   string progString;
   ReturnDouble rd;

   outputFile.open(filename); 
   if (outputFile.bad())
   {
      cerr << "SymbolicFitness::outputResults Could not open output file"
           << endl;  
      return;
   }

   program->print(progString);

   outputFile << "#Results for evolved program" << endl  
              << "#Output" << endl 
              << "#X    Expected     Actual" << endl;


   CVDebug::setIndex(0);

   //CVDebug::setEnabled(true);

   program->setRoot(LoggingNode::Wrap(this->config, program->getRoot()));

   EvaluateProg(program, false, 0);

/*
   for (i=0; i<NUM_TEST_CASES; i++)
   {
      xDouble = (double)i;
      XDouble::setValue(xDouble);

      program->evaluate(&rd);
      
      outputFile << xDouble << " "
   //            << (3 * xDouble) + 14.45 << " "
                 << (1.5 * (xDouble * xDouble * xDouble)) +
                    (3.2 * (xDouble * xDouble)) +
                    (4.0 * xDouble) -127.2 << " "
                 << rd.getData() << endl;
   }
*/
   outputFile.close();
}

bool SymbolicFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.05)
         return true;
   }
   return false;
}

bool SymbolicFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool SymbolicFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool SymbolicFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double SymbolicFitness::best()
{
   return 0.0;
}

double SymbolicFitness::worst()
{
   return DBL_MAX;
}


///////////////////////////////////////////////////////////////////////
// MPI Processing Section - Master and slave have different processes
// Master mutates and assigns programs to slaves who process and return relevant values
// to the Master
///////////////////////////////////////////////////////////////////////

#ifdef MPI_ENABLED
void SymbolicFitness::masterProcess(GeneticProgram* pop[], int popSize)
{
  int process = 0;
  int popNum = 0;

  char message[MPI_MESSAGE_SIZE];
  int processSize;
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD,&processSize);
  process = processSize-1;

 
  for(int i=1;i<processSize;i++) // sends programs to the slave processors
  {

	  formatSlaveMessage(pop, message, MPI_MESSAGE_SIZE, popNum);

	//cout<<"Message Sent: "<<message<<"\n Sent to: "<< i<<" "<<popNum<<" "<<programString<<endl;
	MPI_Send(&message,MPI_MESSAGE_SIZE,MPI_CHAR,i,1,MPI_COMM_WORLD);
	//cout<<"Messent sent"<<endl;
	popNum++;

  }
  while (popNum < popSize) // Wait for a slave to finish, process it, then send it another
  {
    MPI_Recv(&message,MPI_MESSAGE_SIZE,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    parseSlaveResponse(pop, message, process);

    formatSlaveMessage(pop, message, MPI_MESSAGE_SIZE, popNum);

	//cout<<message<<endl;
	MPI_Send(&message,MPI_MESSAGE_SIZE,MPI_CHAR,process,1,MPI_COMM_WORLD);
	popNum++;

   }
   while (processSize > 1) // Once all programs have been sent, wait for last program results to be returned
   {
    MPI_Recv(&message,MPI_MESSAGE_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    parseSlaveResponse(pop, message, process);

    processSize--;
   }
}

void SymbolicFitness::formatSlaveMessage(GeneticProgram* pop[], char* message, int msg_size, int popNum)
{
	stringstream ss("");
	string programString = "";
	pop[popNum]->print(programString);
	ss << popNum << " " << programString<<'\0';
	ss.read(message,msg_size);
}
void SymbolicFitness::parseSlaveResponse(GeneticProgram* pop[], char* message, int& process)
{
	stringstream ss("");
	int currentPop;
	double fitness;

	ss << message;
	ss >> process >> currentPop >> fitness;
	pop[currentPop]->setFitness(fitness);
}


void SymbolicFitness::slaveProcess(GeneticProgram* pop)
{
	int rank = 0;
	double fitness;
	char message[MPI_MESSAGE_SIZE];
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	ofstream log;
	std::ostringstream stringStream;
	stringStream << "slave" << rank << ".log";
	std::string copyOfStr = stringStream.str();
	log.open(stringStream.str().c_str());
	
	log << "slave " << rank << '\n';

	int nindiv =0;
	std::clock_t start;
	start = std::clock();
	double duration;
	double work=0;
	std::clock_t workstart;	

	while(1) // Wait for master instructions
	{

		if(nindiv%1000==0)
		{		
			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; 	
			log << duration << " " << work << '\n';
			log.flush();

			start = std::clock();
			work=0;
		}
		

		MPI_Recv(&message,MPI_MESSAGE_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		nindiv++;
		workstart = std::clock();

		slaveProcessMessage(pop, message, MPI_MESSAGE_SIZE, rank);
		
		MPI_Send (&message, MPI_MESSAGE_SIZE, MPI_CHAR,0,1,MPI_COMM_WORLD);

		work += ( std::clock() - workstart ) / (double) CLOCKS_PER_SEC; 	
	 }
}
void SymbolicFitness::slaveProcessMessage(GeneticProgram* prog, char* message, int msg_size, int rank)
{
	string programString="";
	stringstream ss("");

	ss.clear();
	ss.str("");
	programString = "";

	int popNum = 0;
	int currentPop;

	ss << message;
	ss >> currentPop;
	if (currentPop == -1) // termination message
	{
		return;
	}

	getline(ss,programString);
	programString.erase(0,1);

	//try
	{
		prog->parseProgram(programString);
	}
	//catch(const string& e)
	//{
	//	cerr << "Exception parsing: " << e << endl;
	//	throw e;
	//}

	int falseneg = 0,falsepos =0, trueneg =0, truepos = 0;
	programString = "";
	prog->print(programString);

	this->EvaluateProg(prog, true, rank);

	ss.clear();
	ss.str("");
	ss << rank <<" "<< currentPop <<" "<< prog->getFitness()<<'\0';
	ss.read(message, msg_size);
}

#endif


