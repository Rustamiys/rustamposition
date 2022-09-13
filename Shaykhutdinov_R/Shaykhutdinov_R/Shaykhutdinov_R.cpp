#include <iostream> 
#include <string>

using namespace std;

void printmenu();

int CheckInt(string i);

int main()
{   
    setlocale(LC_ALL, "Russian");

    string numstr;
    int numint;

    printmenu();

    for (;;) {
        cin >> numstr;
        numint = CheckInt(numstr);
        if (-1 < numint < 10) {
            cout << "dmkfmdmkd";
        }
        else {
            printmenu();
        }
    }

    return 0;
}

void printmenu() {

    cout << "1. Добавить трубу\n";
    cout << "2. Добавить КС\n";
    cout << "3. Просмотр всех объектов \n";
    cout << "4. Редактировать трубу \n";
    cout << "5. Редактировать КС \n";
    cout << "6. Сохранить \n";
    cout << "7. Загрузить \n";
    cout << "Пункт номер: ";
}

int CheckInt(string i) {

}

