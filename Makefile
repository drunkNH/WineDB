#
#
CC=g++
#
CFLAGS = -c -Wall -I/usr/include/mysql 
LFLAGS = -L/usr/lib/mysql -lmysqlclient



all: winedb

winedb: winedb.o dbconnect.o wineOperations.o Wine.o print_me_first.o
	$(CC) winedb.o dbconnect.o wineOperations.o Wine.o print_me_first.o -o winedb $(LFLAGS)

dbconnect.o: dbconnect.cpp
	$(CC) $(CFLAGS) dbconnect.cpp

winedb.o: winedb.cpp wineOperations.h Wine.h print_me_first.h
	$(CC) $(CFLAGS) winedb.cpp
	
wineOperations.o: wineOperations.cpp wineOperations.h Wine.h
	$(CC) $(CFLAGS) wineOperations.cpp
	
Wine.o: Wine.cpp Wine.h
	$(CC) $(CFLAGS) Wine.cpp
	
print_me_first.o: print_me_first.cpp print_me_first.h
	$(CC) $(CFLAGS) print_me_first.cpp
clean:
	rm *.o winedb

run:
	./winedb
