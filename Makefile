# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc jeu.cc chaine.cc mobile.cc message.cc tools.cc
OFILES = projet.o jeu.o chaine.o mobile.o message.o tools.o

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o prog

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
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE

