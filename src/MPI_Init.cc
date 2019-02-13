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

#include <mpi.h>
#include <octave/oct.h>
#include "octave_mpi_communicator.h"

// PKG_ADD: autoload ("MPI_Init", "MPI_Init.oct");
DEFMETHOD_DLD (MPI_Init, interp, args, nargout,"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} @var{INFO} = MPI_Init ()\n\
Initialize the MPI execution environment.\n\
\n\
 @example\n\
 @group\n\
    @var{INFO} (int) return code\n\
       0 MPI_SUCCESS    No error\n\
      16 MPI_ERR_OTHER  Attempt was made to call MPI_Init a  second  time\n\
                       MPI_Init may only be called once in a program\n\
                       \n\
SEE ALSO: MPI_Finalize, MPI_Initialized, MPI_Finalized\n\
@end group\n\
@end example\n\
@end deftypefn")
{

  int nargin = args.length ();
  int info   = MPI_ERR_ARG;

  // std::cout << "MPI_Init "
  //           <<  communicator_type_loaded ()
  //           << " "
  //           << octave_mpi_communicator::static_type_id ()
  //           << std::endl;
  // COMMUNICATOR_TYPE_LOAD (interp);
  // std::cout << "MPI_Init "
  //           <<  communicator_type_loaded ()
  //           << " "
  //           << octave_mpi_communicator::static_type_id ()
  //           << std::endl;
  
  for (int i = 0; i < nargin; i++)
    if (! args(i).is_string ())
      {
        error ("MPI_Init: arguments must be all strings");
        return octave_value (info);
      }
  
  string_vector argvec = args.make_argv ("MPI_Init");
  char **argve= argvec.c_str_vec () + 1;
  
  info = MPI_Init (&nargin, &argve);
  return octave_value (info);
}
 
