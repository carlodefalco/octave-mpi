// Copyright (C) 2017 Carlo de Falco
// Copyright (C) 2004-2007 Javier Fernández Baldomero, Mancia Anguita López
// Copyright (C) 2009 Riccardo Corradini <riccardocorradini@yahoo.it>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// Octave is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Octave; see the file COPYING.  If not, see
// <http://www.gnu.org/licenses/>.


#include "octave_mpi_communicator.h"
#include "put_mpi_stat.h"

// PKG_ADD: autoload ("MPI_Iprobe", "MPI_Init.oct");
DEFMETHOD_DLD (MPI_Iprobe, interp, args, nargout,"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [@var{FLAG} @var{STAT} @var{INFO}] = MPI_Iprobe(@var{SRCRANK}, @var{TAG}, @var{COMM})\n\
Nonblocking test for an MPI message.\n\
 @example\n\
 @group\n\
 \n\
     @var{FLAG} int \n\
       1    if the message is ready to be received\n\
       0    if it is not\n\
     @var{STAT} struct object\n\
       MPI_SOURCE         (int)  source rank for the accepted message\n\
       MPI_TAG            (int)  message tag for the accepted message\n\
       MPI_ERROR          (int)  error \n\
       MPI_Get_count      (int)  count\n\
       MPI_Test_cancelled (int)  cancel\n\
    @var{INFO} (int) return code\n\
      0 MPI_SUCCESS    No error\n\
     13 MPI_ERR_ARG    Invalid argument\n\
      5 MPI_ERR_COMM   Invalid communicator (null?)\n\
      4 MPI_ERR_TAG    Invalid tag argument (MPI_ANY_TAG, 0..MPI_TAG_UB attr)\n\
      6 MPI_ERR_RANK   Invalid src/dst rank (MPI_ANY_SOURCE, 0..Comm_size-1)\n\
 @end group\n\
 @end example\n\
 \n\
@seealso{MPI_Probe, MPI_Recv, MPI documentation for examples}\n\
@end deftypefn")
{
  octave_value_list results;
  int nargin = args.length ();
  if (nargin != 3)
    print_usage ();
  else 
    {
      //      COMMUNICATOR_TYPE_LOAD (interp);
      if (is_octave_mpi_communicator (args(2)))
        {
          error ("MPI_Iprobe: Please enter octave comunicator object");
          results = octave_value (-1);
        }
      else
        {
          MPI_Comm comm = ov_mpi_comm (args(2));
          int src = args(0).int_value();
          int tag = args(1).int_value();
          if (! error_state)
            {
              int flag;
              MPI_Status stat = {0, 0, 0, 0};    
              int info = MPI_Iprobe (src, tag, comm, &flag, &stat);
              comm = NULL;
              results(0) = flag;
              results(1) = put_MPI_Stat (stat);
              results(2) = info;
            }
          else
            print_usage ();
        }
    }
  return results;
}

	
