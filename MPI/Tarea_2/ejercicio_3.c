#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
 
  long *array_1;
  int rank,size,i,size_of_array=1;
  array_1 = (long*)malloc(sizeof(long));
  double start_time, end_time;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  //Inicio de tiempo
  start_time = MPI_Wtime();
  int ping_pong_count = 0;
  int rank_vecino = (rank + 1) % 2;
  while (ping_pong_count < 18) {
  
    if (rank == ping_pong_count % 2) {
      //Duplicando el tamaño del array
      size_of_array =size_of_array*2;
      array_1 = (long*)malloc(sizeof(long) *size_of_array);
      
      //Enviar el tamaño antes de enviar el array
      MPI_Send(&size_of_array, 1, MPI_INT, rank_vecino, 0, MPI_COMM_WORLD);
      MPI_Send(array_1, size_of_array, MPI_INT, rank_vecino, 0, MPI_COMM_WORLD);
      
      ping_pong_count++;
      //printf("%d enviar y ping_pong_count %d a %d\nSize of array:%d\n",rank,ping_pong_count,rank_vecino,size_of_array);


      
    } else {
      //Recibir el tamaño antes de recibir el array ya duplicado de tamaño
      MPI_Recv(&size_of_array,1, MPI_LONG, rank_vecino, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      MPI_Recv(array_1, size_of_array, MPI_LONG, rank_vecino, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      
      ping_pong_count++;
      //printf("%d recibir y ping_pong_count %d to %d\nSize of array:%d\n",rank,ping_pong_count,rank_vecino,size_of_array);
    }
    //En cada seccion del if se debe aumentar el conteo del ping-pong
    //para llegar al array de tamaño 2^18. 
  }
  //fin de tiempo
  end_time = MPI_Wtime();
  if(rank==0){
	  printf("Tamaño de array final: %d\n",size_of_array);
	  printf("Tiempo de ejecucion: %f\n",end_time - start_time);
	  }
  MPI_Finalize();
}
