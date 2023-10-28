CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.

# List of source files
SRCS = main.cpp ClassSchedule.cpp Student.cpp TimeInterval.cpp readClassesPerUcFile.cpp Uc.cpp readClassesFile.cpp Class.cpp readStudentsClassesFile.cpp Data.cpp

# List of object files
OBJS = $(SRCS:.cpp=.o)

# Name of the executable
TARGET = AED

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean