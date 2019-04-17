program hello
!  use mpi
  implicit none
  include "mpif.h"
  integer :: ierr,iproc,nproc,icomm
  integer :: tid,nthreads
  integer :: omp_get_num_threads
  integer :: omp_get_thread_num
  integer :: omp_get_place_proc_ids
  integer :: len
  integer :: i,j
  character*(MPI_MAX_PROCESSOR_NAME) :: name
  character*(30) :: clbuf

  call MPI_INIT(ierr)
  icomm = MPI_COMM_WORLD
  call MPI_COMM_SIZE(icomm,nproc,ierr)
  call MPI_COMM_RANK(icomm,iproc,ierr)
  call MPI_GET_PROCESSOR_NAME(name, len, ierr)
  do i=0,nproc-1
    call MPI_BARRIER(icomm,ierr)
!$omp parallel private( tid,clbuf ) 
    tid = omp_get_thread_num()
    nthreads = omp_get_num_threads()
    clbuf = ' '
    call core_affinity(clbuf)

    do j=0,nthreads-1
!$omp barrier
      if(i .eq. iproc .and. j.eq.tid) then
        write(*,'(a,i3,a,i3,a,a,a,a)') "Rank=",iproc,",thread=",tid,&
                       " on ",name(1:len)," | core affinity: ",clbuf(1:30)
      endif
   enddo
!$omp end parallel
  enddo
  call MPI_FINALIZE(ierr)
  stop
end program hello

