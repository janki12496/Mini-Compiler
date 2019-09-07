# Mini-Compiler
This is a compiler based on client server architecture designed using fork, exec, dup2 and socket programming concepts.

S.c is server program and C.c is client program. Run both programs on different servers and server should be ran first.

Steps to run:
1. Get IP address of server by command: hostname -I and save it eg. 136.127.45.98
2. gcc S.c
3. ./a.out port-number e.g. a./.out 8890
4. On different server, gcc C.c
5. ./a.out 136.127.45.98 8890
6. All set up- Enter commands on client side, it will be executed by server and output will be returned to client

See Output video for live demo.
