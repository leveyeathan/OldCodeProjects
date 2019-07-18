#include <iostream>
#include "graphics.h"
#include <sstream>
#include <vector>

using namespace std;
using namespace mssm;

class Bullet{
public:
    Vec2d center;
    Vec2d velocity;
public:
    void draw(Graphics& g);
    void physics();
};

void Bullet::draw(Graphics& g){
    g.ellipse(center.x, center.y, 5, 5, RED, RED);
}

void Bullet::physics(){
    center = center + velocity;
}

class Asteroid{
public:
    Vec2d center;
    Vec2d velocity;
    Vec2d offset;
    Vec2d offset1;
    Vec2d offset2;
    Vec2d offset3;
    Vec2d offset4;
public:
    void draw(Graphics& g);
    void update(Graphics& g);
    void randomize(Graphics& g);
private:
    void constrain(Graphics& g);
    void physics();
};

void Asteroid::update(Graphics& g){
    physics();
    constrain(g);
}

void Asteroid::physics(){
    center = center + velocity;
}

void Asteroid::randomize(Graphics& g){
    offset = {g.randomDouble(5, 15), 0};
    offset1 = {g.randomDouble(5, 15), 0};
    offset2 = {g.randomDouble(5, 15), 0};
    offset3 = {g.randomDouble(5, 15), 0};
    offset4 = {g.randomDouble(5, 15), 0};

    offset.rotate(g.randomDouble(0, 1));
    offset1.rotate(g.randomDouble(1, 2));
    offset2.rotate(g.randomDouble(2, 3));
    offset3.rotate(g.randomDouble(3, 4));
    offset4.rotate(g.randomDouble(4, 5));

    velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
    center = {(g.randomDouble(0, g.width())), (g.randomDouble(0, g.height()))};
}

void Asteroid::draw(Graphics &g){

    Vec2d point = center + offset;
    Vec2d point1 = center + offset1;
    Vec2d point2 = center + offset2;
    Vec2d point3 = center + offset3;
    Vec2d point4 = center + offset4;

    g.line(point, point1);
    g.line(point1, point2);
    g.line(point2, point3);
    g.line(point3, point4);
    g.line(point4, point);
}

void Asteroid::constrain(Graphics &g){
    if(center.y > g.height()){
        center.y = 0;
    }
    if(center.x > g.width()){
        center.x = 0;
    }
    if(center.x < 0){
        center.x = g.width();
    }
    if(center.y < 0){
        center.y = g.height();
    }
}

class Ship{
public:
    Vec2d position;
    Vec2d velocity;
    Vec2d acceleration;
    double angle;
    double angularVelocity;
public:
    Vec2d draw(Graphics& g);
    void update(Graphics& g);
private:
    void physics();
    void constrain(Graphics& g);
};

void Ship::physics(){
    angle = angle + angularVelocity;
    velocity = velocity + acceleration;
    position = position + velocity;
}

void Ship::constrain(Graphics& g){
    if(position.y > g.height()){
        position.y = 0;
    }
    if(position.x > g.width()){
        position.x = 0;
    }
    if(position.x < 0){
        position.x = g.width();
    }
    if(position.y < 0){
        position.y = g.height();
    }
}

void Ship::update(Graphics& g){
    physics();
    constrain(g);
}

Vec2d Ship::draw(Graphics& g){

    Vec2d offset{25, 0};
    Vec2d offset1{-10, 10};
    Vec2d offset2{-10, -10};

    offset.rotate(angle);
    offset1.rotate(angle);
    offset2.rotate(angle);

    Vec2d endPoint = position + offset;
    Vec2d endPoint1 = position + offset1;
    Vec2d endPoint2 = position + offset2;

    g.line(endPoint2, endPoint);
    g.line(endPoint, endPoint1);
    g.line(endPoint1, position);
    g.line(endPoint2, position);

    return endPoint;
}
//bool difficulty(Graphics& g){

//    vector<string> modes {"WEENIE", "EASY", "MEDIUM", "HARD", "INSANITY"};

//    double y = g.height() - 150;
//    double x = (g.width()/2)-100;

//    g.text((g.width()/2)-100, g.height() - 50, 50, "CHOOSE YOUR GAMEMODE", WHITE);
//    g.text((g.width()/2)-100, g.height() - 75, 10, "GAME WILL START UPON CLICK", WHITE);

