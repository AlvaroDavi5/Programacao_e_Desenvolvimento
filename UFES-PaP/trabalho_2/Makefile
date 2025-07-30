# Makefile for Haskell clustering program

# Compiler and flags
GHC = ghc
GHC_FLAGS = -O2 -Wall -package containers

# Source files
SRC = Main.hs
EXEC = clustering

# Default target
all: $(EXEC)

# Compile the program
$(EXEC): $(SRC)
	$(GHC) $(GHC_FLAGS) -o $(EXEC) $(SRC)

# Install required packages (if needed)
setup:
	ghc-pkg list

# Run the program
run: $(EXEC)
	./$(EXEC)

# Clean compiled files
clean:
	rm -f $(EXEC) *.hi *.o

# Force rebuild
rebuild: clean all

.PHONY: all setup run clean rebuild
