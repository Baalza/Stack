CXXFLAGS = 

main.exe: main.o negative_size.o stack_overflow.o stack_underflow.o
	g++ main.o negative_size.o stack_overflow.o stack_underflow.o -o main.exe -std=c++0x

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++0x

negative_size.o: negative_size.cpp
	g++ -c negative_size.cpp -o negative_size.o
stack_overflow.o: stack_overflow.cpp
	g++ -c stack_overflow.cpp -o stack_overflow.o

stack_underflow.o: stack_underflow.cpp
	g++ -c stack_underflow.cpp -o stack_underflow.o
	
.PHONY:
clean:
	rm *.exe *.o