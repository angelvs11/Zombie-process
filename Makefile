CC = gcc
CFLAGS = -Wall -g

all: zombie_creator zombie_detector zombie_reaper process_daemon libzombie.a test_lib

zombie_creator: src/zombie_creator.c
	$(CC) $(CFLAGS) -o $@ $^

zombie_detector: src/zombie_detector.c
	$(CC) $(CFLAGS) -o $@ $^

zombie_reaper: src/zombie_reaper.c
	$(CC) $(CFLAGS) -o $@ $^

process_daemon: src/process_daemon.c
	$(CC) $(CFLAGS) -o $@ $^

zombie.o: src/zombie.c
	$(CC) $(CFLAGS) -c -o $@ $^

libzombie.a: zombie.o
	ar rcs $@ $^

test_lib: src/test_lib.c libzombie.a
	$(CC) $(CFLAGS) -o $@ $^ -L. -lzombie

clean:
	rm -f *.o *.a zombie_creator zombie_detector zombie_reaper process_daemon test_lib

