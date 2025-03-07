PROJECT = Gwint

TESTPROJECT = test$(PROJECT)

CXX = g++

CXXFLAGS = -I. -std=c++17 -Werror -Wall -Wpedantic -g -fPIC

TESTCXXFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

DEPS = $(wildcard inlude/Gwint/*.h)

SRC = $(wildcard src/*.cpp)
TEST_SRC = $(wildcard tests/*.cpp)

OBJDIR = src/obj
TEST_OBJDIR = tests/obj

OBJ = $(SRC:src/%.cpp=$(OBJDIR)/%.o)
TEST_OBJ = $(TEST_SRC:tests/%.cpp=$(TEST_OBJDIR)/%.o)


.PHONY: default

default: all

$(OBJDIR)/%.o: $(SRC) $(DEPS) | $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	
$(TEST_OBJDIR)/%.o: $(TEST_SRC) | $(TEST_OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(TESTPROJECT): $(TEST_OBJ)
	$(CXX) -o $@ $^ $(TESTCXXFLAGS)



$(OBJDIR):
	mkdir -p $(OBJDIR)
$(TEST_OBJDIR):
	mkdir -p $(TEST_OBJDIR)



.PHONY: test

test: $(TESTPROJECT)

all: $(PROJECT)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(TEST_OBJDIR)
	rm -f $(PROJECT)
	rm -f $(TESTPROJECT)
