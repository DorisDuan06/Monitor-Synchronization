/*
// Main File:      synch.c
// This File:      synch.c
//
// Author:         Yanjia Duan
// Email:          duan35@wisc.edu
// CS Login:       yanjia
//
// Author:         Karina Nihalani
// Email:          nihalani@wisc.edu
// CS Login:       karina
//
*/

#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Queue.h"
#include "process.h"

#define BUFFERSIZE 1024
#define QUEUESIZE 10

int main(){
    Queue *q1, *q2, *q3;
    pthread_t reader, munch1, munch2, writer;
    
    q1 = CreateStringQueue(QUEUESIZE, 1);
    q2 = CreateStringQueue(QUEUESIZE, 2);
    q3 = CreateStringQueue(QUEUESIZE, 3);
    Queue *set1[2] = {q1, q2}, *set2[2] = {q2, q3}; // set1 groups q1 and q2 which munch1 will use, set2 groups q2 and q3 which munch2 will use
    
    pthread_create(&reader, NULL, read, (void *)q1);
    pthread_create(&munch1, NULL, space, (void *)set1);
    pthread_create(&munch2, NULL, upperLetter, (void *)set2);
    pthread_create(&writer, NULL, write, (void *)q3);
    
    pthread_join(reader, NULL);
    pthread_join(munch1, NULL);
    pthread_join(munch2, NULL);
    pthread_join(writer, NULL);
    
    PrintQueueStats(q1);
    PrintQueueStats(q2);
    PrintQueueStats(q3);
    
    
    free(q1);
    free(q2);
    free(q3);
    pthread_exit(NULL);
}