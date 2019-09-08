# Mini-Compiler
This is a compiler based on client server architecture designed using fork, exec, dup2 and socket programming concepts.

Technology Used: C, Nano editor, Linux GNU bash compiler

S.c is server program and C.c is client program. Run both programs on different servers and server should be ran first.

Steps to run:
1. Get IP address of server by command: hostname -I and save it eg. 136.127.45.98
2. gcc S.c
3. ./a.out port-number e.g. a./.out 8890
4. On different server, gcc C.c
5. ./a.out 136.127.45.98 8890
6. All set up- Enter commands on client side, it will be executed by server and output will be returned to client

See Output video for live demo.

The server task can be summarized as follows :
• The server start running before any client, and wait for connections.
• When the server gets a client, forks and, the child process take care of the client in a separate function, called serviceClient, while the parent process goes back to wait for
the next client. In particular, the server is capable to service multiple clients at the same time.

Note: for this part, you can also use threads instead of processes.

• Then, the server’s child process
1. uses "dup2()" to swap screen for socket
2. gets in an infinite loop then :
– reads a shell command-line (ended by new line) from client,
– if the client has closed its sockets then, the server’s child quits.
– otherwise, it assembles the command and its arguments before excuting it using
exec() system call,

The client process connects to the server, then
• gets into an infinite loops
1. reads a command-line from keyboard,
2. if command is "quit", closes socket and quits
3. otherwise, send command-line to server,
4. Then, reads command output from socket and displays them on the screen
