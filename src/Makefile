CXX ?= g++
RM = rm -f
ifeq ($(CXX),clang++)
CXXFLAGS = -Wall -std=c++11
else
CXXFLAGS = -Wall -std=c++11
endif

PREFIX = ?= /usr/local
MANDIR = $(PREFIX)/share/man
INCDIRS = -I/usr/include
LIBDIRS = -L/usr/lib

LIBS = -lsfml-graphics -lsfml-window -lsfml-system
#if debugging is needed
ifeq ($(DEBUG),yes)
	CXXFLAGS += -g
endif

SRCS = \
GetTemperatureSFML.o

# Rule to create .o files from .cpp files
.cpp.o:
	$(RM) $@
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $*.cpp

# Targets...

all:: GetTemperatureSFML

GetTemperatureSFML: $(FILES)
	$(RM) $@
	$(CXX) -o $@ $(CXXFLAGS) $(INCDIRS) $(FILES) $(LIBS)
	strip GetTemperatureSFML
	
# Clean
clean:
	$(RM) GetTemperatureSFML
