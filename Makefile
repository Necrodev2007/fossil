# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/main.c src/tasks.c
TARGET = bin/fossil

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "  CC      $(TARGET) [OK]"

# Regla para limpiar
clean:
	@rm -rf bin/fossil
	@echo "  CLEAN   Project cleaned."

# Regla para recompilar
re: clean all
