# Systems_Final_Project
Node by Kevin Li & Peter Lee, Period 10

Description:
Node is a note-taking program that allows its users to easily take notes in programming in c and compile and run the example code without having to open terminal.

Installing gtk:
Linux:
1. Open terminal and type "sudo apt-get install gtk+3"

Mac:
1. Install homebrew
2. Open terminal and type "brew install gtk+3"

To compile:
$ gcc editor.c -Wall -ansi -o node `pkg-config --cflags --libs gtk+-2.0`
OR
$ make

To run:
$ ./node
OR
$ make run

Instructions:
1. Take regular notes in the "Node: Notes" window.
2. Type example code that will be compiled and ran in the "Node: Codes" window.
3. Save your code file as "run.c". 
4. In the output window, click File and then click Compile&Run. 
