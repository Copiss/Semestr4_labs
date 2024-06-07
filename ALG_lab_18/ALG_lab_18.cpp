/*Лабораторная 18.	
Решить задачу о суммах подмножеств, используя жадный алгоритм.*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
//Сортировка вставками для вектора целых чисел
void  sort(std::vector<int>& _arr) {
    for (int step = _arr.size() / 2; step > 0; step /= 2) {
        for (int i = step; i < _arr.size(); ++i) {
            int temp = _arr[i];
            int j;
            // Сортируем по модулю, начиная с шага step
            for (j = i; j >= step && abs(_arr[j - step]) < abs(temp); j -= step) {
                _arr[j] = _arr[j - step];
            }
            _arr[j] = temp;
        }
    }
};
//Проверяем, существует ли в исходном векторе подмножество, сумма элементов которого равна нулю
bool subsetSumZero(std::vector<int>& numbers) {

    for (int i = 0; i < numbers.size() - 1; ++i) {
        int sum = numbers[i];
        for (int j = i + 1; j < numbers.size(); ++j) {
            if (abs(sum) > abs(sum + numbers[j])) {
                sum += numbers[j];
            }
        }
        if (sum == 0)
            return true;
    }
    return false;
}

int main() {
    std::vector<int> numbers = { -7, -3, 10, 4 }; //наши чиселки

    sort(numbers); //сортируем их

    if (subsetSumZero(numbers)) //Ну и, собственно, смотрим, есть ли нулевая сумма подмножеств
    {
        std::cout << "Yes,there sum exists" << std::endl;
    }
    else 
    {
        std::cout << "No, there doesn't exist" << std::endl;
    }

    return 0;
}