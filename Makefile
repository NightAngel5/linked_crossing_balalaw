# Definitions de macros
OUT = projet
CXX     = g++
CXXFLAGS = -g -std=c++17
LINKING = `pkg-config --cflags gtkmm-4.0`
LDLIBS = `pkg-config --libs gtkmm-4.0`
CXXFILES = projet.cc jeu.cc chaine.cc mobile.cc message.cc tools.cc gui.cc graphic.cc
OFILES = projet.o jeu.o chaine.o mobile.o message.o tools.o gui.o graphic.o

# Definition de la premiere regle
all: $(OUT)
# Definitions de cibles particulieres
clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(OUT)
	
graphic.o: graphic.cc graphic_gui.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

gui.o: gui.cc graphic_gui.h graphic.h gui.h jeu.h tools.h constantes.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

projet.o: projet.cc gui.h jeu.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile
$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)


#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc gui.h jeu.h tools.h graphic.h mobile.h message.h \
 constantes.h chaine.h
jeu.o: jeu.cc jeu.h tools.h graphic.h mobile.h message.h constantes.h \
 chaine.h
chaine.o: chaine.cc chaine.h tools.h graphic.h message.h constantes.h
mobile.o: mobile.cc mobile.h tools.h graphic.h message.h constantes.h
message.o: message.cc message.h
tools.o: tools.cc tools.h graphic.h
gui.o: gui.cc graphic_gui.h graphic.h gui.h jeu.h tools.h mobile.h \
 message.h constantes.h chaine.h
graphic.o: graphic.cc graphic_gui.h graphic.h
