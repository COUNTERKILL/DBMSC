CC=g++
CFLAGS=-std=c++11 -pthread
LDFLAGS=
SRC_DIR=./src
SOURCES=./src/main.cpp ./src/CCoordinator.cpp ./src/CWorker.cpp ./src/CLine.cpp ./src/CSwitch.cpp ./src/CDBMSC.cpp ./src/CDCHTree.cpp ./src/CNode.cpp ./src/Config.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN_DIR=./bin
EXECUTABLE=main.o

all:
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN_DIR)/$(EXECUTABLE)

clean:
	rm -rf $(BIN_DIR)/*.o
