#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>

void core_affinity_(char *clbuf);

int main(int argc, char *argv[])
{
 int rank, thread, requested, provided;
 cpu_set_t coremask;
 char clbuf[7 * CPU_SETSIZE], hnbuf[64];
 MPI_Init_thread(&argc, &argv, 3, &provided);
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 memset(clbuf, 0, sizeof(clbuf));
 memset(hnbuf, 0, sizeof(hnbuf));
 (void)gethostname(hnbuf, sizeof(hnbuf));
 #pragma omp parallel private(thread, coremask, clbuf)
 {
 thread = omp_get_thread_num();
 (void) core_affinity_(clbuf);
#pragma omp barrier
 printf("Level 1: rank= %d, thread level 1= %3d, on %s. (core affinity = %s)\n",
 rank, thread, hnbuf, clbuf);
 }
 MPI_Finalize();
 return(0);
}

