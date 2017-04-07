#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  
  MPI_Init(NULL, NULL);
  int size;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int message;
  //Condicion para recibir el mensaje del proceso anterior, menos caso de 0 a 6
  if (rank != 0) {
    MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Proceso %d recibió mensaje %d del proceso %d\n", rank, message,rank - 1);
  }
  //Mensaje transmitido
  message = 1000 + 100*rank ;
  //Proceso al que se enviara el mensaje
  int next = (rank+1)%size;
  //Envio para todos los casos
  MPI_Send(&message, 1, MPI_INT, next, 0,MPI_COMM_WORLD);
  //Caso particular de recepcion de mensaje para 0
  if (rank == 0) {
    MPI_Recv(&message, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Proceso %d recibió mensaje %d de proceso %d\n", rank, message,size - 1);
  }
  MPI_Finalize();
}
