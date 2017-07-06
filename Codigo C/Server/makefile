candidato.o:
	gcc -c candidato.c -o candidato.o
#-g	

servidor.o:
	gcc -c servidor.c -o servidor.o
#-g

main.o:
	gcc -c main.c -o main.o
#-g

all: servidor.exe

servidor.exe: candidato.o servidor.o main.o
	gcc candidato.o servidor.o main.o -o servidor -Wall -lm -march=native -O3

#-g

clean:
	rm -rf *.o

run:
	./servidor
