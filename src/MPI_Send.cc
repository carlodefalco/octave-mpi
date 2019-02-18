// Copyright (C) 2012, 2013, 2014, 2015, 2017 Carlo de Falco
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

#include <string>
#include <sstream>

#include <oct-map.h>
#include <octave/load-save.h>
#include <octave/ls-oct-binary.h>
using namespace octave;

static const load_save_format frmt = load_save_system::BINARY;
static const octave::mach_info::float_format flt_fmt = octave::mach_info::flt_fmt_unknown;
static const bool swap = false;
static const std::ios::openmode omode = std::ios::out | std::ios::binary;

// PKG_ADD: autoload ("MPI_Send", "MPI_Init.oct");
DEFMETHOD_DLD (MPI_Send, interp, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{INFO} =} MPI_Send(@var{VALUE},@var{RANKS},@var{TAG},@var{COMM})\n\
Transmit an Octave variable as a set of MPI message.\n\
Return an integer @var{INFO} to indicate success or failure.\n\
@example\n\
@group\n\
@var{VALUE} must be an octave variable \n\
@var{RANKS} must be a vector containing the list of rank destination processes \n\
@var{TAG} must be an integer to identify the message by openmpi \n\
@var{COMM} must be an octave communicator object created by MPI_Comm_Load function \n\
@end group\n\
@end example\n\
\n\
@seealso{MPI_Comm_Load,MPI_Init,MPI_Finalize,MPI_Recv}\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();
  if (nargin != 4 )
    print_usage ();
  else
    {
      int mytag = args(2).int_value ();
      if (! error_state)
        {
          if (is_octave_mpi_communicator (args(3)))
            {
              MPI_Comm comm = ov_mpi_comm (args(3));
              std::stringstream file (omode);
              //write_header (file, frmt);

              if (! save_binary_data (file, args(0),
                                      "mpi_message",
                                      "", false, false))
                { retval = MPI_ERR_OTHER; }
              else
                {
                  // std::cerr << "encoded data :" << file.str () << std::endl;
                                    
                  std::string s = file.str ();
                  int num = s.length ();
                  Array<int> dest = args(1).int_vector_value ();
                  Array<octave_int32> info (dim_vector (dest.numel (), 1));
                  for (octave_idx_type iproc = 0; iproc < dest.numel (); ++ iproc)
                    info(iproc) = MPI_Send (&(s.c_str ()[0]), num,
                                            MPI_CHAR, dest(iproc),
                                            mytag, comm); 
                  // int rank;
                  // MPI_Comm_rank (comm, &rank);
                  // std::cerr << "data sent from rank " << rank << " to " << ", info :" << info << std::endl;
                  comm = NULL;
                  retval = info;
                }
            }
          else 
            error ("MPI_Send: Please enter octave comunicator object!");
        }
    }
  return retval;
}

