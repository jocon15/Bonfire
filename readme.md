# Bonfire

## Overview
Bonfire is a lighweight threaded logger written in C\++ and designed for C\++. Single threaded logic would require a logger to open and close the file every time the logger needed to write an entry to the file. This is a tremendous amount of overhead that could be delegated to a different thread. Bonfire is designed to do exactly that, offload most of the overhead of file operations to a different thread.

## QuickStart
To start using the logger:
1. Inlclude the header
2. Instantiate a Logger object
3. Log away!

```
#include "Logger.hpp"

int main(){
	Logger logger = Logger();

    log.info("Starting some task...");
    // perform some task
    log.info("Some task finished!")
}
```

## A Queue Between Two Threads
The Logger class has a queue to mediate between the two threads. When the main thread logs a message ex: `log.info("task complete!");`, the message is added to the queue. When you instantiated the logger object, a background listener thread was started that periodically checks the queue for any data to write. If there is data present, the listener thread write the data to the designate log file. This relieves the burden of file interactions from the main thread.

When the Logger destructor is called, the listener thread finishes writing the remaining data in the queue to the file. Then joins the main thread.

## Log Levels
The log levels follow the log levels defined in Python.

| Level  |
|--------|
|DEBUG   |
|INFO    |
|WARNING |
|ERROR   |
|CRITICAL|

## Handlers