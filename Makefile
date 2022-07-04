CXX := g++
CFLAGS := -g
LDLIBS := -lncurses -lpanel
TARGET := main

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(LDLIBS) -o $@ $^
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
cleanO:
	rm -rf $(TARGET).o
	
.PHONY: all clean cleanO
