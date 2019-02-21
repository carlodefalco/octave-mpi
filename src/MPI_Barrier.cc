// Copyright (C) 2004-2007 Carlo de Falco
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

// PKG_ADD: autoload ("MPI_Barrier", "MPI_Init.oct");
DEFMETHOD_DLD (MPI_Barrier, interp, args, ,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} @var{INFO} = MPI_Barrier (@var{COMM})\n\
Block processes in the communicator @var{COMM} until the call to this routine has been reached by all.\n\
The communicator object @var{COMM} must be specified otherwise \n\
an error occurs. \n\
 @example\n\
 @group\n\
    @var{INFO} (int) return code\n\
       0 MPI_SUCCESS    No error\n\
       5 MPI_ERR_COMM   Invalid communicator (NULL?)\n\
      13 MPI_ERR_ARG    Invalid argument (typically a NULL pointer?)\n\
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
      
      if((args.length () != 1)
         || ! is_octave_mpi_communicator (args(0)))
        {
          error ("MPI_Barrier: Please enter octave comunicator object");
          results(0) = octave_value (-1);
        }
      else
        {	       
          MPI_Comm comm = ov_mpi_comm (args(0));
          if (! error_state)
            {
              int my_size;
              int info = MPI_Barrier (comm);
              
              results(0) = octave_value (info);
            }
          else
            print_usage ();
        }
    }
   
  return results;
}

