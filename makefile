all: main

main:Downloader.o Parser.o
	g++ -o main main.cpp Downloader.o Parser.o  -lcurl -Wall

Downloader.o: Downloader.cpp Downloader.h
	g++ -c Downloader.cpp

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp

main.o: main.cpp
	g++ -c main.cpp 
