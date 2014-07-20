CC = gcc
CPPFLAGS = -g
LDFLAGS =

FILES = 	main.o		\
		exo1.o		\
		exo2.o		\
		exo3.o		\
		exo4.o		\
		exo5.o		\


INC =		$(FILES:.o=.h)	\
		chaine.h	\
		reseau.h	\

all: main

clean:
	find . -name "*.o" -exec rm '{}' ';'
	rm -f exec

main: $(FILES)
	$(CC) $(CPPFLAGS) -o ./exec $^ $(LDFLAGS)

%.o:%.c $(INC)
	$(CC) $(CPPFLAGS) -I ./ -c $< -o $@ $(LDFLAGS)

.PHONY: all clean track
