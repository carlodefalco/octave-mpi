## Copyright (C) 2009 Riccardo Corradini <riccardocorradini@yahoo.it>
## Copyright (C) 2012 Carlo de Falco
## Copyright (C) 2015 Alexander Barth
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
## @deftypefn {Function File} {} = test_mpi_send_receive ()
## This function test the sending and receiving various data types over MPI.
## The master (rank = 0) will send a message to all processes and the results 
## will be checked.
## To run this test, set the variables HOSTFILE and NUMBER_OF_MPI_NODES (you 
## need at least two nodes) to appropriate values, then type the following 
## command in your shell:
## @example
## mpirun --hostfile $HOSTFILE -np $NUMBER_OF_MPI_NODES octave --eval 'pkg load mpi; test_mpi_send_receive ()'
## @end example
## @seealso{hello2dimmat,helloworld,hellostruct,hellocell,hellosparsemat,mc_example,montecarlo,Pi} 
## @end deftypefn

function test_mpi_send_receive ()

  MPI_Init ();
  CW = MPI_COMM_WORLD;

  my_rank = MPI_Comm_rank (CW);
  p = MPI_Comm_size (CW);

  TAG = 1;

  message = 123.4;
  send_receive_check(message, "double scalar")

  message = single(123.4);
  send_receive_check (message, "single scalar")

  message = true;
  send_receive_check (message, "boolean")

  message = "a message";
  send_receive_check (message, "string")

  message = magic(5);
  send_receive_check (message,"2d array")

  message = cat (3, magic (5), 2 * magic (5));
  send_receive_check (message, "3d array")

  message = struct ("f1", 1, "f2", 25);
  send_receive_check(message,"scalar struct")

  message = struct ("f1", {1 3; 2 4}, "f2", 25);
  send_receive_check(message,"struct")

  ## does not work jet (10/06/2015)
  message = {"this","is","a","test"};
  send_receive_check(message,"cell")

  clear message
  message.f1 = 123;
  message.f2.g1 = "string";
  message.f2.g2 = magic (3);
  message.f3 = {"a", "b", "c"};
  send_receive_check (message, "complex struct")
  

  MPI_Finalize ();



  function send_receive_check (message, type)

    ## send to single node
    ## need at least two nodes

    if p >= 2
      if my_rank == 0
        ## send message to rank 1
        info = MPI_Send (message, 1, TAG, CW);
      endif
      
      if my_rank == 1
        [messagerec, info] = MPI_Recv (0, TAG, CW);

        test = sprintf ("%s (rank %d):",type,my_rank);
        
        if isequal (message,messagerec)
          printf ("%50s [ OK ]\n",test)
        else
          printf ("%50s [FAIL]\n",test)
          message,messagerec
        endif
      endif
    endif

    info = MPI_Barrier (CW);

    TAG = TAG+1;

    ## broadcasting

    if my_rank == 0
      ## send message to all nodes (including master)
      info = MPI_Send (message, 0:p-1, TAG, CW);
    endif

    ## receive from master
    [messagerec, info] = MPI_Recv (0, TAG, CW);
    
    test = sprintf ("broadcast %s (rank %d):",type,my_rank);

    if isequal (message,messagerec)
      printf ("%50s [ OK ]\n",test)
    else
      printf ("%50s [FAIL]\n",test)
      message,messagerec
    endif

    TAG = TAG+1;

    info = MPI_Barrier (CW);
  endfunction

endfunction

