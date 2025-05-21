// graphic.cc, Mohamed Yassine Toujani 100% et Adam Belghith, V2
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "graphic_gui.h"
#include "graphic.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

// local prototypes
static void set_color(Color color);
// graphic_gui.h
void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr)
{
    ptcr = &cr;
}

void Graphic::draw_circle(double x, double y, double r, double width,
                          Color C, Remplissage R, Color C_Interieur)
{
    (*ptcr)->set_line_width(width);
    set_color(C_Interieur);
    (*ptcr)->arc(x, y, r, 0.0, 2 * M_PI);
    if (R == PLEIN)
    {
        set_color(C_Interieur);
        (*ptcr)->fill_preserve();
    }
    set_color(C);
    (*ptcr)->stroke();
}

void Graphic::draw_line(double x1, double y1, double x2, double y2,
                        double width, Color C)
{
    (*ptcr)->set_line_width(width);
    (*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}

// local function
static void set_color(Color color)
{
    double r(0.), g(0.), b(0.);
    switch (color)
    {
    case WHITE:
        r = g = b = 1;
        break;
    case GREY:
        r = g = b = 0.5;
        break;
    case BLACK:
        r = g = b = 0.;
        break;
    case RED:
        r = 1;
        break;
    case GREEN:
        g = 0.65;
        break;
    case BLUE:
        r = g = 0.65;
        b = 1;
        break;
    case ORANGE:
        r = 1;
        g = 0.65;
        break;
    case PURPLE:
        r = b = 0.65;
        break;
    case CYAN:
        g = b = 1;
        break;
    }
    (*ptcr)->set_source_rgb(r, g, b);
}
