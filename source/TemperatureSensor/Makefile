# Compiler and Flags
CC      = wr-cc
CFLAGS  = -rtp -static -Iinclude
TARGET  = run.vxe
SRC     = main.c \
          temperatureSensor.c \
		  evaluateData.c \
		  logError.c

OBJS    = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
	