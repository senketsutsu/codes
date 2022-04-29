#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 // sets the size of the buffor

sem_t sem_p; // semaphore for the producer (has a number 10-0 and is telling us if the producer has any space in the buffer so they can produce a new item)
sem_t sem_c; // semaphore for the consumer (has a number 10-0 and is telling us if the consumer has any item in the buffer that they can take)

pthread_mutex_t mutex_FI; // mutex for free indx
pthread_mutex_t mutex_TI; // mutex for taken indx

int buffer[BUFFER_SIZE]; 

// circular queue of free indexes
int free_indx[BUFFER_SIZE]; // list of indexes of the buffor that are free (no data)
int addition_free_index = 0; // at this index of the list you add the index of the buffor that is now free
int removal_free_index = 0; // at this index of the list you take the index of the buffor that is free 

// circular queue of taken indexes
int taken_indx[BUFFER_SIZE] = { };  // list of indexes of the buffor that are taken
int addition_taken_index = 0; // at this index of the list you add the index of the buffor that is now taken
int removal_taken_index = 0; // at this index of the list you take the index of the buffor that is taken

int count = 0; // counting all already produced elements


void* producer(void* args) {
    int x1,x2;
    while (1) {

        sem_wait(&sem_p);
        // produce
        pthread_mutex_lock(&mutex_FI);

        x1 = count;
        count++;
        x2 = free_indx[removal_free_index];
        free_indx[removal_free_index] = -1;
        removal_free_index=(removal_free_index+1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex_FI);
        // to make the producing time different we do this: 
        if(x1%2==0)
        {
            sleep(1);
        }else{
            sleep(2);
        }
        // consume
        // we are putting it in a free spot in the buffer
        buffer[x2] = x1;
        // we are signing the slot in the buffer as taken by adding it to the taken queue
        pthread_mutex_lock(&mutex_TI);

        taken_indx[addition_taken_index]=x2;
        addition_taken_index=(addition_taken_index+1)%BUFFER_SIZE;


        // now we can free the mutex and increase the number in the costumer semaphore which will signal to the costumers if they were waiting that now they have something to buy
        pthread_mutex_unlock(&mutex_TI);
        sem_post(&sem_c);
    }
}


void* consumer(void* args) {
    int y1,y2;
    while (1) {
        // consume
        sem_wait(&sem_c);
        pthread_mutex_lock(&mutex_TI);
        
        y2 = taken_indx[removal_taken_index];
        taken_indx[removal_taken_index] = -1;
        removal_taken_index=(removal_taken_index+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_TI);
        // we are getting a product from the buffer
        y1 = buffer[y2];
        //buffer[y2]=0;
        // we are putting the index back to the free ones
        pthread_mutex_lock(&mutex_FI);
        free_indx[addition_free_index]=y2;
        addition_free_index=(addition_free_index+1)%BUFFER_SIZE;

        // now we can free the mutex and increase the number in the costumer semaphore which will signal to the costumers if they were waiting that now they have something to buy
        sleep(1);
        pthread_mutex_unlock(&mutex_FI);
        sem_post(&sem_p);

        // Consume
        printf("Consumed: %d\n", y1);
        
    }
}

int main(int argc, char* argv[]) {

    printf("\t *** \t The producer-consumer problem\t *** \n");

    int number_of_producers = 0;
    int number_of_consumers = 0; 

    // get the values while they are >0

    printf("Enter the number of the producers (it has to be higher then 0): ");
    while(number_of_producers<=0)
    {
        scanf("%d", &number_of_producers);
    }

    printf("Enter the number of the consumers (it has to be higher then 0): ");
    while(number_of_consumers<=0)
    {
        scanf("%d", &number_of_consumers);
    }

    srand(time(NULL));

    pthread_t th[(number_of_consumers+number_of_producers)];
    pthread_mutex_init(&mutex_FI, NULL); // initialize mutexes
    pthread_mutex_init(&mutex_TI, NULL);
    sem_init(&sem_p, 0, BUFFER_SIZE); // semaphore with the starting size buffer_size for producers and below for consumers starting at 0
    sem_init(&sem_c, 0, 0); 

    // set the values of free indexes as 0,1,2,3...
    for(int i=0; i<BUFFER_SIZE; i++)
    {
        free_indx[i]=i;
    }

	// create given number of threads 
    for(int i=0; i < number_of_producers; i++)
    {
        if (pthread_create(&th[i], NULL, &producer, NULL) != 0) 
        {
            perror("Failed to create thread");
        }
    }

    for(int i=number_of_producers; i < number_of_consumers + number_of_producers; i++)
    {
        if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) 
        {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < number_of_consumers + number_of_producers; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    sem_destroy(&sem_p);
    sem_destroy(&sem_c);
    pthread_mutex_destroy(&mutex_FI);
	pthread_mutex_destroy(&mutex_TI);

    return 0;
}
