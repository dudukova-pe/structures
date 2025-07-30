all:                                                                                                                                                                                                                                                 
	gcc -c arrays/arrays.c -o arrays/arrays.o
	ar r arrays/libarrays.a arrays/arrays.o
	gcc -c dialog/communication.c -o dialog/communication.o -L /home/students/d/dudukova.pe/lab3/arrays/ -l:libarrays.a
	ar r dialog/libcommunication.a dialog/communication.o -L/home/students/d/dudukova.pe/files/entering/ -l:libentering.a
	gcc main.c -o check -L ./entering/ -l:libentering.a -L ./arrays/ -l:libarrays.a -L ./dialog/ -l:libcommunication.a