#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class ArrayList {
public:
    // Конструктор по умолчанию
    ArrayList() {}

    // Добавление элемента в конец списка
    void add(const T& item) {
        items.push_back(item);
    }

    // Вставка элемента по индексу
    void insert(int index, const T& item) {
        if (index < 0 || index > items.size()) {
            throw out_of_range("Index out of range");
        }
        items.insert(items.begin() + index, item);
    }

    // Получение размера списка
    int size() const {
        return items.size();
    }

    // Удаление элемента по индексу
    void remove(int index) {
        if (index < 0 || index >= items.size()) {
            throw out_of_range("Index out of range");
        }
        items.erase(items.begin() + index);
    }

    // Замена элемента по индексу
    void set(int index, const T& item) {
        if (index < 0 || index >= items.size()) {
            throw out_of_range("Index out of range");
        }
        items[index] = item;
    }

    // Получение элемента по индексу
    T get(int index) const {
        if (index < 0 || index >= items.size()) {
            throw out_of_range("Index out of range");
        }
        return items[index];
    }

private:
    std::vector<T> items;
};

int main() {
    ArrayList<int> list;

    list.add(1);
    list.add(2);
    list.add(3);

    cout << "Size: " << list.size() << endl;

    list.insert(1, 4);

    cout << "Size after insertion: " << list.size() << endl;

    cout << "Element at index 2: " << list.get(2) << endl;

    list.set(0, 0);

    cout << "Element at index 0 after set: " << list.get(0) << endl;

    list.remove(3);

    cout << "Size after removal: " << list.size() << endl;

    return 0;
}
