//
//  dp_main.c
//  dining_philosophers
//

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>

#define NUM_PHILO    5
#define MAX_SLEEP_TIME     2
#define MAX_EATEN          3

int total_iterations = 0;

typedef enum {THINKING, HUNGRY, EATING} STATE;

pthread_t tid[NUM_PHILO];
STATE state[NUM_PHILO];
long thread_id[NUM_PHILO];
int haveEaten[NUM_PHILO];


sem_t ok[NUM_PHILO] ={1,1,1,1,1};




const char* toString(STATE state, int haveEaten) {
    static char buf[20];
    
    switch(state) {
    case THINKING:  return "thinking";
    case HUNGRY:    return "*Hungry*";
    case EATING:
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "EATING (%d)", haveEaten);
            return buf;
    default:        return "-------- invalid state --------";
    }
}
void showAllPhilosophers() {
    printf("-------------------------------------------------------------------------\n");
    for (long i = 0; i < NUM_PHILO; ++i) { printf("%10s  |  ", toString(state[i], haveEaten[i])); }
    printf("\n");
}
void nap(const char* msg, int time) { /* printf("%s\n", msg);  */   sleep(time); }
void thinking(int thinking_time) { nap("thinking", thinking_time); }
void eating(  int eating_time)   { nap("eating",   eating_time);   }

long onleft(long number)  { return (number + NUM_PHILO - 1) % NUM_PHILO; }
long onright(long number) { return (number + 1) % NUM_PHILO; }

void hungry_chopsticksAvail_eat(long i)
 {      // eat when I'm hungry and my neighbors aren't eating
    if (state[i] == HUNGRY && state[onleft(i)] != EATING && state[onright(i)] != EATING) 
    {
        ++haveEaten[i];
        state[i] = EATING;
        showAllPhilosophers();
        sem_post(&ok[i]);
       
    }
}
void wants_to_pickup_chopsticks(long number) 
{
    sem_wait(&ok[NUM_PHILO]);
    state[number] = HUNGRY;
    hungry_chopsticksAvail_eat(number);
                                                        // wait for signal to eat
    while (state[number] != EATING) 
    {
       sem_post(&ok[NUM_PHILO]);
      
    }
   sem_post(&ok[NUM_PHILO]);
}
void wants_to_return_chopsticks(long number)
 {
     sem_wait(&ok[NUM_PHILO]);
    
    state[number] = THINKING;
    hungry_chopsticksAvail_eat(onleft(number));     // signal HUNGRY left/right neighbors to eat
    hungry_chopsticksAvail_eat(onright(number));
    
    sem_post(&ok[NUM_PHILO]);
}
void* philosopher(void* param) {
    long number = *(long *)param;
    int sleep_time;
    int times_through_loop = 0;
    
    srandom((unsigned)time(NULL));
    while (haveEaten[number] < MAX_EATEN) {
        sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
        thinking(sleep_time);
        wants_to_pickup_chopsticks(number);

        sleep_time = (int)((random() % MAX_SLEEP_TIME) + 1);
        eating(sleep_time);
        
        wants_to_return_chopsticks(number);
        ++times_through_loop;
    }
    return NULL;
}

void init() {               // requires -std=C99 or -std=C11 compile-flag
    for (int i = 0; i < NUM_PHILO; i++) 
    {
        state[i] = THINKING;
        haveEaten[i] = 0;
        thread_id[i] = i;
       
       sem_init(&ok[i],0,1);
    

    }
    sem_init(&ok[NUM_PHILO],0,1);

}

int main(int argc, const char** argv) {
    init();
    printf("=========================================================================\n");
    printf("|                    ====== PHILOSOPHERS ======                         |\n");
    printf("=========================================================================\n");
    printf("   Phil_0   |     Phil_1   |     Phil_2   |     Phil_3   |    Phil_4    |\n");
    showAllPhilosophers();
    for (int i = 0; i < NUM_PHILO; i++) {
      pthread_create(&tid[i], 0, philosopher, (void *)&thread_id[i]);
    }
    for (int i = 0; i < NUM_PHILO; i++) {
      pthread_join(tid[i], NULL);
    }

    printf("\n\t\t...done.\n");
    return 0;
}
