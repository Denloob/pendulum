SRC_DIR = src
BIN_DIR = bin
DEP_DIR = .deps

LIBS = sdl2

CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu2x $(shell pkg-config --cflags $(LIBS)) -I$(SRC_DIR)
LDFLAGS = $(shell pkg-config --libs $(LIBS)) -lm
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

TARGET = pendulum
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRCS))

.PHONY: clean all run

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $(OBJS)) $(dir $(DEPS))
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BIN_DIR) $(DEP_DIR)

run: $(BIN_DIR)/$(TARGET)
	@./$(BIN_DIR)/$(TARGET) $(ARGS)
