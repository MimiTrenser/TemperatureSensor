# Compiler and Flags
CC      = wr-cc
CFLAGS  = -rtp -static
TARGET  = run.vxe
SRC     = main.c

OBJS    = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
	