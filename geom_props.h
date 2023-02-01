#pragma once

struct AxialMomentsOfInertia {			// Осевые моменты инерции относительно центральных осей
    double Ix;							// Относительно оси X
    double Iy;							// Относительно оси Y
    double Ixy;   						// Центробежный
};

struct MainCentralMomentsOfInertia {	// Главные центральные моменты инерции
    double Iu;							// Относительно главный центральной оси U(X)
    double Iv;							// Относительно главной центральной оси V(Y)
};

struct GeomProps {
    double xc, yc;						    // Координаты центра тяжести фигуры
    double area; 		   					// Площадь
    double angle_of_rotation;				// Угол поворота центральных осей для того, чтобы они стали главными
    AxialMomentsOfInertia axial_moments;
    MainCentralMomentsOfInertia main_moments;
};
