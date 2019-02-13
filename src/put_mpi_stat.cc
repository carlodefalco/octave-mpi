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

#include <mpi.h>
#include <octave/ov-struct.h>

octave_scalar_map
put_MPI_Stat (MPI_Status &stat)
{
  octave_scalar_map map;
  octave_value tmp = stat.MPI_SOURCE;
  map.assign ("MPI_SOURCE", tmp);
  tmp = stat.MPI_TAG;
  map.assign ("MPI_TAG", tmp );
  tmp = stat.MPI_ERROR;
  map.assign ("MPI_ERROR", tmp );

  int itmp;
  MPI_Get_count (&stat, MPI_CHAR, &itmp);
  map.assign ("MPI_Get_count", itmp);
  MPI_Test_cancelled (&stat, &itmp);
  map.assign ("cancelled", itmp);
  return map;
}
