#include <pthread.h> 
#include <stdio.h>

#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t lock;

void *rutone(void *arg)
{
    int i;
    
    i = 0;
    pthread_mutex_lock(&lock); 
    while (i < 1000000)
    {
        counter++;
        i++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    printf("Main started\n");

    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, rutone, NULL);
    pthread_create(&t2, NULL, rutone, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    printf("Final counter = %d\n", counter);
    printf("Main finished\n");

    return 0;
}
