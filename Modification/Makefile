# Macros

MAIN = main/
MAIN_FILE = $(MAIN)main.cpp
SRC = src/
SRC_FILES = $(SRC)*.cpp
OUT = bin/
OUT_FILE = $(OUT)hash-table


# Reglas explícitas

default:
	g++ $(MAIN_FILE) $(SRC_FILES) -o $(OUT_FILE)

app:
	$(OUT_FILE)

run: default app
