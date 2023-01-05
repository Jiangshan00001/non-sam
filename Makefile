OBJS = main.o
CC = gcc

# libsdl present
#CFLAGS =  -Wall -O2 -DUSESDL `sdl-config --cflags`
#LFLAGS = `sdl-config --libs`

# no libsdl present
CFLAGS =  -Wall -O2 
LFLAGS = 

sam: $(OBJS)
	$(CC) -o non-sam $(OBJS) $(LFLAGS)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

package: 
	tar -cvzf non-sam.tar.gz README.md Makefile sing src/

clean:
	rm *.o

doc:
	echo "nothing done"