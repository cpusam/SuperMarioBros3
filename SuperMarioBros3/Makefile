# C++ Compiler
CC=g++

# Compile settings
CFLAGS= -std=c++11 -Wall -g -I./../chora_engine-2-master -I./../chora_engine-2-master/include -I./../chora_engine-2-master/game  -I./include -L./../chora_engine-2-master -D_DEBUG_
LFLAGS= -lm -lchora -lSDL2 -lSDL2_image -g

# Search for Headers and Source files
MAIN				= 	$(shell find . -name "main.cpp")
SOURCES 			= 	$(shell find src -name "*.cpp")
SOURCES_LIB_JSON	=	$(shell find lib -name "*.cpp")
HEADERS 			=	$(shell find . -name "*.hpp")
HEADERS_LIB_JSON	=	$(shell find . -name "*.h")
OBJECTS				=	$(SOURCES:src/%.cpp=obj/%.o)
OBJECTS_LIB_JSON	=	$(SOURCES_LIB_JSON:lib/SimpleJSON/src/%.cpp=lib/SimpleJSON/obj/%.o)

# Output
EXECUTABLE=SMB3

# Generates Everything
all: $(EXECUTABLE) $(MAIN) $(OBJECTS) $(OBJECTS_LIB_JSON)

# Generates the Executable
$(EXECUTABLE): $(MAIN) $(OBJECTS) $(OBJECTS_LIB_JSON)
		$(CC)  $(OBJECTS) $(MAIN) $(OBJECTS_LIB_JSON) $(CFLAGS) $(LFLAGS) -o $@

# Generates the project objects
obj/%.o:	src/%.cpp  $(HEADERS)
	@test -d $(@D) || mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(@:obj/%.o=src/%.cpp) -o $@

# Generates the SimpleJSON objects
lib/SimpleJSON/obj/%.o: lib/SimpleJSON/src/%.cpp $(HEADERS_LIB_JSON)
	@test -d $(@D) || mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(@:lib/SimpleJSON/obj/%.o=lib/SimpleJSON/src/%.cpp) -o $@

# Remove Everything
clean:
		rm -f $(OBJECTS) $(EXECUTABLE) lib/SimpleJSON/obj/%.o
