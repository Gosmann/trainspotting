all : 
	gcc src/main.c src/railway.c -o main
	gcc src/server.c -o bin/server
	gcc src/client.c -o bin/client



