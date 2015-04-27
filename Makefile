CPP = g++
CFLAGS = -Wall -O3
MKDIR = mkdir
RM = rm -frv

.PHONY: all clean

all: build/keylogger.exe

build/keylogger.exe: build/main.o build/utils.o
	$(CPP) $(CFLAGS) $^ -o $@

build/main.o: src/main.cpp src/main.h build
	$(CPP) $(CFLAGS) -c $< -o $@

build/utils.o: src/utils.cpp src/utils.h build
	$(CPP) $(CFLAGS) -c $< -o $@

build:
	$(MKDIR) "$@"

clean:
	$(RM) build/main.o build/utils.o
