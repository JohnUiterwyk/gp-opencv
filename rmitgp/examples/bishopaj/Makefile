
.SUFFIXES: .cpp $(SUFFIXES)

all:
	mpiCC -D MPI_ENABLED -rdynamic -g -I ../../src/ *.cpp -L/usr/local/openmpi/1.6.3-gcc/lib/ -lopencv_highgui -lopencv_core -lopencv_imgproc  -o symbolic2 ../../src/*.o

#	-D MPI_ENABLED

clean:
	rm symbolic2
	rm core*

