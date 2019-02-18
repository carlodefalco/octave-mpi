// Copyright (C) 2012, 2013, 2014, 2017 Carlo de Falco
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
static octave::mach_info::float_format flt_fmt = octave::mach_info::native_float_format ();
static bool swap = false;
static const std::ios::openmode imode = std::ios::in | std::ios::binary;
static bool dummy;
static std::string doc ("");

// PKG_ADD: autoload ("MPI_Recv", "MPI_Init.oct");
DEFMETHOD_DLD (MPI_Recv, interp, args, nargout,"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} [@var{VALUE} @var{INFO}] = \
MPI_Recv(@var{SOURCE},@var{TAG},@var{COMM})\n\
Receive an MPI message containing an Octave variable and extract its value.\n\
The Octave variable being received is returned as @var{VALUE},\n\
while @var{INFO} is an integer indicating success or failure.\n\
 @example\n\
 @group\n\
@var{SOURCE} must be an integer indicating source processes \n\
@var{TAG} must be an integer to identify the message by openmpi \n\
@var{COMM} must be an octave communicator object created by \
MPI_Comm_Load function \n\
@end group\n\
@end example\n\
@seealso{MPI_Comm_Load,MPI_Init,MPI_Finalize,MPI_Send}\n\
@end deftypefn")
{
  octave_value_list retval;
  retval(0) = "";
  int nargin = args.length ();
  if (nargin != 3)
    print_usage ();
  else
    {
      int source = args(0).int_value ();    
      int mytag = args(1).int_value ();
      if (! error_state)
        {
          if (is_octave_mpi_communicator (args(2)))
            {
              MPI_Comm comm = ov_mpi_comm (args(2));
              int num;
              MPI_Status status;

              MPI_Probe (source, mytag, comm, &status);
              MPI_Get_count (&status, MPI_CHAR, &num);
              char buffer[num];
              
              int info =
                MPI_Recv (buffer, num, MPI_CHAR, source,
                          mytag, comm, &status);
              
              if (info == MPI_SUCCESS)
                {
                  std::stringstream file (imode);
                  file.str (std::string (buffer, num));
                  
                  // if (read_binary_file_header (file, swap, flt_fmt, true) != 0)
                  //   {
                  //     info = MPI_ERR_OTHER;
                  //     std::cerr << "error decoding data" << std::endl;
                  //   }
                  // else
                    {
                      std::string nm = read_binary_data (file, swap, flt_fmt, "",
                                                         dummy, retval(0), doc);
                      if (nm != "mpi_message")
                        std::cerr << "unexpected message name";
                    }                
                }

              comm = NULL;
              retval(1) = octave_value (info);

            }
          else
            {
              error ("Please enter octave comunicator object!");
              retval = octave_value (-1);
            }
        }
    }
  return retval;
}
