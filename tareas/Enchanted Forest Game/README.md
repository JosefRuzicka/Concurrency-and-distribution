# Vikingos Destructores

Para el proyecto 2 grupal del curso paralela y concurrente (version Paralela)


## CONTENIDOS
   
* Introducción
* Requerimientos
* Mantenedores

## INTRODUCCIÓN

En este proyecto se realiza un programa el cual consiste en realizar un tipo de juego donde exite un bosque el cual tiene un rey que esta aburrido y decide hechizar el bosque cada noche para cambiar el lugar. Para implementar esta programa se penso en crear una clase "Wizard" el cual seria como el hechicero que ayuda al rey, una clase "Forest", la cual seria el bosque a hechizar cada noche, una clase "WorkOrder" la cual indicaria la cantidades de mapas del bosque a modificar, una clase "SpellSimulator". La cual tendria como las funcionaes para cambiar los bosques, es decir los "hechizos", con la finalidad de retornar un archivo con los mapas modificados ingresados al programa.



## REQUERIMIENTOS

Para realizar el programa de manera  tomaron en cuenta los siguientes requerimientos

* Realizar una clase Forest la cual tendra los mapas con sus funciones para poder modificarlos.
* Realizar una clase SepellSimulator la cual tendra las funciones para hacer los respectivos cambios dependiendo del contenido del     bosque
* Realizar una clase WorkOrder la cual contendra la cantidad y todos los mapas contenidos en el JobFile
* Realizar una clase Wizard la cual llamara las respectivas funciones para hacer modificaciones en los bosques.
* Asegurar que la cantidad de hilos solicitados no sobrepasen la cantidad máxima de hilos que se pueden crear.
* Crear nuevos archivos por cada noche de los bosques modificados.
* Se aplica el uso de la biblioteca openMP.

## MANUAL DE USUARIO

Para ejecutar el programa de manera concurrente se tomo en cuenta lo siguiente: 

Para ejecutar se debe abrir correr el siguiente comando en la terminal desde la
carpeta que contiene los archivos del programa:

mpiexec -n 3 -f Hosts.txt ./bin/Avance02_correccion job001.txt ./tests/input/

Los parametros utilizados para correr el programa son:

1. El comando para ejecutar mpi (mpiexec)
2. La cantidad de procesos que se deben ejecutar
3. El archivo con los hosts, es decir, los nodos que deben ejecutar los 
   procesos
4. El ejecutable (./bin/proyecto02_avance02)
5. El nombre del archivo (Job)
6. La ruta que direcciona el lugar donde se encuentran los mapas y Jobs a utilizar

Salida esperada :

Por cada mapa dentro del job se crea un archivo de salida con el nombre del mapa y la cantidad de medias noches que transcurrieron.
Ejemplo : "map001-10.txt" 
Si el numero de noches ingresado en el en el archivo de job de cada mapa es positivo se imprimen el bosque resultante despues de cada medianoche de lo contrario se imprime solo el bosque original y el bosque al finalizar la ultima medianoche.

Un ejemplo de lo que podria venir en cada archivo en la salida es el siguiente:


0:
|-------|
|-l--l--|
|-ll----|
|-l-----|
|---laa-|
|-aa-al-|
|a-a----|
1:     
|-------|
|-------|
|-ll----|
|-------|
|----aa-|
|-aaaa--|
|aaaa---|


Si el numero de noches ingresado en el en el archivo de job de cada mapa es positivo se imprimen el bosque resultante despues de cada medianoche de lo contrario se imprime solo el bosque original y el bosque al finalizar la ultima medianoche.

## ANALISIS DE RENDIMIENTO

![graficoProyecto2Avance2.jpeg](https://git.ucr.ac.cr/SAMANTHA.ROMERO/vikingos-destructores/-/blob/master/proyecto_02/Avance02_correccion/design/graficoProyecto2Avance2.jpeg)

Tiempos de durasion: 
serial  7602s
OMP     1847s
MPI+OMP 1323s     

Las decisiones tomadas sobre la descomposicion y mapeo permitieron obtener los resultados esperados, ya que se obtuvo un speedup de 4.116 con el uso de la tecnologia openMP para dividir los chequeos de cada celda entre hilos, ya que esto permite que se revisende manera concurrente una celda por cada nucleo activo en el sistema. Lo mismo sucede con los resultados del MPI+OMP, tuvimos un speedup de 5.746 ya que se dividen los mapas entre las diferentes computadoras disponibles y se pueden realizar varios mapas de manera concurrente, sin embargo puede ser ineficiente cuando los mapas tienen una distribucion en la que los mapas mas pesados vienen muy pegados en el orden de ejecucion ya que al utilizar un mapeo estatico, a un proceso podrian tocarle los mapas mas pesados y los otros procesos terminarian su trabajo mas rapido, esto se solucionaria utilizando un mapeo dinamico en la distribucion de los mapas, o uno aleatorio.
Al realizar la prueba de MPI con tantos procesos como nucleos activos tenga el sistema, se obtuvo un speedup de 4,698, lo cual no es mejor que la combiancion de MPI+OMP, la hipotesis realizada por el equipo indica que esto se debe a que cuando en un solo sistema hay varios mapas activos en un mismo instante, se requiere mas memoria activa para trabajarlos a todos, mientras que en en el sistema con un solo mapa trabajado por varios hilos solo se requiere la memoria de ese unico mapa, y esto agiliza el proceso. 

## MANTENEDORES

Mantenedores actuales:

* Samantha Romero  - B87033
* Carlos Solórzano - B87741
* Josef Ruzicka    - B87095


Este proyecto es brindado por:

*  Allan Berrocal 
*  Jeisson Hidalgo
*  Andrés Mena

Para el proyecto grupal del curso paralela y concurrente
