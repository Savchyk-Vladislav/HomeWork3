#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T item) : data(item), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    // Метод добавления элемента в конец списка
    void add(T item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Метод вставки элемента в середину списка по индексу
    void insert(int index, T item) {
        if (index < 0 || index > size) {
            std::cerr << "Недопустимый индекс." << std::endl;
            return;
        }

        Node<T>* newNode = new Node<T>(item);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Метод подсчета количества элементов в списке
    int getSize() const {
        return size;
    }

    // Метод удаления элемента по индексу
    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Недопустимый индекс." << std::endl;
            return;
        }

        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
    }

    // Метод замены значения существующего элемента по индексу
    void set(int index, T item) {
        if (index < 0 || index >= size) {
            std::cerr << "Недопустимый индекс." << std::endl;
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = item;
    }

    // Метод получения значения элемента по индексу
    T get(int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Недопустимый индекс." << std::endl;
            throw std::out_of_range("Недопустимый индекс.");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Деструктор для освобождения памяти
    ~LinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList<int> list;

    list.add(1);
    list.add(2);
    list.add(3);

    std::cout << "List: ";
    for (int i = 0; i < list.getSize(); i++) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;

    list.insert(1, 4);
    list.remove(2);
    list.set(0, 0);

    std::cout << "Changed list: ";
    for (int i = 0; i < list.getSize(); i++) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
