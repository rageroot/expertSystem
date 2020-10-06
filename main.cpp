/*экспертная система  "Выбор мотоцикла"*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <knowledge.h>
#include <facts.h>

#define ONESTR 22   //отступы для чистки экрана
#define EXP_MENU 16


using namespace std;

string getLineInCase();
void clear(int);

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    unsigned short rez = 0;
    unsigned short menu_item = 0;
    Knowledge knowladge_base;
    Facts facts;

    while(true){
        if(rez == 0){
            cout << "Привет пользователь! В каком режиме ты хочешь зайти?\n1- Режим пользователя\n2- режим эксперта" << endl;
            cin >> rez;
        }
        if(rez == 1){
            int countQuestion = 0;  //сколько вопросов уже было задано
            int nTry = 1; //номер попытки для угадывания
            bool uniq;  //флаг уникальности факта, чтобы факты не повторялись
            int randomFact; //переменная для хранения номер рандомного факта
            vector <int> numberQuestion; //номер уже заданных вопросов, чтобы не повторялис
            numberQuestion.clear();
            clear(ONESTR);  //вопросы будут задаваться в рандомном порядке
            cout << "Привет пользователь!\nДавай попоробуем подобрать тебе мотоцикл?\n"
                    "Я задам тебе 6 вопросов, и на основании твоих ответов попробую подобрать нужную модель.\n"
                    "Если я не смогу определиться, то буду задавать дополнительные вопросы." << endl;
            bool result = false;
            while(!result){
                while(countQuestion < 6 * nTry){
                    countQuestion++;
                    cout << "Вопрос №" << countQuestion << endl;
                    uniq = false;
                    while(!uniq){
                        randomFact = rand() % facts.getCountFacts();
                        auto res = find(numberQuestion.begin(), numberQuestion.end(), randomFact); //ищем в векторе номер, выповший рандомом
                        if(res == numberQuestion.end()){
                            numberQuestion.push_back(randomFact);
                            uniq = true;
                        }
                    }
                    cout << "Важен ли для тебя следующий факт: " << facts.getFact(randomFact) << "?" << endl;
                    cout << "1 - Важен\n2- Не важен\n3- Категорически не нужен\nВаш выбор: ";
                    int choise;
                    cin >> choise;
                    switch (choise) {
                    case 1:
                            knowladge_base.setValid(facts.getFact(randomFact), true);
                        break;
                    case 3:
                            knowladge_base.setValid(facts.getFact(randomFact), false);
                        break;
                    default:
                        break;
                    }
                }
                //cout << knowladge_base.getValidCount() << endl;
                if((knowladge_base.getValidCount() > 3) && (nTry < 2)){
                    cout << "Под ваш выбор подходит много вариантов, поробуем конкретизировать, вам будет задано еще 6 "
                            "вопросов" << endl;
                    cout << "Нажмите ввод для продолжения" << endl;
                    getLineInCase();
                    nTry = 2;
                }
                else{
                    if(knowladge_base.getValidCount() == 0){
                        cout << "Мы не смогли подобрать вам мотоцикл, простите =(" << endl;
                    }
                    else
                    {
                        cout << "Мы уверены, что вам подойдут: " << endl;
                        cout << knowladge_base.getAllValid() << endl;
                    }
                    knowladge_base.clearValid(); //забываем все валидности
                    rez = 0; //выходим обратно в меню
                    cout << "Нажмите ввод для продолжения" << endl;
                    getLineInCase();
                    result = true; //флаг выхода из цикла
                    clear(ONESTR);
                }
             }
        }
        else{
            clear(EXP_MENU);
            cout << "###########Режим ЭКСПЕРТА#############" << endl;
            cout << "Меню:\n1- Показать базу знаний\n2- Показать базу фактов\n3- "
                    "Добавить запись в базу знаний\n4- Добавить факт\n5- Выход" << endl;

            cin >> menu_item;
            switch(menu_item){
                case 1 :knowladge_base.showBase();
                        cout << "Нажмите ввод для продолжения" << endl;
                        getLineInCase();
                        break;
                case 2 :
                        facts.showFacts();
                        cout << "Нажмите ввод для продолжения" << endl;
                        getLineInCase();
                        break;
                case 3 :{
                        clear(ONESTR);
                        cout << "Введите название мотоцикла:" << endl;
                        string name_moto = getLineInCase();
                        facts.showFacts();
                        string facts_moto;
                        cout << "Перечислите через пробел номера фактов, которые надо добавить к этой модели" << endl;
                        getline(cin, facts_moto); //костыль =)
                        facts_moto += " ";       //2 костыля =)
                        vector <string> facts_vec; //в вектор будем переносить факты из базы фактов
                        string number_fact = "";
                        for(int i = 0; i <= facts_moto.length(); i++){
                            if((facts_moto[i] != ' ') && (i != facts_moto.length() - 1)){    //дергаем номера фактов из строки
                                number_fact += facts_moto[i];
                            }
                            else{
                                facts_vec.push_back(facts.getFact(stoi((string)number_fact)));//когда дернули число- вырываем из базы факт и пишем во временный вектор
                                number_fact.clear();
                            }
                        }

                        int index = knowladge_base.addMoto(name_moto, facts_vec);
                        facts_vec.clear();

                        break;
                }
                case 4 :{           //добавление фактов
                             int work = 1;
                             while(work == 1){
                                cout << "Введите новый факт:" << endl;
                                int index = facts.addFact(getLineInCase());
                                clear(ONESTR);
                                cout << "Добавить еще один факт?\n1- Добавить\n2- Выйти" << endl;
                                cin >> work;

                            }
                             facts.saveBase();
                        break;
                }
                case 5 :rez = 0;
                        break;
            }
        }
    }

    return 0;
}

string getLineInCase(){
    string tmp;
    cin.ignore();
    getline(cin, tmp);
    return tmp;
}

void clear(int count){
    for(int i=0;i<count;i++)
    cout <<"\n";
}
