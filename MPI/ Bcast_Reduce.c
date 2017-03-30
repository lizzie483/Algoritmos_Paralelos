int main(int argc, char *argv[]){
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &me);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
...
MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);

MPI_Reduce(&data,&res, DATA_SIZE, MPI_INIT,MPI_SUM,0,MPI_COMM_WORLD);

if(me==0){
//Impirmir resultado proceso 0

}
MPI_Finalize();
}
