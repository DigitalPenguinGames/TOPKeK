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

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}

float getModule(const sf::Vector2f &orig, const sf::Vector2f &des) {
    return std::sqrt(std::pow(std::abs(des.x-orig.x), 2) + std::pow(std::abs(des.y-orig.y), 2));
}

float radToAngle(float rad) {
    return rad * 180 / M_PI;
}

float floatangleToRad(float angle) {
    return angle * M_PI / 180;
}

bool isCollisioning(sf::Vector2f point1, float radius1, sf::Vector2f point2, float radius2) {
    return (getModule(point1,point2) < radius1+radius2);
}
