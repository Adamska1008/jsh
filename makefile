CC=g++
INC_DIR=include
SRC_DIR=src
TAR_DIR=target
CFLAGS=-Wall -g -I./$(INC_DIR) -std=c++17
LIB=-lboost_filesystem -lboost_system -lreadline
EXE=jsh

SRC_FILES=$(patsubst $(SRC_DIR)/%.cpp, %.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES=$(SRC_FILES:.cpp=.o)
HEADERS=$(wildcard $(INC_DIR)/*.h)

OBJS=$(patsubst %.o, $(TAR_DIR)/%.o, $(OBJ_FILES))

.PHONY: all run clean

all: $(TAR_DIR)/$(EXE)

$(TAR_DIR)/$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LIB) 
	@echo finish building

$(TAR_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(TAR_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

run:
	@$(TAR_DIR)/$(EXE)

clean:
	@rm -rf ./target