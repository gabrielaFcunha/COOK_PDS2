# O compilador que vamos usar
CXX = g++

# Flags de compilação (-std=c++11 e os diretórios de include)
CXXFLAGS = -std=c++11 -I. -IInclude

# Nome do executável final que será gerado
TARGET = cook_app

# Lista de todos os arquivos fonte necessários na pasta Src
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

# Regra principal (executada ao rodar apenas 'make')
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regra para limpar os arquivos compilados (executada ao rodar 'make clean')
clean:
	rm -f $(TARGET)