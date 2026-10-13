CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Itests

SRC = $(wildcard src/*.cpp)
TEST_SRC = $(wildcard tests/*.cpp)

TARGET = testes

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)