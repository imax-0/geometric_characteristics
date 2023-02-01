#pragma once
#include "figure.h"
#include <vector>
#include <limits>
#include <memory>

class Section {
public:
    Section() = default;
    Figure::Figure& AddRectangle(double width, double height, double angle);
    Figure::Figure& AddRightTriangle(double width, double height, double angle);
    Figure::Figure& AddCircle(double radius);

    void DeleteFigure(size_t number);
    void StartCalc(std::ostream& output);

private:
    std::vector<Figure::Figure> figures;
    double min_x = std::numeric_limits<double>::max();	// Минимальные координаты сечения, относительно которых
    double min_y = std::numeric_limits<double>::max();	// считается центр тяжести

    GeomProps geom_props;									// Геометрические характеристики сечения
    void ComputeMinCoords();
    void ComputeTotalArea();
    void ComputeGravityCenter();
    void ComputeAxialMomentsOfInertia();
    void ComputeAxisRotationAngle();
    void ComputeMainCentralMomentsOfInertia();

    void PrintGeomProps(std::ostream& output) const;
};
