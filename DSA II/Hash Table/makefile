spell.out: spellcheck.o hash.o
	g++ -o spell.out spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	g++ -c spellcheck.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o spellDebug.out spellcheck.cpp hash.cpp

clean:
	rm *.out *.o *.stackdump *~