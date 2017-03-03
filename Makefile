# Authors : Anmol Sood , Kartikay Garg , Rahul Rathore
# Makefile for Assignment 2 : COP290 2014-2015

all:
	(cd src/Server; make all;)
	(cd src/Client; qmake; make;)

DEBUG:
	(cd src/Server; make DEBUG port=$(port);)
	(cd src/Client; make;)

server:
	(cd src/Server; make server port=$(port); )

client:
	(cd src/Client; qmake;make; cd bin; ./dropbox2 $(server) $(port);)


.PHONY: clean 

clean:
	@rm -f out *.o  *.aux *.blg  *.bbl *.log *.ps *.dvi *.toc *.idx *.ind *.ilg *.br *.db;	
	(cd src/Server; make clean;)
	(cd src/Client; make clean;)
	
