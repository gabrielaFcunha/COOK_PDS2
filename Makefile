CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -I. -IInclude
COVERAGE_FLAGS = --coverage -g -O0

TARGET = cook_app
TEST_TARGET = build/coverage/testes

BUILD_DIR = build/app
COVERAGE_DIR = build/coverage

SRC = Src/main.cpp \
      Src/interface.cpp \
      Src/catalogo.cpp \
      Src/despensa.cpp \
      Src/receita.cpp \
      Src/ingredientes.cpp \
      Src/filtro.cpp \
      Src/texto.cpp \
      Src/unidade.cpp \
      Src/categoria.cpp

APP_SRC = $(filter-out Src/main.cpp, $(SRC))

TEST_SRC = Tests/main.cpp $(wildcard Tests/test_*.cpp)

APP_OBJ = $(patsubst Src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

COVERAGE_SRC = $(APP_SRC) $(TEST_SRC)
COVERAGE_OBJ = $(patsubst %.cpp,$(COVERAGE_DIR)/%.o,$(COVERAGE_SRC))

DEPS = $(APP_OBJ:.o=.d) $(COVERAGE_OBJ:.o=.d)

.PHONY: all clean test cobertura

all: $(TARGET)

$(TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: Src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(COVERAGE_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -MMD -MP -c $< -o $@

$(TEST_TARGET): $(COVERAGE_OBJ)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

cobertura: $(TEST_TARGET)
	find $(COVERAGE_DIR) -name "*.gcda" -delete
	./$(TEST_TARGET)
	gcovr -r . --filter 'Src/' --object-directory $(COVERAGE_DIR) --html-details coverage.html

-include $(DEPS)

clean:
	rm -rf build $(TARGET) coverage.html