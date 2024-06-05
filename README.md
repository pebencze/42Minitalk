# Minitalk

The `minitalk` project involves creating a small data exchange program using UNIX signals. The goal is to implement a client-server communication system where the client sends a string to the server using signals, and the server displays the received string.

## Mandatory Part

### Overview

You must create two programs:

1. **Server**
   - The server must be started first.
   - It prints its PID upon launch.
   - It receives a string from the client and displays it.
   - The server can handle multiple client connections sequentially without restarting.
   - Communication is done using only `SIGUSR1` and `SIGUSR2` signals.

2. **Client**
   - The client takes two arguments:
     1. Server PID
     2. String to send
   - The client sends the string to the server using signals.

### Usage

1. Compile the programs using the provided Makefile:
   ```
   make
   ```
### Run the server:

    ./server

Run the client with the server PID and the string to send:

    ./client <server_pid> "Your message here"

### Example:

    $ ./server
    Server PID: 12345

    $ ./client 12345 "Hello, server!"

### Allowed Functions

    write, ft_printf (or equivalent coded by you), signal, 
    sigemptyset, sigaddset, sigaction, kill, getpid, malloc, 
    free, pause, sleep, usleep, exit

Bonus Part

The bonus part includes:

    Message Acknowledgment: The server acknowledges each received message by sending a signal back to the client.
    Unicode Support: The server can handle Unicode characters in the received string.

