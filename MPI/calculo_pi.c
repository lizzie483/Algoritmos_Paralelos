#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
 
int main (int argc, char *argv[]) 
{
	int rank, n_procs, n_dentro, puntos, i;
	double pi_local, pi_total, x, y, z, error;

	//Cantidad total de puntos dentro del circulo.
	n_dentro = 0;
	puntos = 10000;

	//Paralelismo
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	//Obtención de los puntos aleatorios
	srand(time(NULL));
	int p_particion;
	p_particion = puntos/n_procs;
	
	for (i = 1; i <= p_particion; i++) {
			x = (double) rand() / RAND_MAX;
			y = (double) rand() / RAND_MAX;
			z = x*x + y*y;
					//Esto indica que dicha coordenada (x,y) se encuentra dentro del circulo de radio 1.
			if (z <= 1.0){
				n_dentro+=1;}
			}
	
	//Luego calcular PI 
	pi_local = 4.0 * (double)n_dentro/(double)puntos;

	//Sumando los resultados de cada proceso
	MPI_Reduce(&pi_local, &pi_total, 1, MPI_DOUBLE, MPI_SUM, 0 , MPI_COMM_WORLD);
	//if (rank!= 0)
		//printf("Valor local de PI: %f, del proceso: %d de %d\n", pi_local, rank,n_procs);

	MPI_Barrier(MPI_COMM_WORLD);

	//Se define que solo el proceso 0 va a tener el valor total de pi
	if (rank == 0)
	{
		//Promedio del valor obtenido en cada proceso

		
		printf("Valor obtenido:	%11.10f\n", pi_total);
		
	}

	//Fin Paralelismo
	MPI_Finalize();

	return 0;
}
