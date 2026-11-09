# =====================================================================
# Makefile do COOK++
#
#   make                    -> compila o programa (gera ./receitas)
#   make run                -> compila e executa o programa
#   make tests-all          -> compila e roda TODOS os testes
#   make test-ingredientes  -> compila e roda so tests/test_ingredientes.cpp
#                              (o que vem depois de "test-" e o nome do
#                               arquivo de teste, sem "test_" e sem ".cpp")
#   make clean              -> apaga tudo que foi gerado
#
# =====================================================================
CXX := g++

# -MMD -MP: o compilador gera um arquivo .d com a lista de headers de cada
#           .cpp, para o make saber o que recompilar quando um .hpp mudar.
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -Ithird_party -MMD -MP
SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build


APP_SRC = $(filter-out src/main.cpp,$(SRC))

APP := receitas
TEST := $(BUILD_DIR)/testes

# --- Arquivos do programa ---------------------------------------------
# A main fica separada: os testes tem a main deles (tests/main.cpp) e
# reaproveitam todo o resto do programa.
APP_SRC  := $(filter-out $(SRC_DIR)/main.cpp,$(wildcard $(SRC_DIR)/*.cpp))
APP_OBJ  := $(APP_SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_OBJ := $(BUILD_DIR)/main.o

# --- Arquivos dos testes ----------------------------------------------
TEST_SRC      := $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_OBJ      := $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)
TEST_MAIN_OBJ := $(BUILD_DIR)/tests/main.o
 
DEPS := $(APP_OBJ:.o=.d) $(MAIN_OBJ:.o=.d) $(TEST_OBJ:.o=.d) $(TEST_MAIN_OBJ:.o=.d)
 
.PHONY: all run tests-all clean
 
# Primeiro alvo = o que acontece ao digitar apenas "make"
all: $(APP)
 
run: $(APP)
	./$(APP)
 
# --- Programa ---------------------------------------------------------
$(APP): $(APP_OBJ) $(MAIN_OBJ)
	$(CXX) $^ -o $@
 
# --- Testes -----------------------------------------------------------
# Todos os testes juntos, em um unico executavel
tests-all: $(TESTS)
	./$(TESTS)
 
$(TESTS): $(APP_OBJ) $(TEST_MAIN_OBJ) $(TEST_OBJ)
	$(CXX) $^ -o $@
 
# Um teste so: make test-receita, make test-texto, ...
# O "%" e o nome entre "test-" e o fim (ex.: test-receita -> test_receita.cpp)
test-%: $(APP_OBJ) $(TEST_MAIN_OBJ) $(BUILD_DIR)/tests/test_%.o
	$(CXX) $^ -o $(BUILD_DIR)/$@
	./$(BUILD_DIR)/$@
 
# --- Compilacao de cada .cpp para .o ----------------------------------
$(APP_OBJ) $(MAIN_OBJ): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
$(TEST_OBJ) $(TEST_MAIN_OBJ): $(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
clean:
	rm -rf $(BUILD_DIR) $(APP)
 
# Inclui as dependencias de headers geradas pelo compilador (se existirem)
-include $(DEPS)