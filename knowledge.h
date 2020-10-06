#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Knowledge
{
public:
    Knowledge();
    void showBase();
    int addMoto(string, vector<string>); //принимаем название мотоцикла и факты про него, возвращаем его индекс в базе
    void clearValid(); //сбрасывает валидность у всех мотоциклов
    void setValid(string, bool); //меняет валидность.
    int getValidCount(); //получаем количество валидных записей, попутно формируем валидную строку
    string getAllValid(); //выводим валидную строку

private:
    void saveMot(int); //сохраняет информацию про одну единицу на диск
    string to_string(int);
    struct moto{    //структруа, описывает элемент вектора
        string model;
        vector <string> facts;
        unsigned short file_number;
        bool valid; //переменная работает при выборе в режиме пользователя.
                    //программа помечает для себя валидные модели
                    //и когда их остается мало- делает вывод
                    //изначально все мотоциклы валидны
        bool favorit; //истина, при выборе важных параметров
    };

    vector <moto> knowledge_base;
    unsigned short count_elements; //количество элементов в базе знаний
    vector <string> validString;             //вектор содержит список валидных моделей
    vector <string> importantFacts;     //вектор важных фактов, которые должны быть у всех моделей
};

#endif // KNOWLEDGE_H
