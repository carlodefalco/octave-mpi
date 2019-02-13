// Copyright (C) 2017 Carlo de Falco
// Copyright (C) 2004-2007 Javier Fernández Baldomero, Mancia Anguita López
// Copyright (C) 2009 Riccardo Corradini <riccardocorradini@yahoo.it>
// Copyright (C) 2009 VZLU Prague
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

// PKG_ADD: autoload ("MPI_Comm_rank", "MPI_Init.oct");
DEFMETHOD_DLD(MPI_Comm_rank, interp, args, nargout , "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [@var{RANK} @var{INFO}] = MPI_Comm_rank (@var{COMM})\n\
Return the rank of the calling process in the specified communicator.\n\
If the comunicator object @var{COMM} (loaded with MPI_Comm_Load) is omitted \n\
an error is thrown. \n\
 @example\n\
 @group\n\
    @var{RANK} rank of the calling process in group of communicator\n\
    @var{INFO} (int) return code\n\
       0 MPI_SUCCESS    No error\n\
       5 MPI_ERR_COMM   Invalid communicator (NULL?)\n\
      13 MPI_ERR_ARG    Invalid argument (typically a NULL pointer?)\n\
SEE ALSO: MPI_Comm_size\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value_list results;
  int nargin = args.length ();

  if (nargin != 1)
    print_usage ();
  else
    {
      //      COMMUNICATOR_TYPE_LOAD (interp);
      if (is_octave_mpi_communicator (args(0)))
        {
          MPI_Comm comm = ov_mpi_comm (args(0));
          if (! error_state)
            {
              int my_rank;
              int info = MPI_Comm_rank (comm, &my_rank);
              if (nargout > 1)
                results(1) = info;
              
              results(0) = my_rank;
            }
          else
            print_usage ();
        }
      else
        error ("MPI_Comm_rank: Please enter octave comunicator object");
    }
  return results;
}
