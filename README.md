# Systems_Final_Project

Installing gtk:
If on linux:
sudo apt-get install gtk+3
If on Mac:
install brew
brew install gtk+3

To compile:
gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0`
