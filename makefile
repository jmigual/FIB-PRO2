#Opcions que passem al compilador
flags = -c -Wall -Wextra -D_GLIBCXX_DEBUG



#Lincat final 
all: main.o Organisme.o ConjuntOrg.o Ranking.o
	g++ -o main.exe main.o Organisme.o ConjuntOrg.o Ranking.o

#Programa principal
main.o: main.cpp Arbre.hpp Organisme.hpp ConjuntOrg.hpp Ranking.hpp
	g++ $(flags) main.cpp

#Classes necesàries
Organisme.o: Organisme.hpp Organisme.cpp Arbre.hpp
	g++ $(flags) Organisme.cpp

ConjuntOrg.o: ConjuntOrg.hpp ConjuntOrg.cpp Organisme.hpp
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
