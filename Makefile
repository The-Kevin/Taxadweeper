# Variáveis
CXX = clang++
CXXFLAGS = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = bin/app
SRC = main.cpp

# Regras
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

