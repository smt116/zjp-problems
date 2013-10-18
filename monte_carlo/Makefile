# Maciej Małecki
# smt116@gmail.com

CC = mpicc
# Flagi dla kompilatora
FLAGS = -Wall -ggdb
# Nazwa programu wyjsciowego
OUTPUT = app
# Nazwa plikow obiektowych
SEQ_OBJS = main_sequential.o
PAR_OBJS = main_parallel.o
OBJS = lib.o smt_lib.a
# Nazwa plikow naglowkowych
LIBS = lib.h ${ls headers/*.h}

# Domyslna regola
default: compile_seq compile_par clean

# Kompilacja
compile_seq: $(OBJS) $(SEQ_OBJS) $(LIBS)
	$(CC) $(FLAGS) $(SEQ_OBJS) $(OBJS) -o seq_$(OUTPUT) -lrt

compile_par: $(OBJS) $(PAR_OBJS) $(LIBS)
	$(CC) $(FLAGS) $(PAR_OBJS) $(OBJS) -o par_$(OUTPUT) -lrt

# Regula (pattern)
%.o: %.c $(LIBS)
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *~ *.o .*.swp

veryclean: clean
	rm -f *.in *.out seq_$(OUTPUT) par_$(OUTPUT)
