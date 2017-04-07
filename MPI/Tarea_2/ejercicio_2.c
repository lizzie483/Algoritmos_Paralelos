#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


float promedio (float* a, int n)
{
    int i;
    float sum = 0;
    for (i=0; i<n; ++i) {
        sum += a[i];
    }
    return sum/n;
}

int main (int argc, char *argv[])
{
    float *array, *sub_array;
    float *sub_a_prom;
    int i, j, size, rank, to, from, k, num = 1024;
    int size_sub_a;
    float promedio_total;
    float start_time, end_time;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    //Inicio tiempo
    start_time = MPI_Wtime();
    size_sub_a = 1024/size;
    if (rank == 0) {
        array = (float*) malloc(sizeof(float) * num);
        for (i=0; i<num; ++i) {
            array[i] = rand() % 100+1;
        }
    }
    
    sub_array = (float*) malloc(sizeof(float) * size_sub_a);

    MPI_Scatter(array, size_sub_a, MPI_FLOAT, sub_array,size_sub_a, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float sub_avg = promedio(sub_array, size_sub_a);

    printf ("Proces %d: %f\n", rank, sub_avg);

    if (rank == 0) {
        sub_a_prom = (float*) malloc(sizeof(float) * size);
    }
    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_a_prom, 1, MPI_FLOAT, 0,
                   MPI_COMM_WORLD);
    
    if (rank == 0) {
        promedio_total = promedio(sub_a_prom, size);
        }
    //Fin tiempo
	end_time = MPI_Wtime();        
	if(rank==0){        
		printf("tiempo1: %f\n",start_time);
        printf("tiempo2: %f\n",end_time);
        printf ("Promedio total: %f\n", promedio_total);
        printf("Tiempo de ejecucion: %f\n",end_time - start_time);
    
    }

    MPI_Finalize ();
return 0;
}
