MPICC     ?= mpicxx
OFMPIINC  ?= $(shell $(MPICC) -showme:compile | sed -e "s/-pthread/ /g")
MPIINC    := $(OFMPIINC)
OFMPILIBS ?= $(shell $(MPICC) -showme:link | sed -e "s/-pthread/ /g")
MPILIBS   := $(OFMPILIBS)
MKOCTFILE ?= mkoctfile

OBJS = MPI_Init.o MPI_Initialized.o \
     MPI_Comm_rank.o MPI_Comm_size.o \
     MPI_Finalize.o MPI_Finalized.o MPI_Send.o \
     MPI_Recv.o MPI_Barrier.o  MPI_Iprobe.o \
     MPI_Probe.o __MPI_COMM_WORLD__.o \
     MPI_Get_processor_name.o octave_mpi_communicator.o \
     put_mpi_stat.o

all: MPI_Init.oct

%.o : %.cc octave_mpi_communicator.h
	$(MKOCTFILE) $(MPIINC) -c $<

MPI_Init.oct: $(OBJS) MPI_Init.o
	$(MKOCTFILE) $(MPILIBS) $(OBJS) -o MPI_Init.oct
clean:
	$(RM) *.o  *.oct *~

