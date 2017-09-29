#########################################################
# Factorization Algorithms by Rodrigo Arigita, Feb 2003 #
#########################################################

OPTIONS = -ggdb -Wno-deprecated

all : Trial Fermat Shanks Pollard_rho Pollard_p-1 QS Lenstra

Trial : Trial_division.cc Integer.o
	g++ $(OPTIONS) -o Trial Trial_division.cc Integer.o -lgmp

Fermat : Fermat.cc Integer.o
	g++ $(OPTIONS) -o Fermat Fermat.cc Integer.o -lgmp

Shanks : Shanks.cc Integer.o
	g++ $(OPTIONS) -o Shanks Shanks.cc Integer.o -lgmp

Pollard_rho: Pollard_rho.cc Integer.o
	g++ $(OPTIONS) -o Pollard_rho Pollard_rho.cc Integer.o -lgmp

Pollard_p-1: Pollard_p-1.cc Integer.o
	g++ $(OPTIONS) -o Pollard_p-1 Pollard_p-1.cc Integer.o -lgmp

QS: QS.cc bitset.cc Integer.o 
	g++ $(OPTIONS) -o QS QS.cc bitset.cc Integer.o -lgmp

Lenstra: Lenstra.cc Integer.o
	g++ $(OPTIONS) -o Lenstra Lenstra.cc Integer.o -lgmp

Integer.o : Integer.cc Integer.h
	g++ $(OPTIONS) -c Integer.cc

clean :
	rm *.o Trial Fermat Shanks Pollard_rho Pollard_p-1 QS Lenstra

