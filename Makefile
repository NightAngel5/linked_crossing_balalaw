# Definitions de macros

CXX     = g++
CXXFLAGS = -g -std=c++11
CXXFILES = projet.cc jeu.cc chaine.cc mobile.cc message.cc tools.cc
OFILES = projet.o jeu.o chaine.o mobile.o message.o tools.o

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc jeu.h tools.h mobile.h message.h constantes.h \
 chaine.h
jeu.o: jeu.cc jeu.h tools.h mobile.h message.h constantes.h chaine.h
chaine.o: chaine.cc chaine.h tools.h message.h constantes.h
mobile.o: mobile.cc mobile.h tools.h message.h constantes.h
message.o: message.cc message.h
tools.o: tools.cc tools.h
