#include <vector>
#include <string>
#include <cmath>

class Robot {
    int id; //id-робота
    double baseX, baseY, baseZ; //Положение в пространстве робота
    double angleMin, angleMax; //Минимальный и максимальный угол поворота 
    double vMax; //Максимальная скорость
    double AMax; //Максимальное ускорение
    double toolClearance; //Радиус "сферы" - максимальная длина робота
    double safeDist; //Минимальное расстояние между сферами
public:
    //Конструктор с параметрами
    Robot(int id, double baseX, double baseY, double baseZ,
            double angleMin, double angleMax,
            double vMax, double AMax,
            double toolClearance, double safeDist) : id(id), baseX(baseX), baseY(baseY), baseZ(baseZ),
                vMax(vMax), toolClearance(toolClearance), safeDist(safeDist) {}

};