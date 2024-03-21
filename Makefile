CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I/home/jammy/shared-folder/pacs-Examples/Examples/include -I/home/jammy/shared-folder/pacs-examples/Examples/include/muparser

EXEC     = main
LDFLAGS ?= -L/home/jammy/shared-folder/pacs-Examples/Examples/lib -Wl,-rpath=/home/jammy/shared-folder/pacs-examples/Examples/lib/libmuparser.so.2
LIBS  ?= -lmuparser

all: $(EXEC)

%.o: %.cpp GradientMethod.hpp Point.hpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC): main.o GradientMethod.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $^ -o $@

clean:
	$(RM) *.o

distclean: clean
	$(RM) *~