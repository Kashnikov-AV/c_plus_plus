#include <iostream>
#include <cmath>
#include <cstdlib>

// Структура узла бинарного дерева
struct TreeNode {
    double value;
    int index;       // Индекс в исходном массиве
    TreeNode* left;
    TreeNode* right;

    TreeNode(double val, int idx) : value(val), index(idx), left(nullptr), right(nullptr) {}
};

//функция перебора
int linear_search(double* arr, int N, double number);

//метод деления пополам дихотомия
int binary_search(double* arr, double number, int start, int end);

//функции для бинарного дерева
TreeNode* build_tree(double* arr, int start, int end);
int search_tree(TreeNode* root, double number);
void delete_tree(TreeNode* root);

int main()
{
    int N = 10;
    double start = 1.0;

    double* data_ptr = new double[N];

    // Создаем отсортированный массив
    for (int i = 0; i < N; i++) {
        double random_number = (double)rand() / RAND_MAX * 100;
        data_ptr[i] = start;
        start += random_number;
    }

    // Выводим массив
    std::cout << "Sorted array:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "[" << i << "]=" << data_ptr[i] << " ";
    }
    std::cout << std::endl << "Enter number to search: ";

    double number;
    std::cin >> number;

    // Линейный поиск
    int res = linear_search(data_ptr, N, number);
    std::cout << "\n=== Linear search ===" << std::endl;
    if (res >= 0) {
        std::cout << "i=" << res << " arr[i]= " << data_ptr[res];
        if (res + 1 < N) {
            std::cout << " arr[i+1]= " << data_ptr[res + 1];
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Number is outside array bounds" << std::endl;
    }

    // Бинарный поиск
    std::cout << "\n=== Binary search ===" << std::endl;
    int res2 = binary_search(data_ptr, number, 0, N - 1);
    if (res2 >= 0) {
        std::cout << "i=" << res2 << " arr[i]= " << data_ptr[res2];
        if (res2 + 1 < N) {
            std::cout << " arr[i+1]= " << data_ptr[res2 + 1];
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Number is outside array bounds" << std::endl;
    }

    // Построение и поиск в бинарном дереве
    std::cout << "\n=== Binary tree search ===" << std::endl;
    TreeNode* root = build_tree(data_ptr, 0, N - 1);
    int res3 = search_tree(root, number);
    if (res3 >= 0) {
        std::cout << "i=" << res3 << " arr[i]= " << data_ptr[res3];
        if (res3 + 1 < N) {
            std::cout << " arr[i+1]= " << data_ptr[res3 + 1];
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Number is outside array bounds" << std::endl;
    }

    // Освобождение памяти
    delete_tree(root);
    delete[] data_ptr;

    system("PAUSE");
    return 0;
}

int linear_search(double* arr, int N, double number)
{
    // Проверка границ
    if (number < arr[0]) return -1;
    if (number >= arr[N - 1]) return N - 1;

    for (int i = 0; i < N - 1; i++) {
        if (number >= arr[i] && number < arr[i + 1]) {
            return i;
        }
    }
    return -1;
}

int binary_search(double* arr, double number, int start, int end)
{
    // Проверка границ
    if (start > end) {
        return -1;
    }

    if (number < arr[0]) return -1;
    if (number >= arr[end]) return end;

    int middle = (start + end) / 2;

    // Проверяем, находится ли number между arr[middle] и arr[middle+1]
    if (middle + 1 <= end && number >= arr[middle] && number < arr[middle + 1]) {
        return middle;
    }

    // Если число меньше середины, ищем в левой части
    if (number < arr[middle]) {
        return binary_search(arr, number, start, middle - 1);
    }
    // Иначе ищем в правой части
    else {
        return binary_search(arr, number, middle + 1, end);
    }
}

// Построение сбалансированного бинарного дерева поиска
TreeNode* build_tree(double* arr, int start, int end)
{
    if (start > end) {
        return nullptr;
    }

    // Находим середину для сбалансированного дерева
    int mid = (start + end) / 2;

    // Создаем узел с значением из массива
    TreeNode* node = new TreeNode(arr[mid], mid);

    // Рекурсивно строим левое и правое поддеревья
    node->left = build_tree(arr, start, mid - 1);
    node->right = build_tree(arr, mid + 1, end);

    return node;
}

// Поиск в бинарном дереве
int search_tree(TreeNode* root, double number)
{
    TreeNode* current = root;
    TreeNode* candidate = nullptr;  // Ближайший меньший узел

    while (current != nullptr) {
        // Если нашли точное совпадение
        if (number == current->value) {
            return current->index;
        }

        // Если число меньше текущего значения
        if (number < current->value) {
            // Переходим в левое поддерево
            current = current->left;
        }
        // Если число больше текущего значения
        else {
            // Запоминаем этот узел как кандидата
            candidate = current;
            // Переходим в правое поддерево
            current = current->right;
        }
    }

    // Возвращаем индекс кандидата (ближайший меньший элемент)
    if (candidate != nullptr) {
        return candidate->index;
    }

    return -1;  // Число меньше всех элементов массива
}

// Удаление дерева (очистка памяти)
void delete_tree(TreeNode* root)
{
    if (root == nullptr) {
        return;
    }

    // Рекурсивно удаляем левое и правое поддеревья
    delete_tree(root->left);
    delete_tree(root->right);

    // Удаляем текущий узел
    delete root;
}