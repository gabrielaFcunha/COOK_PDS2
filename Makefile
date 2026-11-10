CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -I. -IInclude
COVERAGE_FLAGS = --coverage -g -O0 -DTESTANDO

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

.PHONY: all clean test cobertura relatorio

# Compila a aplicação
all: $(TARGET)

$(TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: Src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compila os arquivos dos testes com suporte à cobertura
$(COVERAGE_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -MMD -MP -c $< -o $@

# Gera o executável de testes, sem executá-lo
$(TEST_TARGET): $(COVERAGE_OBJ)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $^ -o $@

# Apenas compila os testes
cobertura: $(TEST_TARGET)

# Executa os testes explicitamente
test: $(TEST_TARGET)
	find $(COVERAGE_DIR) -name "*.gcda" -delete
	./$(TEST_TARGET)

# Gera o relatório após a execução dos testes
relatorio:
	gcovr -r . --filter 'Src/' --object-directory $(COVERAGE_DIR) --html-details coverage.html

-include $(DEPS)

clean:
	rm -rf build $(TARGET) coverage.html