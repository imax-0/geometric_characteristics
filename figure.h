#pragma once
#include "geom_props.h"

#include <iostream>
#include <vector>
#include <string>

namespace Figure {

    struct Point {
        double x = 0;
        double y = 0;
    };

    class Figure {
    public:
        void SetOffset_X(double x);				// Задать смещение фигуры по оси X
        void SetOffset_Y( double y);			// Задать смещение фигуры по оси Y
        void EnableHole();						// Фигура является отверстием (по умолчанию фигура не является отверстием)
        GeomProps GetGeomProps() const;

        std::vector<Point> vertexes;			// Координаты вершин фигуры относительно центра тяжести

        bool is_hole = false;
    protected:
        GeomProps geom_props;					// Геометрические характеристики сечения относительно центральных осей
    };

    class RotatableFigure : public Figure {  // Класс для фигур, которые есть смысл поворачивать (пример исключения - круг)
    public:
        void SetAngle(double angle);			// Задать угол поворота фигуры в градусах
    protected:
        double angle_ = 0;						// Угол поворота фигуры относительно центра масс в радианах
    };

    class Rectangle : public RotatableFigure {
    public:
        Rectangle(double width, double height);
    private:
        double width_;
        double height_;
    };

    class Circle : public Figure {
    public:
        Circle(double radius);
    private:
        double radius_;
    };

    class RightTriangle : public RotatableFigure {
    public:
        RightTriangle(double width, double height);
    private:
        double width_;
        double height_;
    };

}
