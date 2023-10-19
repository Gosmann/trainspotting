all : 
	gcc src/train.c src/railway.c src/server.c -o train
	gcc src/railway.c src/main.c src/server.c -o rbc
	
	




