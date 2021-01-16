cc=gcc
AR=ar
FLAGS= -Wall 

all: frequency 

frequency: main.o 
		$(CC) $(FLAGS) -o frequency main.o 

main.o: main.c  
	$(CC) $(FLAGS) -c main.c 

clean:
	rm -f *.o *.a *.so *.out frequency

.PHONY: clean all