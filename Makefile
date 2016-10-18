all: try

try:	menu2.o checksudoku.o    
	gcc menu2.c `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0` -o try


checksudoku.o:	checksudoku.c
	gcc -c checksudoku.c


menu2.o:	menu2.c
	gcc menu2.c `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0`

	    





clean:
	rm -fr *o try
	
	

	
	 
	
 
