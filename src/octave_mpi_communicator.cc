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

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_mpi_communicator,
                                     "octave_mpi_communicator",
                                     "octave_mpi_communicator");

static bool flag = false;

bool
communicator_type_loaded ()
{ return flag; };

void
communicator_type_loaded (bool in)
{ flag = in; }; 


MPI_Comm
ov_mpi_comm (const octave_value &in)
{
  const octave_base_value& rep = in.get_rep ();
  const octave_mpi_communicator& B = ((const octave_mpi_communicator &)rep);
  MPI_Comm comm = ((const octave_mpi_communicator&) B).comunicator_value ();
  return comm;
}

bool
is_octave_mpi_communicator (const octave_value &in)
{
  return (in.type_id () == octave_mpi_communicator::static_type_id ());
}
