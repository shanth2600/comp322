EXECUTABLES=matrix_gen matrix_add
all: matrix_gen matrix_add

matrix_gen: matrix_gen
	gcc matrix_add.c -lm -lrt -o matrix_add

matrix_add: matrix_add
	gcc matrix_add.c -lrt -o matrix_add

clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
