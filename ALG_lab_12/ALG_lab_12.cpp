/*Лабораторная 12.	
Реализовать алгоритм Кнута-Морриса-Пратта для поиска по образцу*/

#include <iostream>
#include <string>
#include <vector>
//Функция KMP для вычисления таблицы префиксов-суффиксов
std::vector<int> KMP(const std::string& pattern) {
    std::vector<int> arr(pattern.size(), 0); //Для хранения значений таблицы
    int i = 1, j = 0; 
    while (i < pattern.size()) {
        //Если символы совпадают, устанавливаем значение вектора и идём дальше
        if (pattern[j] == pattern[i]) 
        {
            arr[i] = j + 1;
            i++; j++;
        }
        else
            if (j == 0) {
                arr[i] = 0; //Иначе значение нулевое
                i++;
            }
            else j = arr[j - 1];
    }
    return arr;
}
//Поиска шаблона в тексте с использованием алгоритма КМП
void searchPattern(const std::string& text, const std::string& pattern) {
    int n = text.size();    //Длина текста
    int m = pattern.size(); //Длина шаблона
    std::vector<int> p = KMP(pattern); //Получаем таблицу префиксов-суффиксов для шаблона
    int i = 0, j = 0, check = 0; //Инициализируем переменные для цикла и проверки
    while (i < n) { // Проходимся  по тексту
        if (text[i] == pattern[j]) { // Если символы совпадают, идём к следующему символу
            i++;
            j++;
            if (j == m) { // Если весь шаблон найден, делаем отметку и выводем индекс, где нашли наш шаблон
                check = 1; 
                std::cout << "Pattern found at index " << i - m << std::endl; 
            }
        }
        else {
            if (j > 0)
                j = p[j - 1]; // Используем таблицу префиксов-суффиксов для сдвига
            else
                i++;
        }
        if (i == n && !check) // Если достигнут конец текста и шаблон не найден
            std::cout << "There is no pattern in the text " << std::endl;    std::vector<int> p = KMP(pattern); // Получаем таблицу префиксов-суффиксов для шаблона
        int i = 0, j = 0, check = 0; // Инициализируем переменные для цикла и проверки
        while (i < n) { // Проходим по тексту
            if (text[i] == pattern[j]) { // Если символы совпадают
                i++;
                j++;
                if (j == m) { // Если весь шаблон найден
                    check = 1; // Устанавливаем флаг
                    std::cout << "Pattern found at index " << i - m << std::endl; // Выводим индекс, где найден шаблон
                }
            }
            else {
                if (j > 0)
                    j = p[j - 1]; // Используем таблицу префиксов-суффиксов для сдвига
                else
                    i++;
            }
            if (i == n && !check) // Если достигнут конец текста и шаблон не найден
                std::cout << "There is no pattern in the text " << std::endl; // Выводим сообщение о том, что шаблон не найден, то выводим соответствующее сообщение
        }
    }
}

int main() {
    std::string text = " abcabca abacbab abcabcabc"; //Наш текст
    std::string pattern = "abcabc"; //Шаблон, котороый ищем
    searchPattern(text, pattern);
    return 0;
}