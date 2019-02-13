## Copyright (C) 2017,2018 Carlo de Falco
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free Software
## Foundation; either version 3 of the License, or (at your option) any later
## version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License along with
## this program; if not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {[@var{comm}]} = MPI_COMM_WORLD ()
##  Octave representation of the MPI_COMM_WORLD communicator.
## @end deftypefn

function o = MPI_COMM_WORLD ()
  o = __MPI_COMM_WORLD__ ();
endfunction
