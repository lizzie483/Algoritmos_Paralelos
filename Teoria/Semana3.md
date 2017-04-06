# Paralelismo 

## Procesamiento de Imagenes

Solo las coordenadas del pixel son modificada. Se toma especial cuidado en la distribucion de la imagen entre procesos, normalmente se separa la imagen en regiones cuadradas, o en lineas y columnas.

### Paralelismo Ideal
Si se necesitan dos pasos de transformacion para cada pixel. Tendremos una secuencia de calculos de nxn pixeles en tiempo O(n^2). Para p procesos, cada uno con 4 resultados (antiguas y nuevas coordenadas), es el tiempo de comunicación: O(p+n^2).

## Mandelbrot Set
Es un set de puntos complejos, que se calculan a través de la iteración de una funcion compleja no-divergente. 

Cada pixel puede ser calculado independientemente del reso (el cálculo individual del pixel no es paralelizable).
**Distribución estática de tareas:**cada pixel necesita un numero distinto de iteraciones, por lo que cada proceso recibe una porcion de la imagen, y no terminan sincronizadas entre ellas, lo que torna ineficiente al algoritmo.
### Paralelismo
**Distribución dinámica de tareas:**se distribuyen en un **work pool**, desde donde cada proceso obtiene una nueva tarea.

En esta representacion el tiempo va a ser proporcinal a n.

## Método Monte Carlo
Utiliza principios del cálculo probabilistico y estadistica para aproximas soluciones de problemas complejos.
### Paralelismo
Calculo de una integral, esta puede calcularse a través de la generacion de N valores aleatorios. El que los numeros se autogeneren de forma aleatoria es mas confiable, ya que se vuelve realista.

## Paradigma Divide y Venceras

En un calculo de la suma de n/p numeros la eficiencia maxima es p.
### Bucket Sort

Utiliza un metodo de particionamiento. Funciona mejor con conjuntos homogeneos. Un intervalo `a` se separa en `m` regiones (**buckets**). En cada bucket se realiza un ordenamiento `quicksort` o `mergesort`.

