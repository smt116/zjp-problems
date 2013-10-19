# Maciej Małecki
# smt116@gmail.com

CC = mpicc
# Flagi dla kompilatora
FLAGS = -Wall -ggdb
# Nazwa programu wyjsciowego
OUTPUT = app
# Nazwa plikow obiektowych
SEQ_OBJS = main_sequential.o lib.o sequential.o smt_lib.a
PAR_OBJS = main_parallel.o lib.o smt_lib.a
# Nazwa plikow naglowkowych
LIBS = lib.h ${ls headers/*.h}
SEQ_LIBS = sequential.h

# Domyslna regola
default: copy_lib compile_sequential compile_parallel clean

seq: copy_lib compile_sequential clean

par: copy_lib compile_parallel clean

copy_lib:
	cp ../c-libs/smt_lib.a .

# Kompilacja
compile_sequential: $(SEQ_OBJS) $(LIBS) $(SEQ_LIBS)
	$(CC) $(FLAGS) $(SEQ_OBJS) -o seq_$(OUTPUT) -lrt

compile_parallel: $(PAR_OBJS) $(LIBS)
	$(CC) $(FLAGS) $(PAR_OBJS) -o par_$(OUTPUT) -lrt

# Regula (pattern)
%.o: %.c $(LIBS) $(SEQ_LIBS) $(PAR_LIBS)
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *~ *.o .*.swp *.a

veryclean: clean
	rm -f *.in *.out seq_$(OUTPUT) par_$(OUTPUT)
