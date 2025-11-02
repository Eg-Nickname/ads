# Makefile
# Compiler
CXX = g++
LIBS =
# CXXFLAGS = -Wall -std=c++23

DIR = $(notdir $(CURDIR))
# Compilation target directory
TARGET_DIR = ./target
# Object directory in target
OBJ_DIR = $(TARGET_DIR)/obj
# Executables directory in target
EXE_DIR = $(TARGET_DIR)/exe
# Source code directory
SRC_DIR = ./src

# Names for object and exe files for programs
SINGLE_LIST_PROGRAM = main
HFILES = $(SRC_DIR)/singlelist.hpp

# Executables objects path
SINGLE_LIST_PROGRAM_OBJ= $(OBJ_DIR)/$(SINGLE_LIST_PROGRAM).o
# Executables path
SINGLE_LIST_PROGRAM_EXE = $(EXE_DIR)/$(SINGLE_LIST_PROGRAM).x

# Compilator flags
CFLAGS = -Wall -std=c++20 -pedantic 
# Linker flags
LFLAGS = 
# Compiler and linker
CO = g++
LD = $(CO)

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HFILES) target_dir
	$(CO) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c target_dir
	$(CO) $(CFLAGS) -c $< -o $@

$(SINGLE_LIST_PROGRAM_EXE): $(SINGLE_LIST_PROGRAM_OBJ) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(SINGLE_LIST_PROGRAM_EXE) Makefile target_dir
	$(SINGLE_LIST_PROGRAM_EXE)

# .PHONY: compile
# compile: $(SORTING_PROGRAM_EXE) Makefile
# # 	Do nothing

.PHONY : clean
clean :
	$(RM) $(TARGET) *.o core; rm -rf $(TARGET_DIR)

.PHONY: target_dir
target_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)
