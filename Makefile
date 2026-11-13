CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -I. -Iinclude
COVERAGE_FLAGS = --coverage -g -O0 -DTESTANDO

TARGET = cook_app
TEST_TARGET = build/coverage/testes

BUILD_DIR = build/app
COVERAGE_DIR = build/coverage
REPORT_DIR = build/relatorios

SRC = src/main.cpp \
      src/interface.cpp \
      src/catalogo.cpp \
      src/despensa.cpp \
      src/receita.cpp \
      src/ingredientes.cpp \
      src/filtro.cpp \
      src/texto.cpp \
      src/unidade.cpp \
      src/categoria.cpp

APP_SRC = $(filter-out src/main.cpp, $(SRC))

TEST_SRC = tests/main.cpp $(wildcard tests/test_*.cpp)

APP_OBJ = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

COVERAGE_SRC = $(APP_SRC) $(TEST_SRC)
COVERAGE_OBJ = $(patsubst %.cpp,$(COVERAGE_DIR)/%.o,$(COVERAGE_SRC))

DEPS = $(APP_OBJ:.o=.d) $(COVERAGE_OBJ:.o=.d)

.PHONY: all clean clean-coverage clean-relatorio test cobertura relatorio

# Compila a aplicação
all: $(TARGET)

$(TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compila os arquivos dos testes com suporte à cobertura
$(COVERAGE_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -MMD -MP -c $< -o $@

# Gera o executável de testes
$(TEST_TARGET): $(COVERAGE_OBJ)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $^ -o $@

# Compila os testes, sem executá-los
cobertura: $(TEST_TARGET)

# Executa os testes já compilados
test:
	./$(TEST_TARGET)

# Gera o relatório com os dados de cobertura existentes
relatorio:
	mkdir -p $(REPORT_DIR)
	gcovr -r . --filter 'src/' --object-directory $(COVERAGE_DIR) --html-details $(REPORT_DIR)/coverage.html

# Remove arquivos e dados da cobertura
clean-coverage:
	rm -rf $(COVERAGE_DIR)

# Remove somente os relatórios do gcovr
clean-relatorio:
	rm -rf $(REPORT_DIR)

# Remove todos os arquivos de compilação e cobertura
clean:
	rm -rf build $(TARGET)

-include $(DEPS)