//    for(int i = 0; i < modes.size(); i++){
//        g.text(x, y - (50*i), 20, modes[i], WHITE);

//    }

//    for (const Event& e : g.events())
//    {
//        switch (e.evtType)
//        {
//        case EvtType::MousePress:
//            for(int i = 0; i < modes.size(); i++){
//                if(e.x)
//            }
//            break;
//        case EvtType::MouseRelease:
//            break;
//        case EvtType::MouseWheel:
//            break;
//        case EvtType::MouseMove:
//            break;
//        case EvtType::KeyPress:
//            break;
//        case EvtType::KeyRelease:
//            break;
//        default:
//            break;
//        }
//    }



void graphicsMain(Graphics& g)
{
  //  difficulty(g);
//    if(weenie){
//        k = 5;
//    }
//    if(easy){
//        k = 10;
//    }
//    if(medium){
//        k = 10;
//    }
//    if(hard){
//        k = 20;
//    }
//    if(insanity){
//        k = 100;
//    }
    int lives = 5;
    bool bullet = false;
    double contra = 0.8;

    vector<Asteroid> asteroids;
    vector<Bullet> bullets;

    Ship player;
    player.acceleration = {0,0};
    player.velocity = {0,0};
    player.angle = 0;
    player.angularVelocity = 0;
    player.position = {g.width()/2.0, 300.0};

    int k = 15;
    for(int i = 0; i < k; i++){
        Asteroid a;
        a.randomize(g);
        asteroids.push_back(a);
    }

    while (g.draw())
    {
        g.clear();

        if(bullet){
            Bullet b;
            Vec2d endPoint = player.draw(g);
            b.center = {endPoint.x, endPoint.y};
            b.velocity = {8, 8};
            b.velocity.rotate(player.angle - contra);
            bullets.push_back(b);
            bullet = false;
        }

        for(int i = 0; i < bullets.size(); i++){
            bullets[i].draw(g);
            bullets[i].physics();
        }

        if(lives < 1 || asteroids.size() == 0){
            break;
        }

        stringstream Asteroids;
        Asteroids << "Asteroids: " << asteroids.size();

        stringstream Lives;
        Lives << "Lives: " << lives;

        if(asteroids.size() > k/2){
            g.text((g.width()/2)-100, 50, 20, Asteroids.str(), RED);
        }
        else{
            g.text((g.width()/2)-100, 50, 20, Asteroids.str(), GREEN);
        }

        if(lives > 2){
            g.text(100, 50, 20, Lives.str(), GREEN);
        }
        else{
            g.text(100, 50, 20, Lives.str(), RED);
        }

        for(int i = 0; i < asteroids.size(); i++){
            asteroids[i].draw(g);
            asteroids[i].update(g);
        }

        player.draw(g);
        player.update(g);

        if(g.isKeyPressed('W')){
            player.acceleration = {0.1, 0};
            player.acceleration.rotate(player.angle);
        }
        else {
            player.acceleration = {0, 0};
        }

        if(g.isKeyPressed('A')){
            player.angle += 0.2;
        }

        if(g.isKeyPressed('D')){
            player.angle -= 0.2;
        }

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
                if(g.isKeyPressed('S')){
                    bullet = true;
                    break;
                }
                else{
                    bullet = false;
                }
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }

        for(int i = asteroids.size() - 1; i >= 0; --i){
            if((asteroids[i].center - player.position).magnitude() < 20){
                lives = lives - 1;
                asteroids.erase(asteroids.begin() +i);
                Asteroid a;
                a.randomize(g);
                asteroids.push_back(a);
                break;
            }
        }

        for(int k = asteroids.size() - 1; k >= 0; --k){
            for(int i = bullets.size() - 1; i >= 0; --i){
                if((bullets[i].center - asteroids[k].center).magnitude() < 20){
                    asteroids.erase(asteroids.begin() + k);
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
        }

    }
    if(asteroids.size() == 0){
        g.clear();
        g.text(g.height()/2, g.width()/2, 100, "YOU WIN", GREEN);

    }
    else{
        g.clear();
        g.text(g.height()/2, g.width()/2, 100, "GAME OVER", RED);
    }

}

int main()
{
    Graphics g("Graphics", 1200, 800, graphicsMain);
}
