// Copyright 2021 Josef Ruzicka <josef.ruzicka@ucr.ac.cr> CC-BY-4
// Creates an arbitrary amound of threads that greet in stdout

//#include <errno.h>
//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

//void* run(void* data);

/**
int main(void) {
  FILE* input = stdin;
  FILE* output = stdout;
  
  printf("Enter numbers to test\n");
  long long value = 0;
  while (fscanf(input, "%lld", &value) == 1 ){
	 
  }
  printf("hola");
  input = fopen("input.txt", "r");
  while (fscanf(input,"%lld", &value) == 1) {
	printf("holi");
  }
  
  //fprintf(output, "%lld\n", value);
  
  //printf(string);
  
  return 0;
}


int main(void) {
  FILE* input = fopen("input.txt", "w");
  
  printf("Enter numbers to test\n");
  long long value = 0;
  
  // user inputs numbers until ctrl+D is pressed
  while (getchar() != EOF){
    
    if (fscanf(input,"%lld", &value) == 1) {
    fprintf(input,"%lld",value);
	}
	
  }
  
  fclose(input);
  
  input = fopen("input.txt", "r");
  printf("hol1");
  //while (getchar() != EOF) {
	  printf("hol1");
    fscanf(input,"%lld", &value);

    printf("Value of n=%lld", value);
     
  //}
  fclose(input);  
  
  return 0;
}
**/

int main(void) {
  FILE* input = stdin;
  long long value = 0;
  long long* numerosIngresados = malloc(10 * sizeof(long long));
  int posicionNumerosIngresados = 0;
  
  printf("Enter numbers to test\n");
    
  // user inputs numbers until ctrl+D is pressed.
  // the following code is based on the code shown at
  // http://jeisson.ecci.ucr.ac.cr/concurrente/2020c/lecciones/0118/
  // good_programming_practices.mp4, by Jeisson Hidalgo-Cespedes
  while (fscanf(input,"%lld", &value) == 1){
	  
	// reallocation of memory.
    if (posicionNumerosIngresados == sizeof(numerosIngresados)/
									 sizeof(numerosIngresados[0])){
	  numerosIngresados = (long long*) realloc(numerosIngresados
						   ,sizeof(numerosIngresados) + 10);
	}
	// input number is added to the array.
    numerosIngresados[posicionNumerosIngresados] = value;
    posicionNumerosIngresados++;
  }
  
  // reading.
  printf("---------\n");

  // deallocation of memory.
  free(numerosIngresados);
  return 0;
}
