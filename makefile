all: editor.c
	gcc editor.c -Wall -ansi -o node `pkg-config --cflags --libs gtk+-2.0`
clean:
	rm *.o
run: all
	./node
