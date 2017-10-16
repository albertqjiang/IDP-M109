# Automatically generated Makefile for arm
main.arm :  robot_functions.arm.o main.arm.o
	 arm-linux-gnueabi-g++ -L/usr/arm-unknown-linux-gnueabi/lib -o main.arm  robot_functions.arm.o  main.arm.o  -lrobot

robot_functions.arm.o: robot_functions.cpp robot_functions.hpp
	 arm-linux-gnueabi-g++ -ansi -Wall -g -I/usr/arm-unknown-linux-gnueabi/include -I/export/teach/1BRobot -c robot_functions.cpp -o robot_functions.arm.o
main.arm.o: main.cpp robot_functions.hpp
	 arm-linux-gnueabi-g++ -ansi -Wall -g -I/usr/arm-unknown-linux-gnueabi/include -I/export/teach/1BRobot -c main.cpp -o main.arm.o

clean:
	/usr/bin/rm *.o *.arm
