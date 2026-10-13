
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Itests

SRC = $(wildcard src/*.cpp)
TEST_SRC = $(wildcard tests/test_*.cpp)

APP_SRC = $(filter-out src/main.cpp,$(SRC))

APP = receitas
TEST = testes

all: app test

app: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $(APP_SRC) src/main.cpp -o $(APP)

$(TEST): $(APP_SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(APP_SRC) $(TEST_SRC) -o $(TEST)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(APP) $(TEST)