# Vikingos Destructores

Para el proyecto grupal del curso paralela y concurrente


## CONTENIDOS
   
* Introducción
* Requerimientos
* Mantenedores

## INTRODUCCIÓN

En este proyecto se modifica el programa basado en un servidor web, el cual funciona de manera serial (solamente atiende una solicitud
a la vez) y siempre responde con las mismas sumas por defecto. Se modificara de manera que se  ejecute de manera concurrente. 
Se realiza un diseño el cual permite que la cantidad de hilos sea ingresada por el usuario o si la cantidad no es ingresada, 
el número predeterminado por el programa de hilos realice las diferentes tareas de forma concurrente. Esta cantidad de hilos
determinará la máxima cantidad de clientes que el servidor podrá antender concurrentemente.
En este programa estas tareas serían la sumas de Goldbach ingresadas por distintos clientes (usuarios). 

La conjetura de Goldbach, explica que todo numero mayor a 5 puede ser calculado como la suma de numeros primos, la conjetura fuerte dice que todo numero par y mayor a 5 puede ser representado como al menos una suma de dos numeros primos. Por otra parte la conjetura debil dice que todo numero impar puede ser representado por la suma de 3 numeros primos.

En este trabajo para representar la conjetura de Goldbach, se crea un "GoldbachCalculator", que toma los numeros ingresados por el usuario, mediante los sockets y calcula sus sumas goldbach.

## REQUERIMIENTOS

Para realizar el programa de manera concurrente se tomaron en cuenta los siguientes requerimientos

* Modificar el mensaje de respuesta que inicialmente responde siempre con los mismos números, para que
* responda con las sumas correctas
* Editar la expresión regular para que acepte más de un número y también números negativos.
* Atender varias solicitudes de forma concurrente, con varios hilos de ejecución.
* Implementar el modelo productor-consumidor para las solicitudes web, de manera que la clase WebServer funcione como un único productor
* de solicitudes web. 
* Asegurar que la cantidad de hilos solicitados no sobrepasen la cantidad máxima de hilos que se pueden crear.
* Crear la clase HttpConnectionHandler los cuales serán los consumidores de solicitudes y se encargaran de brindar 
* las sumas de goldbach solicitadas.
* Implementar una clase GodlbachWebApp encargada de que se encarga de recibir las solicitudes HTTP que realiza el cliente, 
* extraer los números, pasarlos al GoldbachCalculator, 
* obtener las sumas de éste, ensamblar y despachar las respuestas HTTP.
* Implementar GoldbachCalculator: que se encarga de encontrar las sumas de primos de números solicitados y almacenarlas en 
* estructuras de datos en memoria.
* Implementar los métodos de sumas de goldbach en el código y verificar el funcionamiento concurrente.

## MANUAL DE USUARIO
 1. Primeramente para iniciar el servidor web se debe compilar el programa con el siguiente comando :
  ./bin/executable port max_connections 
  En donde port representa el puerto en el que se encontrara el servidor, por ejemplo : "8080" y el max_connections el numero maximo de conecciones que el servidor podra manejar en el momento.
  2. Luego se debe abrir un navegador y en la barra de busqueda poner "localhost/port", esto deplegara una vista en la cual se puede agregar los numeros a los cuales se desea observar sus sumas de goldbach.

 ## MANTENEDORES

Mantenedores actuales:

* Samantha Romero - B87033
* Carlos Solórzano -B87741
* Josef Ruzicka -B87095


Este proyecto es brindado por:

*  Allan Berrocal
*  Andrés Mena Arias
*  Jeisson Hidalgo
Para el proyecto grupal del curso paralela y concurrente


## CONTENIDOS
   
* Introducción
* Requerimientos
* Mantenedores


