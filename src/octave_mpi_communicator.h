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

#include "mpi.h"
#include <octave/oct.h>
#include <octave/interpreter.h>

class
octave_mpi_communicator
  : public octave_base_value
{

 public:

  octave_mpi_communicator (MPI_Comm _rep = MPI_COMM_WORLD)
    : octave_base_value (), rep (_rep) {  }
  
  void
  print (std::ostream& os, bool pr_as_read_syntax = false) 
  { os << "MPI Communicator Object" << std::endl; }

  ~octave_mpi_communicator () { rep = NULL; }

  bool
  is_defined (void) const
  { return true; }

  MPI_Comm
  comunicator_value (bool = false) const
  { return rep; }
  
 private:
  
  MPI_Comm rep;
  
  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA;
};


bool
communicator_type_loaded ();

void
communicator_type_loaded (bool);

#define COMMUNICATOR_TYPE_LOAD(INTERP)            \
  if (! communicator_type_loaded ())              \
    {                                             \
      octave_mpi_communicator::register_type ();  \
      communicator_type_loaded (true);            \
      INTERP.mlock ();                            \
    }                                             \

MPI_Comm
ov_mpi_comm (const octave_value &in);

bool
is_octave_mpi_communicator (const octave_value &in);
