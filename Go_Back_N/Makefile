all: receiver sender
.PHONY: all

receiver: receiver.o
	gcc -o receiver.out receiver.o

sender: sender.o
	gcc -o sender.out sender.o

receiver.o: receiver.c
	gcc -c receiver.c

sender.o: sender.c
	gcc -c sender.c

clean: 
	rm receiver.o sender.o receiver.out sender.out
