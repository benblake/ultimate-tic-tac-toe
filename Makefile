# A sample Makefile for building both Google Mock and Google Test and
# using them in user tests.  This file is self-contained, so you don't
# need to use the Makefile in Google Test's source tree.  Please tweak
# it to suit your environment and project.  You may want to move it to
# your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GMOCK_HEADERS and GTEST_HEADERS, which you can use
# in your own targets but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file, or if you want to use
# a copy of Google Test at a different location.
GTEST_DIR = ../googletest/googletest

# Points to the root of Google Mock, relative to where this file is.
# Remember to tweak this if you move this file.
GMOCK_DIR = ../googletest/googlemock

# Where to find user code.
SRC_DIR = src
TEST_DIR = test
MOCK_DIR = $(TEST_DIR)/mocks
OUTPUT_DIR = out

# Flags passed to the preprocessor.
# Set Google Test and Google Mock's header directories as system
# directories, such that the compiler doesn't generate warnings in
# these headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include
CPPFLAGS += -I./$(SRC_DIR)
CPPFLAGS += -I./$(MOCK_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
# TESTS = gmock_test
TESTS = MCTSTest

SRC_HEADERS = $(SRC_DIR)/MCTS.h \
			  $(SRC_DIR)/MCTSNode.h

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All Google Mock headers. Note that all Google Test headers are
# included here too, as they are #included by Google Mock headers.
# Usually you shouldn't change this definition.	
GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)

# House-keeping build targets.

all : make_out_dir $(TESTS)

run : all
	$(OUTPUT_DIR)/$(TESTS)

clean :
	rm -f $(TESTS) gmock.a gmock_main.a *.o
	rm -rf $(OUTPUT_DIR)

# Builds gmock.a and gmock_main.a.  These libraries contain both
# Google Mock and Google Test.  A test should link with either gmock.a
# or gmock_main.a, depending on whether it defines its own main()
# function.  It's fine if your test only uses features from Google
# Test (and not Google Mock).

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
GMOCK_SRCS_ = $(GMOCK_DIR)/src/*.cc $(GMOCK_HEADERS)

# For simplicity and to avoid depending on implementation details of
# Google Mock and Google Test, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Mock and
# Google Test compile fast and for ordinary users their source rarely
# changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GTEST_DIR)/src/gtest-all.cc

gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock-all.cc

gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) \
            -c $(GMOCK_DIR)/src/gmock_main.cc

gmock.a : gmock-all.o gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gmock_main.a : gmock-all.o gtest-all.o gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.

# gmock_test.o : $(USER_DIR)/gmock_test.cc $(GMOCK_HEADERS)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/gmock_test.cc

# gmock_test : gmock_test.o gmock_main.a
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

MCTSTest.o : $(TEST_DIR)/MCTSTest.cpp $(GMOCK_HEADERS) $(SRC_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/MCTSTest.cpp

MCTSTest : MCTSTest.o gmock_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $(OUTPUT_DIR)/$@

make_out_dir :
	@mkdir -p $(OUTPUT_DIR)
