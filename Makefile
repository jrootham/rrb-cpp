rbbDriver: rbb.o gc.o rbb.h gc.h
	g++ rbbDriver.cpp -o rbbDriver

rbb.o: rbb.h gc.h

gc.o:	gc.h

