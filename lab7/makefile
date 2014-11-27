all: matrix_add matrix_gen

matrix_gen: matrix_gen.c
	gcc  -o matrix_gen -c -lm -lrt  matrix_gen.c

matrix_add: matrix_add.c
	gcc  -o  matrix_add -c -lrt  matrix_add.c
