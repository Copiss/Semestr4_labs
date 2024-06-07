/*Лабораторная 17.	
Решить задачу о раскладке по ящикам*/
//Мы тут должны понять, сколько минимально ящиков/коробочек нужно, чтоб сложить все наши предметы

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int minBoxesDP(std::vector<int>& items, int boxCapacity) 
{   //рассматриваем возможность нулевого ввода
    int n = items.size();
    if (n == 0)
        return 0;
    //Сотрируем предметы по размеру
    std::sort(items.begin(), items.end());

    std::vector<int> dp(boxCapacity + 1, INT_MAX); //оптимальное количество ящиков
    dp[0] = 0;
    //Смотрим, влезает ли в коробку предмет, если да, то обновляем данные, "складывая" предмет в коробку
    for (int i = 1; i <= boxCapacity; ++i) {
        for (int j = 0; j < n; ++j) {
            if (items[j] <= i && dp[i - items[j]] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - items[j]] + 1);
            }
        }
    }
    //Находим минимальное количество ящиков
    int minNumBoxes = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (items[i] > boxCapacity)
            return n;
        minNumBoxes = std::min(minNumBoxes, dp[boxCapacity - items[i]]);
    }

    return minNumBoxes;
}

int main() {
    std::vector<int> items = { 1, 1, 2, 2, 2, 2, 7 }; //объём предметов
    int boxCapacity = 10;                             //вместимость одной коробки

    int minNumBoxes = minBoxesDP(items, boxCapacity);
    std::cout << "Minimum number of boxes required: " << minNumBoxes << std::endl;

    return 0;
}