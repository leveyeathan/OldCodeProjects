#include <iostream>
#include "graphics.h"
#include <sstream>

using namespace std;
using namespace mssm;

int calculateScore(int score, double vx, double vy){
    int c = 1;
    int d = 1;
    if(vx < 0){
        vx = -vx;
    }
    if(vy < 0){
        vy = -vy;
    }
    if(vy > 10){
        c = 2;
    }
    if(vx > 25){
        d = 2;
    }
    score += (c + d);
    return score;
}

void graphicsMain(Graphics& g)
{
    double x = g.width()/2;
    double y = g.height()/2;
    double vx = 10;
    double vy = 1;
    double a = (g.width()/2 + g.width()/7);
    double b = (g.width()/2 - g.width()/7);
    int lives = 5;
    int score = 0;

    while (g.draw() && lives > 0)
    {
        g.clear();
        stringstream Score;
        Score << "Score: " << score;

        stringstream Lives;
        Lives << "Lives: " << lives;

        if(lives > 2){
            g.text(100, 50, 20, Lives.str(), GREEN);
        }
        else{
            g.text(100, 50, 20, Lives.str(), RED);
        }
        g.text(g.width() - 200, 50, 20, Score.str(), PURPLE);

        g.ellipse(x, y, 20, 20, BLUE, BLUE);
        g.line(a, 100, b, 100);

        if(x < 0){
            vx = -vx + 1;
        }
        if(x > g.width()){
            vx = -vx - 1;
        }
        if(y > g.height()){
            vy = -vy - 0.1;
        }
        if(y < 0){
            x = g.width()/2;
            y = g.height()/2;
            lives -= 1;
            vx = 10;
            vy = 1;
            if(lives == 0){
                g.clear();
            }

        }
        if(y < 75 && y > 74 && x > a && x < b){
            vy = -vy - 0.1;
        }
        if(y > 75 && y < 76 && x > a && x < b){
            vy = -vy - 0.1;
        }

        score = calculateScore(score, vx, vy);
        x += vx;
        y += vy;

        g.isKeyPressed('A');
        g.isKeyPressed('D');
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                if(g.isKeyPressed('D')){
                    a += 40;
                    b += 40;
                }
                if(g.isKeyPressed('A')){
                    a -= 40;
                    b -= 40;
                }
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
    }
    g.text(g.width()/2 - 150, g.height()/2, 50, "GAME OVER", WHITE);
}



int main()
{
    Graphics g("Graphics", 1200, 800, graphicsMain);
}
