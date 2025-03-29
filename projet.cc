// projet.cc, Mohamed Yassine Toujani et Adam Belghith, V1
#include "jeu.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(EXIT_FAILURE);
    Jeu jeu;
    jeu.lecture(argv[1]);
    return 0;
}