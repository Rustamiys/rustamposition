#include <iostream> 
#include <string>

using namespace std;

void printmenu();


int main()
{   
    setlocale(LC_ALL, "Russian");

    int numint;

    printmenu();
    cout << "Пункт номер: ";

    for (;;) {
        cin >> numint;
        if ((cin.fail()) || (numint > 7)) {
            cin.clear();
            cin.ignore(10, '\n');
            system("cls");
            printmenu();
            cout << "Введите корректные данные\n";
            cout << "Пункт номер: ";

        }
        else {
            system("cls");
            cout << numint<<"\n";
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
}
