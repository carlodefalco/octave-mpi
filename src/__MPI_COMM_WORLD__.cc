// Copyright (C) 2017 Carlo de Falco
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

// PKG_ADD: autoload ("__MPI_COMM_WORLD__", "MPI_Init.oct");
DEFMETHOD_DLD (__MPI_COMM_WORLD__, interp, args, ,"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} @var{COMM} = MPI_COMM_WORLD ()\n\
Return in @var{COMM} the MPI_COMM_WORLD object.\n\
For example,\n\
\n\
@example\n\
@group\n\
MPI_Init();\n\
X = MPI_COMM_WORLD; \n\
whos X\n\
MPI_Finalize();\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value retval;
  if (args.length () != 0)
    print_usage ();
  else
    {
      // std::cout << "__MPI_COMM_WORLD__ "
      //           <<  communicator_type_loaded ()
      //           << " "
      //           << octave_mpi_communicator::static_type_id ()
      //           << std::endl;
      // COMMUNICATOR_TYPE_LOAD (interp);
      // std::cout << "__MPI_COMM_WORLD__ "
      //           <<  communicator_type_loaded ()
      //           << " "
      //           << octave_mpi_communicator::static_type_id ()
      //           << std::endl;
      retval = new octave_mpi_communicator (MPI_COMM_WORLD);
    }  
  return retval;
}
