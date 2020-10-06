#include "facts.h"

using namespace std;

Facts::Facts() //забираем все факты из файла
{
    ifstream factsFile("facts.txt");
    string tmp;
    while(!factsFile.eof()){
        factsFile >> tmp;
        facts_base.push_back(tmp);
    }
    facts_base.pop_back();
    factsFile.close();
}

void Facts::showFacts(){
    if(facts_base.empty())
        cout << "База совсем пустой =..(" << endl;
    else{
        short stroke = 0;//переменная для переноса строки после 3 вывода
        for(int i = 0; i < facts_base.size(); ++i){
            string tmpString = facts_base[i];
            for(int i = 0; i < tmpString.length(); ++i){  //заменяем нижнее подчеркивание на пробел
                if(tmpString[i] == '_')
                    tmpString[i] = ' ';
            }

           cout << i << " " << tmpString << "\t\t\t\t";
            stroke++;
            if(stroke == STROKE){
                cout << endl;
                stroke = 0;
            }
        }
        cout << endl;
    }
}

int Facts::addFact(string factName){
    string tmpString = "";                      //заменяем пробел на нижнее подчеркивание
    for(int i = 0; i < factName.length(); ++i)
        if(factName[i] != ' ')
            tmpString += factName[i];
        else
            tmpString += '_';
    int index = facts_base.size();
    facts_base.push_back(tmpString);
    return index;
}

void Facts::saveBase(){         //Записывает базу на файловую систему
    ofstream factFile("facts.txt", ios_base::trunc);
    for(int i = 0; i < facts_base.size(); ++i){
        factFile << facts_base[i] << " ";
    }
}

string Facts::getFact(int n){
    return facts_base[n];
}

int Facts::getCountFacts(){
    return facts_base.size();
}
