IDIR = ../include
CXX = g++
CXXFLAGS = -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS = -lm

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hellomake.o hellofunc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
        $(CXX) -c -o $@ $< $(CXXFLAGS)

hellomake: $(OBJ)
        $(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
        rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
