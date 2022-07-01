all: main

main:Downloader.o Parser.o CategoriesDownloader.o main.o JsonParser.o
	g++ -o main main.cpp Downloader.o Parser.o CategoriesDownloader.o JsonParser.o  -lcurl -Wall

Downloader.o: Downloader.cpp Downloader.h
	g++ -c Downloader.cpp

Parser.o: Parser.cpp Parser.h
	g++ -c Parser.cpp

CategoriesDownloader.o: CategoriesDownloader.cpp CategoriesDownloader.h
	g++ -c CategoriesDownloader.cpp

JsonParser.o: JsonParser.cpp JsonParser.h
	g++ -c JsonParser.cpp

main.o: main.cpp
	g++ -c main.cpp 
