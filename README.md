# Octave MPI : Octave bindings for basic Message Passing Interface (MPI) functions for parallel computing.

## CONTENTS:

1. HISTORY
2. INSTALLATION INSTRUCTIONS
3. ORIGINAL README

## 1. HISTORY

This project was started in 2010 under the name *openmpi_ext* 
By Riccardo Corradini in collaboration with Jaroslav Hajek. 
It was intended as more intuitive and more maintainable
alternative to other similar packages existing at that time, 
namely the MPI Toolbox for Octave (MPITB) by Javier Fernández 
Baldomero and Mancia Anguita.

Carlo de Falco started contributing in 2012, then took over
the package maintainance in 2014 after Riccardo Corradini had
stepped down in 2013. At the same time the name of the package
was changed to *mpi*.

Since 2017 the main repository for the package was moved out
of sourceforge and is now at https://github.com/carlodefalco/octave-mpi


## 2. INSTALLATION INSTRUCTIONS

The makefile included derives all the info it needs for building
the code from running mpicxx, so make sure that mpicxx is in your
path before running Octave or type 

    putenv ("PATH", ["/path/to/mpicxx:" getenv("PATH")])

from within Octave.
Once this is done you should be able to install openmpi_ext from a
locally dowloaded tarball by doing:

    pkg install mpi-<version>.tar.gz

or directly from the url by doing 

    pkg install 'https://github.com/carlodefalco/octave-mpi/releases/download/v<version number>/mpi-<version number>.tar.gz'


## 3. ORIGINAL README

*Below are the contents of the original README file included with the first release
by R. Corradini, most of the info there is very outdated but they are still
reported here, just in case, mainly for historical reasons*

The code is general-purpose, but  I would like to use it for econometrics.
So the first step will be to install the following tarball from
http://www.open-mpi.org/software/ompi/v1.3/downloads/openmpi-1.3.3.tar.bz2
possibly in a multi-core computer to run my simple examples
and configure it for instance in the following way (/home/user is your $HOME)
./configure --enable-mpirun-prefix-by-default --enable-heterogeneous --prefix=/home/user/openmpi-1.3.3/ --enable-static

and modify .bashrc in your home
 OMPIBIN=`$ompi_info -path     bindir  -parsable | cut -d: -f3`
 OMPILIB=`$ompi_info -path     libdir  -parsable | cut -d: -f3`
 OMPISCD=`$ompi_info -path sysconfdir  -parsable | cut -d: -f3`



export            PATH=$OMPIBIN:$PATH

export LD_LIBRARY_PATH=:$OMPILIB:$LD_LIBRARY_PATH

unset  ompi_info OMPIBIN OMPILIB OMPISCD 

If you want to install it on a simple toy network, just assign a static ip address on every linux computer and set up 
an ssh connection with no password (see for instance http://linuxproblem.org/art_9.html ) and then install openmpi and octave always with the same versions and with the same info on .bashrc for the same user.

After this type in a terminal mpiCC --showme
In my case I will have something like

g++ -I/home/user/openmpi-1.3.3/include -pthread -L/home/user/openmpi-1.3.3/lib -lmpi_cxx -lmpi -lopen-rte -lopen-pal -ldl -Wl,--export-dynamic -lnsl -lutil -lm -ldl

This will be useful for mkoctfile
for instance for MPI_Init.cc we shall have
mkoctfile -I/home/user/openmpi-1.3.3/include -lpthread -L/home/user/openmpi-1.3.3/lib -lmpi_cxx -lmpi -lopen-rte -lopen-pal -ldl -lnsl -lutil -lm -ldl MPI_Init.cc



The m files just contain some very simple examples
More complex examples will be provided in the next future.
See also
http://static.msi.umn.edu/tutorial/scicomp/general/MPI/content6.html
to understand the logic of MPI Derived Datatypes and how could they be easily handled by openmpi_ext package.
Bests regards
Riccardo Corradini



