CC = g++
CFLAGS  = -g -Wall
TARGET = bms
CLASSES = rsc.cpp interleaver.cpp decoder.cpp siso_decoder.cpp trellis.cpp encoder.cpp

all: $(TARGET)
	
$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(CLASSES) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
