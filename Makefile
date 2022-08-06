CXX := g++
CFLAGS := -g
LDLIBS := -lncurses -lpanel
INC := ./ECS/
TARGET := main

SRCS := $(wildcard *.cpp $(INC)*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(LDLIBS) $^ -o $@ 
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(TARGET) *.o $(INC)*.o
cleanO:
	rm -rf main.o $(INC)*.o
	
.PHONY: all clean cleanO
