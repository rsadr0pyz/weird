all:
	gcc -o prog *.c -lm
	./prog
	rm ./prog