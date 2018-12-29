# Monitor-Synchronization
Creating the synchronization mechanism based on monitors.

This project includes `synch.c`, `Queue.c` and `process.c`.

## synch.c:
1. `main()`: create queues, threads and initialize them.

## Queue.c:
1. `Queue structure`: store queue information.
2. Input file processing function `countlines()`: count the number of processed strings from the input file and create a pointer to the input file.
3. Queue initializing function `CreateStringQueue()`.
4. Queue operation function `EnqueueString()`: check conditions of the queue and put a string into a queue.
5. Queue operation function `DequeueString()`: check conditions of the queue and take a string away from a queue.
6. Queue operation function `PrintQueueStats()`: print queue statistics to stderr.

## process.c:
1. Reader thread function `read()`: read a string from the input file, check its length, and put it into the first queue.
2. Munch1 thread function `space()`: take the string away from the first queue, store it in its own buffer, change " " to "*", and put it into the second queue.
3. Munch2 thread function `upperLetter()`: take the string away from the second queue, store it in its own buffer, change lower letters to upper letters, and put it into the third queue.
4. Writer thread function `write()`: write the string from the third queue to the standard output file.
