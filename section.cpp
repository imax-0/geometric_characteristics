#include "section.h"
#include <cmath>

using namespace std;

void Section::ComputeMinCoords() {
    for (auto& figure : figures) {
        const auto& figure_geom_props = figure.GetGeomProps();
        for (auto& vertex : figure.vertexes) {
            if (vertex.x + figure_geom_props.xc < min_x) {
                min_x = vertex.x + figure_geom_props.xc;
            }

            if (vertex.y + figure_geom_props.yc < min_y) {
                min_y = vertex.y + figure_geom_props.yc;
            }

        }
    }
}

void Section::ComputeTotalArea() {
    double total_area = 0;
    for (auto& figure : figures) {
        const auto& figure_geom_props = figure.GetGeomProps();
        total_area += figure_geom_props.area;
    }
    geom_props.area = total_area;
}

void Section::ComputeGravityCenter() {
    double Sx = 0, Sy = 0;	// Статические моменты для нахождения центра тяжести сечения
    for (auto& figure : figures) {
        const auto& figure_geom_props = figure.GetGeomProps();
        Sx += figure_geom_props.area * (figure_geom_props.yc - min_y);
        Sy += figure_geom_props.area * (figure_geom_props.xc - min_x);
    }
    geom_props.xc = Sy / geom_props.area;
    geom_props.yc = Sx / geom_props.area;
}

void Section::ComputeAxialMomentsOfInertia() {
    double Ix = 0, Iy = 0, Ixy = 0;
    for (auto& figure : figures) {
        const auto& figure_geom_props = figure.GetGeomProps();
        Ix += figure_geom_props.axial_moments.Ix +
              figure_geom_props.area *
              pow((geom_props.yc - (figure_geom_props.yc - min_y)), 2);
        Iy += figure_geom_props.axial_moments.Iy +
              figure_geom_props.area *
              pow((geom_props.xc - (figure_geom_props.xc - min_x)), 2);
        Ixy += figure_geom_props.axial_moments.Ixy +
               figure_geom_props.area *
               (geom_props.yc - (figure_geom_props.yc - min_y)) *
               (geom_props.xc - (figure_geom_props.xc - min_x));
    }
    geom_props.axial_moments.Ix = Ix;
    geom_props.axial_moments.Iy = Iy;
    geom_props.axial_moments.Ixy = Ixy;
}

void Section::ComputeAxisRotationAngle() {
    if (geom_props.axial_moments.Ixy == 0) {
        geom_props.angle_of_rotation = 0;
    } else {
        geom_props.angle_of_rotation =
                atan((2 * geom_props.axial_moments.Ixy) / (geom_props.axial_moments.Iy - geom_props.axial_moments.Ix)) / 2;
    }
}

void Section::ComputeMainCentralMomentsOfInertia() {
    double Ix = geom_props.axial_moments.Ix;
    double Iy = geom_props.axial_moments.Iy;
    double Ixy = geom_props.axial_moments.Ixy;
    double angle = geom_props.angle_of_rotation;

    geom_props.main_moments.Iu = ((Ix + Iy) / 2) + ((Ix - Iy) / 2) * cos(2 * angle) - Ixy * sin(2 * angle);
    geom_props.main_moments.Iv = ((Ix + Iy) / 2) - ((Ix - Iy) / 2) * cos(2 * angle) + Ixy * sin(2 * angle);
}

Figure::Figure& Section::AddRectangle(double width, double height, double angle) {
    Figure::Rectangle rect(width, height);
    rect.SetAngle(angle);

    figures.push_back(rect);
    return figures.back();
}

Figure::Figure& Section::AddRightTriangle(double width, double height, double angle) {
    Figure::RightTriangle trian(width, height);
    trian.SetAngle(angle);

    figures.push_back(trian);
    return figures.back();
}

Figure::Figure& Section::AddCircle(double radius) {
    Figure::Circle circle(radius);

    figures.push_back(circle);
    return figures.back();
}

void Section::DeleteFigure(size_t number) {
    figures.erase(figures.begin() + number - 1);
}

void Section::StartCalc(ostream& output) {
    ComputeMinCoords();
    ComputeTotalArea();
    ComputeGravityCenter();
    ComputeAxialMomentsOfInertia();
    ComputeAxisRotationAngle();
    ComputeMainCentralMomentsOfInertia();

    PrintGeomProps(output);
}

void Section::PrintGeomProps(ostream& output) const {
    output << "Площадь сечения: " << geom_props.area << '\n'
           << "Центр тяжести Ox: " << geom_props.xc << '\n'
           << "Центр тяжести Oy: " << geom_props.yc << '\n'
           << "Осевой момент инерции Ixc: " << geom_props.axial_moments.Ix << '\n'
           << "Осевой момент инерции Iyc: " << geom_props.axial_moments.Iy << '\n'
           << "Осевой момент инерции Ixcyc: " << geom_props.axial_moments.Ixy << '\n'
           << "Угол поворота осей: " << (geom_props.angle_of_rotation * 180) / M_PI << '\n'
           << "Iu: " << geom_props.main_moments.Iu << '\n'
           << "Iv: " << geom_props.main_moments.Iv << '\n';
}
