main: main.c 
	$(CC) -Wall -o $@ $^
	#gcc -g -Wall -o main main.c

clean:
	  $(RM) main
