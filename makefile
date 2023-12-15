

all: hello.c

hello: hello.c 
	gcc -o hello hello.c

# main: main.o
#   gcc -o main main.c

clean: 
	rm hello