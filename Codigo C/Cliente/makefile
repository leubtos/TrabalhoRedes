candidato.o:
	gcc -c candidato.c -o candidato.o
#-g	

#cliente.o:
#	gcc -c cliente.c -o cliente.o
#-g

main.o:
	gcc -c main.c -o main.o
#-g

all: cliente.exe

cliente.exe: candidato.o main.o
	gcc candidato.o main.o -o cliente -Wall -lm -march=native -O3

#-g

clean:
	rm -rf *.o

run:
	./cliente
