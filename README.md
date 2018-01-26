# Systems_Final_Project

Installing gtk:
Linux:
1. Open terminal and type "sudo apt-get install gtk+3"

Mac:
1. Install homebrew
2. Open terminal and type "brew install gtk+3"

To compile:
$ gcc `pkg-config --cflags gtk+-3.0` -o node example-0.c `pkg-config --libs gtk+-3.0`
OR
$ make

To run:
$ ./node
OR
$ make run
