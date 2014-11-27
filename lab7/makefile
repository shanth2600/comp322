OBJECTS = matrix_gen.o matrix_add.o

all: matrix_add matrix_gen

%.o: %.c
	gcc -c $< -o $@

matrix_add: $(OBJECTS)
	gcc matrix_add.o -o $@ -lm -lrt

matrix_gen: $(OBJECTS)
	gcc matrix_gen.o -o $@  -lm -lrt

clean:
	-rm -f $(OBJECTS)
