          RMIT Genetic Programming System (rmitgp)
                 Date : July, 2006

            INSTRUCTIONS FOR v1.5 - UNIX/LINUX
       by Gayan Wijesinghe (gwijesin@cs.rmit.edu.au)

             STEP 1:  DOWNLOAD SOURCE FILES
             STEP 2:  UNTAR   SOURCE  FILES 
             STEP 3:  SET  UP   ENVIRONMENT
             STEP 4:  COMPILE THE GPLIB SRC
             STEP 5:  EXECUTE  ONE  EXAMPLE


STEP 1:  DOWNLOAD SOURCE FILES
------------------------------
Download the tar file and save it to a directory in your
account.   Current version is  1.5 and can be downloaded 
from 
   http://www.cs.rmit.edu.au/~vc/rmitgp


STEP 2:  UNZIP   SOURCE  FILES 
------------------------------
Depending on what platform you are on, you should be able
to untar it using one of the following commands  (replace 
question marks with release version number)

   gzcat -c rmitgp.v1.5.tar.gz | tar -xvf - 
 
OR

   gunzip rmitgp.v1.5.tar.gz
   tar -xvf rmitgp.v1.5.tar

The source will be untarred to a directory called rmitgp.1.5/, 
under this  directory is  a  directory  called doc/ which 
contains the system documentation.  Open the file index.html. 
This  contains a brief overview of the system and some links 
to examples on how to use RMITGP for your own genetic 
programming tasks. (Do this after the last step)


STEP 3:  SET  UP  ENVIRONMENT
------------------------------
You need to set up your  unix  environment by  editing the 
.cshrc file in your home directory. 

   vim ~/.cshrc

   ##### PASTE THE FOLLOWING INTO THE END OF THE FILE #####
   setenv LD_LIBRARY_PATH /share/arch/SunOS~sun4u~5.10/pkg/gcc-4.2.2/lib:${LD_LIBRARY_PATH}
   setenv PATH /share/arch/SunOS~sun4u~5.10/pkg/gcc-4.2.2/bin:${PATH}
   ##### SAVE THE FILE AND EXIT BY TYPEING :wq        #####

   ## If your OS is not SunOS or you're installing on a system other ##
   ## than yallara/numbat/goanna, modify the gcc paths above         ##

Log out of the unix and log in again to activate the  new
settings. 


STEP 4:  COMPILE THE GPLIB SRC
------------------------------
Go to the directory rmitgp.1.5/  and  enter  the sub directory 
src/ to make the RMITGP library files. 

   cd src
   make clean
   make depend
   make

It should  create a file called librmitgp.a.  If there are
errors,  please report to vc@cs.rmit.edu.au.


STEP 5:  EXECUTE  ONE  EXAMPLE
------------------------------
After compiling the source, go back to one directory level
up by 

   cd ..

Enter into the examples/ directory by

   cd examples

Enter into symbolic2/ directory by

   cd symblic2

Edit the Makefile by 
   
   vim Makefile

   # Make sure "-DOLD_GCC" in "DEFINES = -DUNIX -DOLD_GCC" is commented out
   # Save the Makefile (if necessary) and exit by :wq 

Compile the example files by

   make depend
   make 
   
Ignore the warnings on deprecated statements.

Run the example by
   ./symbolicgp

Get the fitness graph from the log file.

There are two scripts that can be used for graphing the
results of your run. They are

gplot_fitness
jplot_fitness

and are located in the graphing/ directory.

The first uses gnuplot and the second uses jgraph.

   ../../graphing/gplot_fitness run-log.txt
   gv run-log-gnu.ps


-----------------
Good luck and please report the errors to vc@cs.rmit.edu.au.

