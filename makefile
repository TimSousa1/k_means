CFLAGS = -O3 -Wall -Wextra -pedantic
#CFLAGS = -g -O0 -D DEBUG -Wall -Wextra -pedantic

SRC = main.c
INC = k_means.h
LDLIBS = -lraylib
OUT = km

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $@ $(CFLAGS) $(LDLIBS)

.PHONY: clean all
clean:
	rm -rf $(OUT)
