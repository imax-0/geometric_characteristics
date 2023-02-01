#include "section.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int prompt_menu_item() {
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. Добавить прямоугольник\n"
         << "2. Добавить прямоугольный треугольник\n"
         << "3. Добавить круг\n"
         << "4. Удалить фигуру\n"
         << "5. Провести расчёт\n"
         << "6. Выйти\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

void ParseGeneralParameters(Figure::Figure &figure) {
    double x;
    cout << "Введите отступ по оси X: ";
    cin >> x;
    cout << "\n";
    figure.SetOffset_X(x);

    double y;
    cout << "Введите отступ по оси Y: ";
    cin >> y;
    cout << "\n";
    figure.SetOffset_Y(y);

    bool is_hole;
    cout << "Фигура является отверстием? (1 - да, 0 - нет): ";
    cin >> is_hole;
    cout << "\n";

    if (is_hole) {
        figure.EnableHole();
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Section section;

    while (true) {
        int variant = prompt_menu_item();

        switch (variant) {
            case 1: {
                double width, height, angle;
                cout << "Введите ширину: ";
                cin >> width;
                cout << "\n";

                cout << "Введите высоту: ";
                cin >> height;
                cout << "\n";

                cout << "Введите угол поворота фигуры: ";
                cin >> angle;
                cout << "\n";

                Figure::Figure &rect = section.AddRectangle(width, height, angle);

                ParseGeneralParameters(rect);
                break;
            }
            case 2: {
                double width, height, angle;
                cout << "Введите ширину: ";
                cin >> width;
                cout << "\n";

                cout << "Введите высоту: ";
                cin >> height;
                cout << "\n";

                cout << "Введите угол поворота фигуры: ";
                cin >> angle;
                cout << "\n";

                Figure::Figure &trian = section.AddRightTriangle(width, height, angle);
                ParseGeneralParameters(trian);
                break;
            }
            case 3: {
                double radius;
                cout << "Введите радиус: ";
                cin >> radius;
                cout << "\n";

                Figure::Figure &circle = section.AddCircle(radius);
                ParseGeneralParameters(circle);
                break;
            }
            case 4:
                size_t number;
                cout << "Введите номер фигуры: ";
                cin >> number;

                section.DeleteFigure(number);

                cout << "Фигура удалена" << endl;
                cout << "\n";
                break;
            case 5:
                section.StartCalc(cout);
                break;
            case 6:
                cout << "Выход из программы..." << endl;
                exit(EXIT_SUCCESS);
            default:
                cerr << "Вы выбрали неверный вариант" << endl;
                break;
        }
    }
}
