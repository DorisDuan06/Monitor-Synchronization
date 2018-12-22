/*
// Main File:      synch.c
// This File:      Queue.h
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
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct {
    int queueID;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    int processLine; // record number of lines that are processed
    int first;
    int last;
    int element;
    pthread_mutex_t mutex;
    pthread_cond_t enqueue;
    pthread_cond_t dequeue;
    char **array; // store 10 lines at most
} Queue;

int countlines();
Queue *CreateStringQueue(int size, int id);
void EnqueueString(Queue *q, char *string);
char *DequeueString(Queue *q, char *str);
void PrintQueueStats(Queue *q);

#endif