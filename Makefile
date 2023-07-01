TARGET := Dictionary

SRC := src
BUILD := build

SRCS := $(shell find $(SRC) -type f -name '*.cpp')
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))

all: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	g++ $(OBJS) -o $@ -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	g++ -w -Iinclude -c -o $@ $<

.PHONY: clean
clean:
	rm -rf build