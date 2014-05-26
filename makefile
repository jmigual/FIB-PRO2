#Opcions que passem al compilador
flags = -c -Wall -D_GLIBCXX_DEBUG -m32



#Lincat final 
all: pro2.o Organisme.o ConjuntOrg.o Ranking.o
	g++ -o pro2.exe *.o -m32

#Programa principal
pro2.o: pro2.cpp Arbre.hpp Organisme.hpp ConjuntOrg.hpp Ranking.hpp
	g++ $(flags) pro2.cpp

#Classes necesàries
Organisme.o: Organisme.hpp Organisme.cpp
	g++ $(flags) Organisme.cpp

ConjuntOrg.o: ConjuntOrg.hpp ConjuntOrg.cpp
	g++ $(flags) ConjuntOrg.cpp

Ranking.o: Ranking.hpp Ranking.cpp
	g++ $(flags) Ranking.cpp

##################################
#Versió per provar coses

prova: prova.o Organisme.o ConjuntOrg.o Ranking.o
	g++ -o prova.exe prova.o Organisme.o ConjuntOrg.o Ranking.o

prova.o: prova.cpp Arbre.hpp Organisme.hpp ConjuntOrg.hpp Ranking.hpp
	g++ $(flags) prova.cpp

##################################
#Netejem tots els arxius creats
clean:
	rm *.o
	rm *.exe
