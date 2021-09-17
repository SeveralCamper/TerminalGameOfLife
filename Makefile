CFLAGS := -Wall -Werror -std=c++17
CPPFLAGS := -MMD
CXX := g++

TARGET := bin/PingPong

SOURCES := $(wildcard src/PingPong/main.cpp)
LIBSOURCES := $(wildcard src/lib/*.cpp)
LIBMSOURCES := $(wildcard src/mlib/*.cpp)

LIBOBJ := $(patsubst src/lib/%.cpp, obj/src/%.o, $(LIBSOURCES))
LIB := obj/lib/functionLib.a

MLIBOBJ := $(patsubst src/mlib/%.cpp, obj/src/%.o, $(LIBMSOURCES))
MLIB := obj/mlib/methodsLib.a

OBJ := $(patsubst src/PingPong/%.cpp, obj/src/%.o, $(SOURCES))

TEST := $(wildcard test/*.cpp)
TESTOBJ := $(patsubst test/%.cpp, obj/test/%.o, $(TEST))
TESTTARGET := bin/TestPingPong
CTEST := thirdparty/ctest.h

all:$(TARGET)

$(TARGET): $(LIB) $(MLIB) $(OBJ)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJ)  -L. $(MLIB) -L. $(LIB)  

$(LIB): $(LIBOBJ)
	ar rcs $@ $^

$(MLIB): $(MLIBOBJ)
	ar rcs $@ $^

obj/src/%.o: src/lib/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@  -I src/lib -I src/mlib

obj/src/%.o: src/mlib/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $ -I src/lib -I src/mlib

obj/src/%.o: src/PingPong/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@  -Isrc/lib -I src/mlib  

test: $(TESTTARGET)
	./$(TESTTARGET)

$(TESTTARGET): $(TESTOBJ) $(CTEST) $(LIB)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(TESTOBJ) -o $@ -L. $(MLIB) -L. $(LIB)  -I src/lib -I src/mlib -I thirdparty

obj/test/%.o: test/%.cpp $(CTEST)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ -L. $(MLIB) -L. $(LIB)  -Isrc/lib -I src/mlib -I thirdparty

run: $(TARGET)
	./bin/PingPong


clean:
	find . -name "*.o" -exec rm '{}' \;
	find . -name "*.d" -exec rm '{}' \;
	find . -name "*.a" -exec rm '{}' \;
	find ./bin -type f -name "PingPong" -exec rm -f '{}' \;
	find ./bin -type f -name "TestPingPong" -exec rm -f '{}' \;

format:
	cd src; find . -name "*.cpp" -exec clang-format -i {} \;
	cd src; find . -name "*.h" -exec clang-format -i {} \;

.PHONY: clean test run all format 
