#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> // For sleep
#include <stdlib.h> // For rand()

#define THINKING 2 
#define HUNGRY 0 
#define EATING 1 
#define LEFT (philo_num + 4) % 5 
#define RIGHT (philo_num + 1) % 5 

#define MAX_HUNGRY_TIME 5 // Max time a philosopher can be hungry before thinking again

int mood[5]; 
int phil[5] = { 0, 1, 2, 3, 4 }; 
sem_t sem; 
sem_t semaphores[5];

void takeChopStick(int philo_num) 
{ 
    sem_wait(&sem); // Enter critical section

    mood[philo_num] = HUNGRY; 
    printf("Philosopher %d is hungry\n", philo_num + 1);
    canStartEating(philo_num); 

    sem_post(&sem); // Leave critical section
  
    sem_wait(&semaphores[philo_num]); // Wait until allowed to eat
}

void canStartEating(int philo_num) 
{ 
    // Check if the philosopher can start eating
    if (mood[philo_num] == HUNGRY && mood[LEFT] != EATING && mood[RIGHT] != EATING) 
    { 
        mood[philo_num] = EATING; 
        printf("Philosopher %d takes chopsticks %d and %d\n", philo_num + 1, LEFT + 1, philo_num + 1);
        sleep(1); // Simulate eating time
        printf("Philosopher %d is eating\n", philo_num + 1); 
        sleep(1); // Simulate eating time
        sem_post(&semaphores[philo_num]); // Allow this philosopher to finish
    } 
} 

void putChopStick(int philo_num) 
{ 
    sem_wait(&sem); // Enter critical section

    mood[philo_num] = THINKING; 
    printf("Philosopher %d puts chopsticks %d and %d down\n", philo_num + 1, LEFT + 1, philo_num + 1);
    sleep(1); // Simulate putting down chopsticks time
    printf("Philosopher %d finished eating\n", philo_num + 1);
    
    canStartEating(LEFT); // Try to start eating the left neighbor
    canStartEating(RIGHT); // Try to start eating the right neighbor

    sem_post(&sem); // Leave critical section
}

void* philosopher(void* number) 
{
    int* delta = number;
    
    while (1) { // Philosophers will keep trying to eat
        // Random delay to simulate different thinking times
        sleep(rand() % 3 + 1); // Thinking for 1-3 seconds
        
        takeChopStick(*delta); // Try to take chopsticks
        
        // Limit the hungry time
        sleep(MAX_HUNGRY_TIME); // Allow some time for hunger
        putChopStick(*delta); // Put down chopsticks
    }
} 

int main() 
{ 
    pthread_t threads[5]; 
    sem_init(&sem, 0, 1); // Initialize semaphore for mutual exclusion

    for (int i = 0; i < 5; i++) 
    {
        sem_init(&semaphores[i], 0, 0); // Initialize semaphores for each philosopher
    }

    for (int j = 0; j < 5; j++) 
    { 
        pthread_create(&threads[j], NULL, philosopher, &phil[j]); 
        sleep(1); // Add a small delay between starting philosophers
    }
  
    for (int v = 0; v < 5; v++)
    {
        pthread_join(threads[v], NULL); // Wait for all philosophers to finish
    }

    // Cleanup
    sem_destroy(&sem);
    for (int i = 0; i < 5; i++) {
        sem_destroy(&semaphores[i]);
    }
  
    return 0; 
}


