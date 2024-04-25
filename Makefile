SCRIPT_DIR := .
BUILD_DIR := $(SCRIPT_DIR)/build
CHAKRA_ET_DIR := $(SCRIPT_DIR)/et_def

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall

# Source files
SRCS =  $(CHAKRA_ET_DIR)/et_def.pb.cc $(SCRIPT_DIR)/et_feeder/et_feeder.cpp $(SCRIPT_DIR)/et_feeder/et_feeder_node.cpp $(SCRIPT_DIR)/third_party/utils/protoio.cc $(SCRIPT_DIR)/et_feeder/tests.cpp

# Object files
OBJS = $(CHAKRA_ET_DIR)/et_def.pb.o $(SCRIPT_DIR)/et_feeder/et_feeder.o $(SCRIPT_DIR)/et_feeder/et_feeder_node.o $(SCRIPT_DIR)/third_party/utils/protoio.o $(SCRIPT_DIR)/et_feeder/tests.o

# Executable name
TARGET := $(BUILD_DIR)/test

# Libraries
LIBS := -lgtest -lgtest_main -lprotobuf -lpthread 

# Include directories
INCLUDES := -I.

# Default target
all: compile_proto build tests

# Compile et_def.proto
compile_proto:
	@if [ ! -f "$(CHAKRA_ET_DIR)/et_def.pb.h" ] || [ ! -f "$(CHAKRA_ET_DIR)/et_def.pb.cc" ]; then \
		protoc et_def.proto \
			--proto_path=$(CHAKRA_ET_DIR) \
			--cpp_out=$(CHAKRA_ET_DIR); \
	fi

# Build target
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET) $(CHAKRA_ET_DIR)/et_def.pb.cc $(CHAKRA_ET_DIR)/et_def.pb.h

# Tests target
tests: $(TARGET)
	./$(TARGET)

.PHONY: all compile_proto build clean tests