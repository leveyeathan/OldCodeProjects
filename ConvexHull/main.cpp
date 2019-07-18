#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>

using namespace std;
using namespace mssm;

double dotProduct(Vec2d vec1, Vec2d vec2){
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

double angleBetween(Vec2d vec1, Vec2d vec2){
    double dp = dotProduct(vec1, vec2);
    double cosAngle = dp / (vec1.magnitude()*vec2.magnitude());
    return acos(cosAngle)*(180/3.1415);
}

vector<Vec2d> convexHull(vector<Vec2d> points)
{
    vector<Vec2d> hull;

    if(points.size() < 3){
        return hull;
    }

    unsigned int j = 0;
    for (unsigned int i = 1; i < points.size(); i++) {
        if (points[i].x < points[j].x){
            j = i;
        }
    }

    Vec2d currentPoint = points[j];
    Vec2d previousPoint = {currentPoint.y + 2, currentPoint.x};
    hull.push_back(currentPoint);

    unsigned int i = 0;

    Vec2d newPoint;

    do{
        currentPoint = hull[hull.size() - 1];
        double angle = 360;
        for(unsigned int k = 0; k < points.size(); k++){
            if(angleBetween(currentPoint-previousPoint, points[k]-currentPoint) < angle){
                newPoint = points[k];
                angle = angleBetween(currentPoint-previousPoint, points[k]-currentPoint);
            }
        }

        i++;
        previousPoint = currentPoint;
        hull.push_back(newPoint);

        if(i > points.size()){
            break;
        }
    }
    while(newPoint.x != hull[0].x || newPoint.y != hull[0].y);

    return hull;
}

vector<Vec2d> randomPoints(Graphics& g, double radius, size_t count)
{
    Vec2d center { g.width()/2.0, g.height()/2.0};

    vector<Vec2d> points;

    for (size_t i = 0; i < count; i++) {
        Vec2d candidate;

        do {
            candidate = { g.randomDouble(-radius, radius), g.randomDouble(-radius, radius) };
        }
        while (candidate.magnitude() > radius);

        points.push_back(candidate + center);
    }

    return points;
}

void graphicsMain(Graphics& g)
{
    vector<Vec2d> points = randomPoints(g, min(g.width(), g.height())*0.4, 20);

    vector<Vec2d> hull;

    bool useExtra = false;
    Vec2d extraPoint;

    while (g.draw()) {

        Vec2d p1 = {650, double(g.height())};
        Vec2d p2 = {600, double(g.height())};


        g.clear();

        g.points(points, WHITE);

        //        for(unsigned int i = 0; i < points.size(); i++){
        //            double a = angleBetween(p2-p1, points[i]-p1);
        //            g.line(p1, points[i], RED);
        //            g.text(points[i], 15, to_string(a));
        //        }
        g.polygon(hull, GREEN);

        if (useExtra) {
            g.point(extraPoint, YELLOW);
        }

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                if (e.arg == 1) {
                    useExtra = true;
                    extraPoint = Vec2d(e.x, e.y);
                    vector<Vec2d> tmpPoints = points;
                    tmpPoints.push_back(extraPoint);
                    hull = convexHull(tmpPoints);
                }
                else {
                    useExtra = false;
                    points.push_back(Vec2d(e.x, e.y));
                    hull = convexHull(points);
                }
                break;
            case EvtType::MouseRelease:
                useExtra = false;
                hull = convexHull(points);
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                if (e.arg == 1) {
                    useExtra = true;
                    extraPoint = Vec2d(e.x, e.y);
                    vector<Vec2d> tmpPoints = points;
                    tmpPoints.push_back(extraPoint);
                    hull = convexHull(tmpPoints);
                }
                else {
                    useExtra = false;
                    points.back() = (Vec2d(e.x, e.y));
                    hull = convexHull(points);
                }
                break;
            case EvtType::KeyPress:
                if (e.arg >= '0' && e.arg <= '9') {
                    size_t count = size_t(pow(2,(e.arg-'0')));
                    count += size_t(g.randomInt(0,1));
                    points = randomPoints(g, min(g.width(), g.height())*0.4, count);
                    hull.clear();
                }
                if (e.arg == ' ') {
                    if (hull.empty()) {
                        hull = convexHull(points);
                    }
                    else {
                        hull.clear();
                    }
                }
                if (e.arg == 'C') {
                    points.clear();
                    hull.clear();
                    useExtra = false;
                }
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }

    }

}

int main()
{
    // main should be empty except for the following line:
    Graphics g("Drawing", 800, 800, graphicsMain);
}
