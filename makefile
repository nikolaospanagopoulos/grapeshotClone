all: main

main:Downloader.o Parser.o CategoriesDownloader.o main.o JsonParser.o Database.o App.o
	g++ -std=c++17 -o main main.cpp Downloader.o Parser.o CategoriesDownloader.o JsonParser.o Database.o   -lcurl -Wall -lmysqlcppconn

Downloader.o: Downloader.cpp Downloader.h
	g++ -c Downloader.cpp -lcurl -Wall 

Parser.o: Parser.cpp Parser.h
	g++ -c -std=c++17 Parser.cpp -lcurl -Wall 

CategoriesDownloader.o: CategoriesDownloader.cpp CategoriesDownloader.h
	g++ -c CategoriesDownloader.cpp -lcurl -Wall 

JsonParser.o: JsonParser.cpp JsonParser.h
	g++ -c JsonParser.cpp -lcurl -Wall 

Database.o: Database.cpp Database.h
	g++ -c Database.cpp -lcurl -Wall



main.o: main.cpp
	g++ -c main.cpp -lcurl -Wall 
