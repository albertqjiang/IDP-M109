# Automatically generated Makefile
line_following_test :  robot_functions.o mobility_control.o line_following_test.o line_follower.o detection.o arm_control.o
	 g++ -L/export/teach/1BRobot -o line_following_test  robot_functions.o  mobility_control.o  line_following_test.o  line_follower.o  detection.o  arm_control.o  -lrobot

robot_functions.o: robot_functions.cpp robot_functions.hpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c robot_functions.cpp
mobility_control.o: mobility_control.cpp robot_functions.hpp mobility_control.hpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c mobility_control.cpp
line_following_test.o: line_following_test.cpp robot_functions.hpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c line_following_test.cpp
line_follower.o: line_follower.cpp line_follower.hpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c line_follower.cpp
detection.o: detection.cpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c detection.cpp
arm_control.o: arm_control.cpp arm_control.hpp robot_functions.hpp
	 g++ -ansi -Wall -g -I/export/teach/1BRobot -c arm_control.cpp

clean:
	/usr/bin/rm -rf *.o
