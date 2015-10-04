#include "utils.hpp"

bool isInt(std::string s) {
    for(int i = 0; i < int(s.size()); ++i)
        if (!(s[i]>='0' && s[i]<='9'))
            return false;
    return true;
}

int myStoi(std::string s) {
    int x=0;
    for (int i = 0; i < int(s.size()); ++i)
        x = 10*x+(s[i]-'0');
    return x;
}

float difference(float a, float b){
    float c = a-b;
    if(c > 0) return c;
    else return c*-1;
}

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}

float getModule(const sf::Vector2f &orig, const sf::Vector2f &des) {
    return std::sqrt(std::pow(std::abs(des.x-orig.x), 2) + std::pow(std::abs(des.y-orig.y), 2));
}

bool isCollisioning(sf::Vector2f point1, float radius1, sf::Vector2f point2, float radius2) {
    return (getModule(point1,point2) < radius1+radius2);
}

/*
 * bool RectangleColision(Rectangle r1, Rectangle r2) {
    if (r1.lowerLeft.x < r2.lowerLeft.x + r2.width &&
       r1.lowerLeft.x + r1.width > r2.lowerLeft.x &&
       r1.lowerLeft.y < r2.lowerLeft.y + r2.height &&
       r1.lowerLeft.y + r1.height > r2.lowerLeft.y)
        return true ;
    else
        return false ;
}
bool colisionCircleRectangle(Circle c, Rectangle r) {
    float closestX = c.center.x;
    float closestY = c.center.y;

    if (c.center.x < r.lowerLeft.x) {
        closestX = r.lowerLeft.x;
    }

    else if (c.center.x > r.lowerLeft.x + r.width) {
        closestX = r.lowerLeft.x + r.width;
    }

    if (c.center.y < r.lowerLeft.y) {
        closestY = r.lowerLeft.y;
    }

    else if (c.center.y > r.lowerLeft.y + r.height) {
        closestY = r.lowerLeft.y + r.height;
    }

    return c.center.distSquared(closestX, closestY) < c.radius * c.radius;
}
*/
