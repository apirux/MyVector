# Makefile...

# MACRO: compiler, flags/switches
CC=g++
CFLAGS=-c -ansi -pedantic -Wall -Wextra

# SPECS: file_name, source_names --> w/o extensions
FILE=myVec
SOURCE_01=MyVector
# SOURCE_02=<source_name_02>

all: $(FILE)

$(FILE):
	$(CC) -o $(FILE) main.cpp

# $(FILE): $(SOURCE_01).o $(SOURCE_02).o
	# $(CC) -o $(FILE) $(SOURCE_01).o $(SOURCE_02).o

# $(SOURCE_01).o: $(SOURCE_01).cpp
# 	$(CC) $(CFLAGS) $(SOURCE_01).cpp

# $(SOURCE_02).o: $(SOURCE_02).cpp
# 	$(CC) $(CFLAGS) $(SOURCE_02).cpp

clean:
	rm -rf *o $(FILE)
