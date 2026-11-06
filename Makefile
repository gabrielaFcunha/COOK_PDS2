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

clean:
	rm -f $(TARGET)