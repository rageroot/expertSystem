#include "knowledge.h"

Knowledge::Knowledge()
{

    count_elements = 0; //получаем количество элементов


    for(int i = 1;;++i){ //перебираем все подобные файлы, пока они есть
            string tmp = to_string(i) + ".txt";
            moto tmp_struct;

            ifstream motoInfo(tmp.c_str());     //получаем имя модели и
            if(!motoInfo.is_open()){ //если не нашли файл, то дальше не смотрим
                break;
            }
            count_elements++; //не забываем счетчик элементов увеличивать
            motoInfo >> tmp_struct.model; //пишем номер файла
            tmp_struct.file_number = i;
            tmp_struct.valid = true;    //не забываем выставить валидность
            tmp_struct.favorit = NULL;
            while(!motoInfo.eof()){       //далее, получаем факты про модель
                string tmp_facts;
                motoInfo >> tmp_facts;
                tmp_struct.facts.push_back(tmp_facts);
            }
            knowledge_base.push_back(tmp_struct); //пишем временную структуру в основную базу
            tmp_struct.facts.clear();
            motoInfo.close();

    }
}

void Knowledge::showBase(){
    if(knowledge_base.empty()){
        cout << "База пустой, совсем пустой =..(" << endl;
    }
    else{
        for(moto knowledge_element : knowledge_base){
            cout << "Название: " << knowledge_element.model << endl;
            cout << "Факты: ";
            for(string fact: knowledge_element.facts)
                cout << fact << " ";
            cout << endl;
        }
   }
}

int Knowledge::addMoto(string name_moto, vector <string> facts_moto){
     moto newMoto;              //создаем экземпляр структуры
    newMoto.model = name_moto;  //заполняем
    newMoto.file_number = knowledge_base.size();
    for(string fact: facts_moto)    //переносим факты в структуру
        newMoto.facts.push_back(fact);
    knowledge_base.push_back(newMoto); //пихаем в общий вектор
    count_elements++;
    saveMot(count_elements);
    return newMoto.file_number;
}


string Knowledge::to_string(int param){
    string str = "";
        for(str = ""; param ; param /= 10)
            str += (char)('0' + param % 10);
        reverse(str.begin(), str.end());
        return str;
}

void Knowledge::saveMot(int index){//index - 1, потому что количество всегда на 1 больше индекса
    string filename = to_string(index) + ".txt";
    ofstream knowFile(filename.c_str(), ios_base::trunc);
    string tmpString = "";
    for(int i = 0; i < knowledge_base[index - 1].model.length(); ++i){
        if(knowledge_base[index - 1].model[i] != ' '){
            tmpString += knowledge_base[index - 1].model[i];
        }
        else{
            tmpString += "_";
        }
    }
    knowFile << tmpString << " ";
    for(string fact: knowledge_base[index - 1].facts)
        knowFile << fact << " ";
    knowFile.close();

}

void Knowledge::clearValid(){    //Сбрасывает валидность
    for(moto& mot: knowledge_base){
        mot.valid = true;
        mot.favorit = false;
    }
    importantFacts.clear(); //забываем все важные факты для следующей итерации
}

void Knowledge::setValid(string fact, bool flag){
    for(moto& mot: knowledge_base){  //перебираем базу
        if(find(mot.facts.begin(), mot.facts.end(), fact) != mot.facts.end())
            if(flag){    //если в базе фактов есть нужный факт
                mot.favorit = true; //то валидируем его, или делаем важным
                importantFacts.push_back(fact); //добавляем факт в вектор важных файлов
            }
            else{
                mot.valid = false;
            }
    }
}

int Knowledge::getValidCount(){
    //вот здеся надо фигачить проверку, что все валидные моты содержат все важные факты


    bool isFavorit = false;
    for(moto mot: knowledge_base){  //смотрим выбрал ли пользователь какой то обязательный факт
        if(mot.favorit){
            isFavorit = true;
            break;
        }
    }
    validString.clear(); //сбрасываем валидный вектор
    int res = 0;
    for(moto& mot: knowledge_base){
       if(isFavorit){           //в зависимости от этого подсчитываем колиество валидных моделей
           if((mot.valid) && (mot.favorit)){
               res++;
               validString.push_back(mot.model);
           }
       }
       else if(mot.valid){
                res++;
                validString.push_back(mot.model);
            }
       //cout << mot.model << "\n fav" << mot.favorit << "\n val" << mot.valid << "\n" << endl;
    }

    //в общем, справедливо, что у каждого предложенного мотоцикла должны быть все ВАЖНЫЕ параметры,
    //за тем требуется еще один перебор базы после формирования полного вектора ВАЖНЫХ параметров
    //и проверка, что у всех отобранных моделей есть все ВАЖНЫЕ характеристики

    return res;
}

string Knowledge::getAllValid(){
    string tmpString ="";
    for(moto& mot: knowledge_base){
        tmpString += mot.model;
        tmpString += "\n";
    }
    return tmpString;
}
