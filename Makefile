SRC_DIR = src
OUTPUT_DIR = out

CPPFLAGS += -I./$(SRC_DIR)

CXXFLAGS += -g -Wall -Wextra -std=c++11
CXX = g++

SRC_HEADERS = $(SRC_DIR)/MCTS.h \
			  $(SRC_DIR)/MCTSNode.h \
			  $(SRC_DIR)/GameState.h \
			  $(SRC_DIR)/GameSimulator.h

all : make_out_dir main

run : all
	$(OUTPUT_DIR)/main

clean :
	rm -f *.o
	rm -rf $(OUTPUT_DIR)

main.o : $(SRC_DIR)/main.cpp $(SRC_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp

main : main.o 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(OUTPUT_DIR)/$@

make_out_dir :
	@mkdir -p $(OUTPUT_DIR)
