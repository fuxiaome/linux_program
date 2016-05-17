BIN=bibsem_lock.a
SRC=sem_lock.c
OBJ=$(SRC:.c=.0)//后缀替换
CC=gcc
AR=arr
FLAGS=#-g -D_DEBUG_

$(BIN):$(SRC)
	$(AR) -o $@ $^ $(FLAGS)
$(OBJ):$(SRC)
	$(CC) -c $(SRC) -o $(OBJ)
	
.PHONY:clean
clean:
	rm -rf $(BIN) $(output)
	
.PHONY:output
output:
	mkdir output 
	cp sem_lock.h output
	cp $(BIN) output