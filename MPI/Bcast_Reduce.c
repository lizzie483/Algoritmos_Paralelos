int main(int argc, char *argv[]){
  //Inicializacion de variables
int me,numprocs;
float data,res;
int valor=10;
float numero=1.2;
 //Todo lo que se escribe antes del MPI_Init no funciona de forma paralela, sucede una unica vez en el proceso "0" 
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &me);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
//MPI_Barrier
  data=20.5; //este dato esta en todos los procesos
MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD); //Copia en un sitio donde ya esta copiado
  //Revisar el funcionamiento del codigo comentando el Bcast
MPI_Barrier(MPI_COMM_WORLD);
  //Colocar la barrera antes del calculo para que 
  //garantize un sincronizmo antes de que la sume se realize
  //Si hay un proceso que no tiene la data correcta se garantiza de 
  //que antes que se reduzca el reduce todo se haya logrado.
MPI_Reduce(&data,&res, 1, MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

//Este if nos indica que solo el proceso 0 va a tener el resultado final, 
  //los demas procesos tiene un valor no definido de res
if(me==0){
//Impirmir resultado proceso 0
  printf("Proceso %d, res: %d",me,res);
  //MPI_COMM_WORLD es una variable, que es un entero que empieza de cero, es para separar
  //La cantidad de procesos que forman parte del bloque, PARTICION

}
MPI_Finalize();
  return 0;
}
