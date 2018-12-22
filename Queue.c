/*
// Main File:      synch.c
// This File:      Queue.c
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
#include <string.h>
#include "Queue.h"

#define BUFFERSIZE 1024
#define QUEUESIZE 10

// Count number of lines in the file
int countlines() {
    int processLine = 0, i = 0;
    char ch;
    while ((ch = getc(stdin)) != EOF) {
        i++;
        if (ch == '\n') {
            if (i <= BUFFERSIZE)
                processLine++;
            i = 0;
        }
    }
    if (i > 0 && i < BUFFERSIZE)
        processLine++;
    rewind(stdin);
    return processLine;
}

// Initialize Queue structure
Queue *CreateStringQueue(int size, int id) {
    Queue *q = malloc(sizeof(Queue));
    q->queueID = id;
    q->enqueueCount = q->dequeueCount = q->enqueueBlockCount = q->dequeueBlockCount = q->first = q->last = q->element = 0;
    q->processLine = countlines();
    q->array = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++)
        q->array[i] = malloc(sizeof(char) * BUFFERSIZE);
    return q;
}

// Put a string to a Queue
void EnqueueString(Queue *q, char *string) {
    pthread_mutex_lock(&q->mutex);
    if (q->element == QUEUESIZE) {
        q->enqueueBlockCount++;
        pthread_cond_wait(&q->enqueue, &q->mutex);
    }
    strcpy(q->array[q->last], string);
    q->last = (q->last+1) % QUEUESIZE;
    q->enqueueCount++;
    q->element++;
    pthread_cond_signal(&q->dequeue);
    pthread_mutex_unlock(&q->mutex);
}

// Take a string away from a Queue
char *DequeueString(Queue *q, char *str) {
    pthread_mutex_lock(&q->mutex);
    if (q->element == 0) {
        q->dequeueBlockCount++;
        pthread_cond_wait(&q->dequeue, &q->mutex);
    }
    strcpy(str, q->array[q->first]);
    q->first = (q->first+1) % QUEUESIZE;
    q->dequeueCount++;
    q->element--;
    pthread_cond_signal(&q->enqueue);
    return str;
}

// Print the Queue's information to stderr
void PrintQueueStats(Queue *q) {
    fprintf(stderr, "\nQueue%d Statistics:\n\tenqueueCount = %d\n\tdequeueCount = %d\n\tenqueueBlockCount = %d\n\tdequeueBlockCount = %d\n", q->queueID, q->enqueueCount, q->dequeueCount, q->enqueueBlockCount, q->dequeueBlockCount);
}