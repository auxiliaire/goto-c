IDIR = .
CC = clang
CFLAGS = -Wall -std=gnu17 -I$(IDIR)

ODIR = .
LDIR = .

LIBS = -lm

_DEPS = strutils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = fib.o strutils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fib: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/fib $(ODIR)/*.o *~ core $(IDIR)/*~
