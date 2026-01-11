CC:=clang

CFLAGS_COMMON:=-Wall -Wextra -Wpedantic -std=c17
CLFAGS_RELEASE:= $(CFLAGS_COMMON) -O2 -DNDEBUG
CLFAGS_DEBUG:= $(CFLAGS_COMMON) -g -O0

SRC_DIR:=src

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

BUILD_DIR:=build

TARGET:=cmoi
SRC:=$(shell find $(SRC_DIR) -name '*.c')

OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))


BUILD ?= debug

ifeq ($(BUILD), release)
	CLFAGS:= $(CLFAGS_RELEASE)
else
	CLFAGS:= $(CLFAGS_DEBUG)
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: all clean
