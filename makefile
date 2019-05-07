# Project: Cheaters
# Makefile created by Aditya Gupta

final: cheaters.o hash.o 
	g++ -o plagiarismCatcher cheaters.o hash.o

hash.o: hash.h 
	g++ -c hash.cpp

cheaters.o: cheaters.cpp hash.h
	g++ -c cheaters.cpp
