#include <iostream>
#include "c_vector.h"

int main()
{
    double tau = 0.001; // такт по времени
    const double G = 1.0; // константа притяжения

    int n = 5; // кол-во точек

    point* arr_point = new point[5];

    arr_point[0].x = 3.0;
    arr_point[0].y = 3.0;
    arr_point[0].z = 0.0;
    arr_point[0].vx = 0.0;
    arr_point[0].vy = 0.0;
    arr_point[0].vz = 0.0;
    arr_point[0].mass = 10.0;

    arr_point[1].x = 3.0;
    arr_point[1].y = 1.0;
    arr_point[1].z = 0.0;
    arr_point[1].vx = 1.0;
    arr_point[1].vy = 0.0;
    arr_point[1].vz = 0.0;
    arr_point[1].mass = 1.0;

    arr_point[2].x = 5.0;
    arr_point[2].y = 3.0;
    arr_point[2].z = 0.0;
    arr_point[2].vx = 0.0;
    arr_point[2].vy = 1.0;
    arr_point[2].vz = 0.0;
    arr_point[2].mass = 1.0;

    arr_point[3].x = 3.0;
    arr_point[3].y = 5.0;
    arr_point[3].z = 0.0;
    arr_point[3].vx = -1.0;
    arr_point[3].vy = 0.0;
    arr_point[3].vz = 0.0;
    arr_point[3].mass = 1.0;

    arr_point[4].x = 1.0;
    arr_point[4].y = 3.0;
    arr_point[4].z = 0.0;
    arr_point[4].vx = 0.0;
    arr_point[4].vy = -1.0;
    arr_point[4].vz = 0.0;
    arr_point[4].mass = 1.0;

    // считаем сумму сил для одной точки допустим для первой
    for (int iter = 0; iter < 10; iter++) {
        double f_sum = 0.0;

        int point = iter % n;

        for (int i = 0; i < n; i++) {
            if (point != i){
                c_vector v(arr_point[point], arr_point[i]);

                // считаем силу скаляр
                f_sum += G * (arr_point[0].mass - arr_point[i].mass) / (v.length * v.length);
            }
        }

        // новые скорости
        arr_point[point].vx = (tau / arr_point[point].mass) * (arr_point[point].x * f_sum) + arr_point[point].vx;
        arr_point[point].vy = (tau / arr_point[point].mass) * (arr_point[point].y * f_sum) + arr_point[point].vy;
        arr_point[point].vz = (tau / arr_point[point].mass) * (arr_point[point].z * f_sum) + arr_point[point].vz;

        // новые координаты точки
        arr_point[point].x = arr_point[point].vx * tau;
        arr_point[point].y = arr_point[point].vy * tau;
        arr_point[point].z = arr_point[point].vz * tau;

        // point
        std::cout << "point " << point << std::endl;
        std::cout << "x y z" << std::endl;
        std::cout << arr_point[point].x << "\t" << arr_point[point].y << "\t" << arr_point[point].z << std::endl;
        std::cout << "vx vy vz" << std::endl;
        std::cout << arr_point[point].vx << "\t" << arr_point[point].vy << "\t" << arr_point[point].vz << std::endl;
    }

    system("PAUSE");
    return 0;
}


