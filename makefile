#Opcions que passem al compilador
flags = -c -Wall -Wextra -D_GLIBCXX_DEBUG



#Lincat final 
main.exe: main.o Organisme.o ConjuntOrg.o Arbre.o
	g++ -o main.exe main.o Organisme.o ConjuntOrg.o Arbre.o

#Programa principal
main.o: main.cpp Arbre.hpp Organisme.hpp ConjuntOrg.hpp
	g++ $(flags) main.cpp -I. 

#Classes necesàries
Organisme.o: Organisme.hpp Organisme.cpp Arbre.hpp
	g++ $(flags) Organisme.cpp -I.

ConjuntOrg.o: ConjuntOrg.hpp ConjuntOrg.cpp Organisme.hpp
	g++ $(flags) ConjuntOrg.cpp -I.

clean:
	rm *.o
	rm *.exe
