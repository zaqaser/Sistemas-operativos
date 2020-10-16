//descripcion: Simulacion de filosofos comensales, se crean varios hilos que simularan los filosofos 
 //	no pueden comer 2 filosofos que esten continuos y se checa mediante la funcion test.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <random>
#include <chrono>

#define MAXHILOS 4 //Numero de hilos
#define N MAXHILOS 
//Definicion de los valores que utilizamos para el control de los filosofos
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
using namespace std;
//Declaracion de Semaforos
sem_t mutex;
sem_t S[N];

int state[N];

//Crear una variable random para realizar las funciones comer y pensar
int random (int lim)
{
    default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> uid(1,lim);
    return uid(dre);
}
//Creca cuando un filosofo puede comer
void test(int i){
	
	if((state[i] == HUNGRY) && (state[LEFT] != EATING) && (state[RIGHT] != EATING)){
		state[i] = EATING;
		printf("Soy el filosofo 1 comiendo\n", i);
		printf("Soy el filosofo 2 comiendo\n", i);
		sem_post(&S[i]);
	}
}
//Cuando un filosofo esta pensando
void put_forks(int i){
	sem_wait(&mutex);
	state[i] = THINKING;
	printf("Soy el filosofo %d pensando\n", i);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}
//Para que el filosofo cambie a hambriento
void take_fork(int i){
	sem_wait(&mutex);
	state[i] = HUNGRY;
	test(i);
	sem_post(&mutex);
	sem_wait(&S[i]);
}
void think(int j,int stomac){//Cuando el filosofo esta pensando
		//stomac=-random(100);
			//cout<<"Philosopher Thinking"<<endl;

		
}
void eat(int j,int stomac){//Cuando el filosofo esta comiendo
	//stomac=+random(100);
	//if(stomac=100)
		//cout<<"Philosopher full"<<endl;
		
	

		
	
}
void * philosopher(void *p){//Funciones que ejecutan los filosofos
  int i = *(int *) p;
    free(p);

	int stomac=100;
	int val=1;
	while(val=1){
		think(i,stomac);
		//if (stomac<=0){
			//cout<<"Philosopher dead"<<endl;
			//val= 0;};
		take_fork(i);
		eat(i,stomac);
		put_forks(i);
		
	};
	return NULL;
}
int main(){
	int i;
	int *p ;
	pthread_t hilo[MAXHILOS];//Declaración del numero de hilos
	
	sem_init(&mutex,0,1); //inicializa un semaforo mutex con el valor de 1	
	for (i = 0; i < N; ++i)
		sem_init(&S[i],0,0); 

	for (i = 0; i < MAXHILOS; ++i)
		*p = i;
		pthread_create(&hilo[i],NULL,&philosopher,p); //El hilo ejecuta la función philosopher().
	
	for (i = 0; i < MAXHILOS; ++i)
		pthread_join(hilo[i],NULL); //Para esperar a los hilos creados	
	
	return 0;
}