TARGET = client serverM serverS serverL serverH

all: $(TARGET)
	
$(TARGET): %: %.cpp
	g++ -std=c++11 -o $@ $<

clean: 
	rm -f $(TARGET)