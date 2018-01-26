all: example-0.c
	gcc `pkg-config --cflags gtk+-3.0` -o node example-0.c `pkg-config --libs gtk+-3.0` -Wno-deprecated
clean:
	rm *.o
run: all
	./node
