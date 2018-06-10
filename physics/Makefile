# Generic C++ Makefile

#1 Output File:
OUT_NAME := physics
OUT_DIR := .

#2 Source root:
SRC_DIR := src

#3 Warnings:
WARNS := -Wall -Wextra -Winline -pedantic

#4 gcc Flags:
CFLAGS := --std=c11

#5 g++ Flags:
CXXFLAGS := --std=c++17 -fconcepts

#6 gcc & g++ Flags:
BOTH := -O2 -march=native -flto

#7 Libs:
LIBS :=

#8 Paths for the libs:
LIBS_PATH :=

#9 Extra include paths:
INCLUDE :=

#**********************************************************

CFLAGS += $(BOTH) $(WARNS)
CXXFLAGS += $(BOTH) $(WARNS)

INCLUDE += -I $(CURDIR)/$(SRC_DIR)

SRC_CPP := $(shell find $(SRC_DIR) | grep -E "\.cpp")
SRC_HPP := $(shell find $(SRC_DIR) | grep -E "\.hpp|\.h|\.tpp")
SRC_OBJ := $(patsubst %.cpp,%.o,$(SRC_CPP))

OUT := $(OUT_DIR)/$(OUT_NAME)

OBJECTS := $(SRC_OBJ)


.PHONY: all clean mkdir check

all: $(OBJECTS) $(SRC_HPP)
	g++ $(CXXFLAGS) $(INCLUDE) $(LIBS_PATH) -o $(OUT) $(OBJECTS) $(LIBS)

mkdir:
	@mkdir -p bin

clean: check
	@rm -i $(OUT) $(OBJECTS)

check:
	@echo "Out: " $(OUT)
	@echo "Sources: "
	@echo $(SRC_CPP)
	@echo "Objects: "
	@echo $(OBJECTS)



%.o: %.cpp $(SRC_HPP)
	g++ $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

%.o: %.c $(SRC_HPP)
	gcc $(CFLAGS) -c $< -o $@ $(INCLUDE)
