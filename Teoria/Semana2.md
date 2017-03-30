#### MPI_Bcast ####
Copia el mismo valor en todos.
Sea **MPI_Bcast(&data,1,MPI_INIT,0,MPI_COMM_WORLD)**. El valor que se envia a todos los procesos es **_data_**.

Se implemeta el Bcast dentro de un condicional, si se inicia en el proceso cero. De esta forma se garantiza que copie de 0 al resto.

