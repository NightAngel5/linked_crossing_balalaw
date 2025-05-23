// graphic.h, Mohamed Yassine Toujani et Adam Belghith, V2
#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Remplissage
{
    VIDE,
    PLEIN
};
enum Color
{
    WHITE,
    GREY,
    BLACK,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    PURPLE,
    CYAN
};
namespace Graphic
{
    void draw_circle(double x, double y, double r, double width,
                     Color C, Remplissage R, Color C_Interieur);
    void draw_line(double x1, double y1, double x2,
                   double y2, double width, Color C);
}
#endif
