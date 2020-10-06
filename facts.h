#ifndef FACTS_H
#define FACTS_H
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iostream>
#include <iomanip>

#define STROKE 1    //количество фактов при выводе в одно строку

using namespace std;

class Facts
{
public:
    Facts();
    void showFacts(); //выводит на экран все факты
    int addFact(string); //добавляет новый факт
    void saveBase();
    string getFact(int); //выводит факт по его номеру
    int getCountFacts(); //выводит количество фактов в базе
private:
    vector<string> facts_base;
};

#endif // FACTS_H
