#include "figure.h"
#include <cmath>

using namespace std;

namespace Figure {

    void Figure::SetOffset_X(double x) {
        geom_props.xc += (x / 10.0);
    }

    void Figure::SetOffset_Y(double y) {
        geom_props.yc += (y / 10.0);
    }

    void Figure::EnableHole() {
        geom_props.area *= -1;

        geom_props.axial_moments.Ix *= -1;
        geom_props.axial_moments.Iy *= -1;
        geom_props.axial_moments.Ixy *= -1;

        is_hole = true;
    }

    void RotatableFigure::SetAngle(double angle) {
        angle_ = angle * M_PI / 180;
        double Ix = geom_props.axial_moments.Ix;
        double Iy = geom_props.axial_moments.Iy;
        double Ixy = geom_props.axial_moments.Ixy;

        geom_props.axial_moments.Ix = ((Ix + Iy) / 2) + ((Ix - Iy) / 2) * cos(2 * angle_) - Ixy * sin(2 * angle_);
        geom_props.axial_moments.Iy = ((Ix + Iy) / 2) - ((Ix - Iy) / 2) * cos(2 * angle_) + Ixy * sin(2 * angle_);
        geom_props.axial_moments.Ixy = ((Ix - Iy) / 2) * sin(2 * angle_) + Ixy * cos(2 * angle_);

        for(auto& vertex : vertexes) {
            double new_x = vertex.x * cos(angle_) - vertex.y * sin(angle_);
            double new_y = vertex.x * sin(angle_) + vertex.y * cos(angle_);

            vertex.x = new_x;
            vertex.y = new_y;
        }

    }

    GeomProps Figure::GetGeomProps() const {
        return geom_props;
    }


    Rectangle::Rectangle(double width, double height) : width_(width / 10.0), height_(height / 10.0) {
        geom_props.xc = (width_ / 2);
        geom_props.yc = (height_ / 2);

        geom_props.area = width_ * height_;

        geom_props.axial_moments.Ix = (width_ * pow(height_, 3)) / 12;
        geom_props.axial_moments.Iy = (height_ * pow(width_, 3)) / 12;
        geom_props.axial_moments.Ixy = 0;

        vertexes.push_back({-width_ / 2, -height_ / 2});
        vertexes.push_back({-width_ / 2, height_ / 2});
        vertexes.push_back({width_ / 2, height_ / 2});
        vertexes.push_back({width_ / 2, -height_ / 2});
    }

    Circle::Circle(double radius) : radius_(radius / 10.0) {
        geom_props.xc = radius_;
        geom_props.yc = radius_;

        geom_props.area = M_PI * pow(radius_, 2);

        geom_props.axial_moments.Ix = (M_PI * pow(radius_, 4)) / 4;
        geom_props.axial_moments.Iy = (M_PI * pow(radius_, 4)) / 4;
        geom_props.axial_moments.Ixy = 0;

        vertexes.push_back({radius_, 0});
    }

    RightTriangle::RightTriangle(double width, double height) : width_(width / 10.0), height_(height / 10.0) {
        geom_props.xc = (width_ / 3);
        geom_props.yc = (height_ / 3);

        geom_props.area = (width_ * height_) / 2;

        geom_props.axial_moments.Ix = (width_ * pow(height_, 3)) / 36;
        geom_props.axial_moments.Iy = (height_ * pow(width_, 3)) / 36;
        geom_props.axial_moments.Ixy = -(pow(width_, 2) * pow(height_, 2)) / 72;

        vertexes.push_back({-width_ / 3, -height_ / 3});
        vertexes.push_back({-width_ / 3, 2 * height_ / 3});
        vertexes.push_back({2 * width_ / 3, -height_ / 3});
    }

}
