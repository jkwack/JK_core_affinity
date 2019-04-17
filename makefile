# Compilers
FF = mpif90
CC = mpicc


all: clean
	$(CC) -c JK_coreID.c
	$(CC) -fopenmp JK_coreID.o JK_core_affinity.c -o Run_c
	$(FF) -fopenmp JK_coreID.o JK_core_affinity.f90 -o Run_f90



clean:
	rm -f *.o Run_c Run_f90 *.mod




