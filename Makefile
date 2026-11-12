CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Iinclude -g
SRC     = src/lista.c src/pila.c src/cola.c src/arbol.c

.PHONY: all test demo memcheck clean

all: demo test

demo: $(SRC) src/demo.c
	$(CC) $(CFLAGS) $^ -o demo

test: $(SRC) tests/test_main.c
	$(CC) $(CFLAGS) $^ -o run_tests
	./run_tests

# Requiere valgrind instalado
memcheck: test
	valgrind --leak-check=full --error-exitcode=1 ./run_tests

clean:
	rm -f demo run_tests
