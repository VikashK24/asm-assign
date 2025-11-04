# Makefile

# target program

# default rule
a.out : inlineAsmExc.o pureAsmExc.o arrAsmExc.o 
	   gcc inlineAsmExc.o pureAsmExc.o arrAsmExc.o

# compile source files into object files
inlineAsmExc.o: inlineAsmExc.c inlineAsmExc.h
	gcc -c inlineAsmExc.c

pureAsmExc.o: pureAsmExc.c inlineAsmExc.h
	   gcc -c pureAsmExc.c

arrAsmExc.o: arrAsmExc.c inlineAsmExc.h
	   gcc -c arrAsmExc.c

# clean up build files
clean:
	rm -f *.o a.out
