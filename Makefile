CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I. -IInclude
TARGET = cook_app

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

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

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
	rm -f $(TARGET)
