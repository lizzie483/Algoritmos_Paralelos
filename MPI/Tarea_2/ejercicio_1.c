#include "mpi.h"
#include <math.h>
#include <stdio.h>

int main(argc,argv)
int argc;
char *argv[];
{
    int done = 0, n, rank_id, size, i;
    double PI_REAL = 3.141592653589793238462643;
    double pi_local, pi, h, sumatoria, x;
    double start_time, end_time;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_id);
    
	if (rank_id == 0) {
	    printf("Ingrese numero de intervalos por proceso (100 - 1000000):");
	    scanf("%d",&n);
	}
	//Inicio de tiempo
	start_time = MPI_Wtime();
	//Se usa Bcast para distribuir el numero de intervalos a todos los procesos
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	h   = 1.0 / (double) n;
	//Inicia el conteo para cada proceso
	sumatoria = 0.0;
	for (i = rank_id + 1; i <= n; i += size) {
	//Realizando la Suma de Riemman
	    x = h * ((double)i - 0.5);
	    sumatoria = sumatoria +( 4.0 / (1.0 + x*x));
	}
	pi_local = h * sumatoria;
    //Se suman todos los procesos en pi
	MPI_Reduce(&pi_local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);
	//Fin de tiempo
	end_time = MPI_Wtime();
    //El resultado se muestra solamente en el proceso 0
	if (rank_id == 0){
	    //printf("El valor de PI por integracion es %.16f \nValor real de PI: %.16f\n", pi, PI_REAL);
	    //printf("Error absoluto: %.16f\n", fabs(pi - PI_REAL));
	    printf("\nTiempo para %d intervalos y %d procesos en segundos %f\n",n,size , end_time - start_time);
	    }
    
    MPI_Finalize();
    return 0;
}

