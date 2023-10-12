CC = g++ -g
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Wpedantic -g -Ofast#$(shell pkg-config --cflags)

all: Order

Order: Dictionary.o Order.o
	$(CC) $(CFLAGS) -o  $@ $^ 


DictionaryTest: Dictionary.o DictionaryTest.o
	$(CC) $(CFLAGS) -o  $@ $^ 


%.o: %.c
	$(CC) $(CFLAGS) -c -Ofast 

clean:
	rm -f *.o
	rm -f DictionaryTest
	rm -f Order

