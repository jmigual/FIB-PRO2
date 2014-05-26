#Opcions que passem al compilador
flags = -c -D_GLIBCXX_DEBUG -I$$INCLUDES_CPP



#Lincat final 
all: pro2.o Organisme.o ConjuntOrg.o Ranking.o
	g++ -o pro2.exe *.o

#Programa principal
pro2.o: pro2.cpp Organisme.hpp ConjuntOrg.hpp Ranking.hpp
	g++ $(flags) pro2.cpp

#Classes necesàries
Organisme.o: Organisme.hpp Organisme.cpp
	g++ $(flags) Organisme.cpp

ConjuntOrg.o: ConjuntOrg.hpp ConjuntOrg.cpp
	g++ $(flags) ConjuntOrg.cpp

Ranking.o: Ranking.hpp Ranking.cpp
	g++ $(flags) Ranking.cpp


##################################
#Netejem tots els arxius creats
clean:
	rm *.o
	rm *.exe
