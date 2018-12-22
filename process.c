/*
// Main File:      synch.c
// This File:      process.c
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
#include "process.h"

#define BUFFERSIZE 1024
#define QUEUESIZE 10

// reader thread function
void *read(void *q) {
    Queue *q1 = (Queue *)q;
    char *buf = malloc(sizeof(char) * BUFFERSIZE), ch;
    int i = 0;

    while ((ch = getc(stdin)) != EOF) {
        //a waste line
        if (i >= BUFFERSIZE) {
            i = 0;
            fprintf(stderr, "%s", "Line too long, discard!\n");
            while (ch != EOF && ch != '\n') {
                ch = getc(stdin);
            }
            if (ch == EOF)
                break;
            continue;
        }
        
        if (ch != '\n')
            buf[i++] = ch;
        else {
            buf[i] = '\0';
            EnqueueString(q1, buf);
            i = 0;
        }
    }
    
    if (i >= BUFFERSIZE)
        fprintf(stderr, "%s", "Line too long, discard!\n");
    else if (i > 0){
        buf[i] = '\0';
        EnqueueString(q1, buf);
    }

    free(buf);
    pthread_exit(NULL);
}

// munch1 thread function
void *space(void *set1) {
    Queue **q = (Queue **)set1;
    Queue *q1 = q[0], *q2 = q[1];
    char *buf = malloc(sizeof(char) * BUFFERSIZE);
    int i = 0;
    
    while (q1->dequeueCount < q1->processLine) {
        buf = DequeueString(q1, buf);
        pthread_mutex_unlock(&q1->mutex);
        while (buf[i] != '\0') {
            if (buf[i] == ' ')
                buf[i] = '*';
            i++;
        }
        EnqueueString(q2, buf);
        i = 0;
    }

    free(buf);
    pthread_exit(NULL);
}

// munch2 thread function
void *upperLetter(void *set2) {
    Queue **q = (Queue **)set2;
    Queue *q2 = q[0], *q3 = q[1];
    char *buf = malloc(sizeof(char) * BUFFERSIZE);
    int i = 0;
    
    while (q2->dequeueCount < q2->processLine) {
        buf = DequeueString(q2, buf);
        pthread_mutex_unlock(&q2->mutex);
        while (buf[i] != '\0') {
            if (buf[i] >= 'a' && buf[i] <= 'z')
                buf[i] = buf[i] - 32;
            i++;
        }
        EnqueueString(q3, buf);
        i = 0;
    }
    
    free(buf);
    pthread_exit(NULL);
}

// writer thread function
void *write(void *q) {
    Queue *q3 = (Queue *)q;
    char *buf = malloc(sizeof(char) * BUFFERSIZE);
    while (q3->dequeueCount < q3->processLine) {
        buf = DequeueString(q3, buf);
        pthread_mutex_unlock(&q3->mutex);
        fprintf(stdout, "%s\n", buf);
    }
    fprintf(stdout, "%d strings processed to stdout.\n", q3->processLine);
    
    free(buf);
    pthread_exit(NULL);
}