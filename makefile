CXX = g++
CXXFLAGS = -Wall
OBJECTS = War.o Horse.o Untrained.o Warhorse.o Light.o Medium.o Heavy.o

proj4: $(OBJECTS) driver.cpp
	$(CXX) $(CXXFLAGS) -o proj4 $(OBJECTS) driver.cpp 

War.o: War.cpp War.h Horse.h Untrained.h Warhorse.h Light.h Medium.h Heavy.h
	$(CXX) $(CXXFLAGS) -c War.cpp

Horse.o: Horse.cpp Horse.h 
	$(CXX) $(CXXFLAGS) -c Horse.cpp

Untrained.o: Untrained.cpp Untrained.h Horse.h Light.h Medium.h Heavy.h
	$(CXX) $(CXXFLAGS) -c Untrained.cpp

Warhorse.o: Warhorse.cpp Warhorse.h Horse.h
	$(CXX) $(CXXFLAGS) -c Warhorse.cpp

Light.o: Light.cpp Light.h Warhorse.h
	$(CXX) $(CXXFLAGS) -c Light.cpp

Medium.o: Medium.cpp Medium.h Warhorse.h
	$(CXX) $(CXXFLAGS) -c Medium.cpp

Heavy.o: Heavy.cpp Heavy.h Warhorse.h
	$(CXX) $(CXXFLAGS) -c Heavy.cpp

clean:
	rm *.o*
	rm *~*
	rm *#*

run:
	./proj4

test:
	./proj4 proj4_data.txt

val:
	valgrind ./proj4 proj4_data.txt
