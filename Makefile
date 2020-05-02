all: example example_mnist

example: example.c brain.c
	gcc -g -o example example.c brain.c -lm

example_mnist: example_mnist.c brain.c
	gcc -g -o example_mnist example_mnist.c brain.c -lm

clean:
	rm -rf *.o
	rm -rf brain example example_mnist