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
PROGNAME_PROGRAM = main
HFILES = $(SRC_DIR)/

# Executables objects path
PROGNAME_PROGRAM_OBJ= $(OBJ_DIR)/$(PROGNAME_PROGRAM).o
# Executables path
PROGNAME_PROGRAM_EXE = $(EXE_DIR)/$(PROGNAME_PROGRAM).x

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

$(PROGNAME_PROGRAM_EXE): $(PROGNAME_PROGRAM_OBJ) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(PROGNAME_PROGRAM_EXE) Makefile target_dir
	$(PROGNAME_PROGRAM_EXE)

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
