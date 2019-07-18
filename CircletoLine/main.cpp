#include <iostream>
#include <memory>
#include "graphics.h"
#include <window.h>
#include <cmath>

using namespace std;
using namespace mssm;

//cout cross product
//cout angle between vectors
//cout left or right

class Segment{
public:
    Vec2d p1;
    Vec2d p2;
    bool mid = false;
    unsigned char c1;
    unsigned char c2;
    unsigned char c3;
public:
    void draw(Graphics& g);
    double slope();
};

void Segment::draw(Graphics& g){
    if(mid){
        g.line(p1, p2, GREEN);
    }
    else{
        g.line(p1, p2, {c1, c2, c3});
    }
}

double Segment::slope(){
    return(p2.y-p1.y) / (p2.x-p1.x);
}

class Circle{
public:
    Vec2d center;
    double radius;
    unsigned char c1;
    unsigned char c2;
    unsigned char c3;
public:
    void draw(Graphics& g);
};

void Circle::draw(Graphics& g){
    g.ellipse(center.x - 0.5*radius, center.y - 0.5*radius, radius, radius, {c1, c2, c3});
}

double distance(Vec2d a, Vec2d b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double dotProduct(Vec2d vec1, Vec2d vec2){
    return(vec1.x*vec2.x) + (vec1.y*vec2.y);
}

int crossProduct(Vec2d vec1, Vec2d vec2){
    return vec1.x*vec2.y - vec1.y*vec2.x;
}

double angleBetween(Vec2d vec1, Vec2d vec2){
    int cp = crossProduct(vec1, vec2);
    double sinAngle = cp / (vec1.magnitude() * vec2.magnitude());
    return asin(sinAngle)*(180/3.1415);
}

string leftOrRight(double cp){
    if(cp >= 0){
        return "Right";
    }
    else{
        return "Left";
    }
}

void graphicsMain(Graphics& g){

    Segment s;
    Circle c;
    bool circle = false;

    Segment mid;
    mid.mid = true;

    double d;

    int f = 0;

    s.c1 = g.randomInt(0, 255);
    s.c2 = g.randomInt(0, 255);
    s.c3 = g.randomInt(0, 255);
    c.c1 = s.c1;
    c.c2 = s.c2;
    c.c3 = s.c3;

    while (g.draw()) {
        g.clear();

        Vec2d p1 = s.p1;
        Vec2d p2 = s.p2;

        Vec2d v1 = (c.center - p2);
        Vec2d v2 = (p2 - p1);

        double dp = dotProduct(v1, v2);

        double projection = dp / v2.magnitude();

        Vec2d p = {v2.x*(1/v2.magnitude()), v2.y*(1/v2.magnitude())};

        p = {p.x*projection, p.y*projection};

        mid.p2 = p2 + p;
        mid.p1 = c.center;

        s.draw(g);
        c.draw(g);
        mid.draw(g);

        d = distance(mid.p1, mid.p2);
        string dist = to_string(d);

        g.text(550, 50, 25, "Distance: ", WHITE);
        g.text(660, 50, 25, dist, WHITE);

        g.text(50, g.height()-25, 15, "Press A for circle", WHITE);

        g.text(50, g.height()-50, 15, "Press F to pay respects", WHITE);
        g.text(50, g.height()-75, 15, "Respects paid: ", WHITE);
        string fs = to_string(f);
        g.text(160, g.height()-75, 15, fs, WHITE);

        int cp = crossProduct(v1, v2);
        string CP = to_string(cp);
        g.text(50, g.height()-100, 15, "Cross Product: ", WHITE);
        g.text(160, g.height()-100, 15, CP, WHITE);

        double a = angleBetween(v1, v2);
        string A = to_string(a);
        g.text(50, g.height()-125, 15, "Angle: ", WHITE);
        g.text(110, g.height()-125, 15, A, WHITE);

        g.text(160, g.height()-150, 15, leftOrRight(cp), WHITE);
        g.text(50, g.height()-150, 15, "Left or Right?", WHITE);



        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                if(circle){
                    c.center = Vec2d(e.x, e.y);
                    mid.p1 = c.center;
                    c.radius = 0;
                    break;
                }
                else{
                    s.p1 = Vec2d(e.x, e.y);
                    s.p2 = s.p1;
                    break;
                }
            case EvtType::MouseRelease:
                if(circle){
                    c.radius = distance(c.center, Vec2d(e.x, e.y));
                    break;
                }
                else{
                    s.p2 = Vec2d(e.x, e.y);
                    break;
                }
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                if(circle){
                    c.radius = distance(c.center, Vec2d(e.x, e.y));
                    break;
                }
                else{
                    s.p2 = Vec2d(e.x, e.y);
                    break;
                }
            case EvtType::KeyPress:
                if(e.arg == 'A'){
                    circle = true;
                }
                if(e.arg == 'F'){
                    s.c1 = g.randomInt(0, 255);
                    s.c2 = g.randomInt(0, 255);
                    s.c3 = g.randomInt(0, 255);
                    c.c1 = s.c1;
                    c.c2 = s.c2;
                    c.c3 = s.c3;
                    f++;
                }
                break;
            case EvtType::KeyRelease:
                if(e.arg == 'A'){
                    circle = false;
                }
                break;
            default:
                break;
            }
        }
    }
}

int main()
{
    Graphics g("Drawing", 800, 600, graphicsMain);
}
