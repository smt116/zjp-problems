# Maciej Małecki
# smt116@gmail.com

# Flagi dla kompilatora
FLAGS = -Wall -ggdb
# Nazwa programu wyjsciowego
OUTPUT = app
# Nazwa plikow obiektowych
OBJS = main.o lib.o
# Nazwa plikow naglowkowych
LIBS = lib.h

# Domyslna regola
default: compile clean

# Kompilacja
compile: $(OBJS) $(LIBS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUTPUT)

# Regula (pattern)
%.o: %.c $(LIBS)
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *~ *.o .*.swp

veryclean: clean
	rm -f *.in *.out $(OUTPUT)
