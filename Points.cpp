#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int id; // Унікальний ідентифікатор точки
    double mass; // Маса точки

    Point(int id, double mass) : id(id), mass(mass) {}
};

int main() {
    int n; // Кількість початкових точок
    cout << "Enter the number of starting points:";
    cin >> n;

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        double mass;
        cout << "Enter point mass" << i + 1 << ": ";
        cin >> mass;
        points.emplace_back(i + 1, mass);
    }

    while (points.size() > 1) {
        // Знаходимо точку з найменшою масою
        double minMass = points[0].mass;
        int minIndex = 0;
        for (int i = 1; i < points.size(); ++i) {
            if (points[i].mass < minMass) {
                minMass = points[i].mass;
                minIndex = i;
            }
        }

        // Знаходимо найближчу точку з неспівпадаючим id
        int nearestIndex = (minIndex == 0) ? 1 : 0;
        double minDistance = abs(points[nearestIndex].id - points[minIndex].id);
        for (int i = 0; i < points.size(); ++i) {
            if (i != minIndex) {
                double distance = abs(points[i].id - points[minIndex].id);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestIndex = i;
                }
            }
        }

        // Передача маси
        points[nearestIndex].mass += points[minIndex].mass;
        points.erase(points.begin() + minIndex);
    }

    cout << "Remaining point: id=" << points[0].id << ", mass=" << points[0].mass << endl;

    return 0;
}
