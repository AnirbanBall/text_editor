CC = gcc

BUILD = build/
SRC = src/

SRCS = $(patsubst $(SRC)%.c,$(BUILD)%.o, $(wildcard $(SRC)*.c))
OBJS = $(SRCS:.c=.o)

all: $(BUILD)text_editor

$(BUILD)%.o: $(SRC)%.S $(BUILD)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD)text_editor:
	$(CC) $(OBJS) -o $@



