CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=vision_main.cpp
INCLUDES=-I/usr/include/opencv
LIBS=-lm -lopencv_core -lopencv_imgproc -lopencv_highgui
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=vision

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES)  $< -o $@

clean:
	@echo "===>  CLEAN"
	@rm -rf *.o
	@rm -f $(EXECUTABLE)

