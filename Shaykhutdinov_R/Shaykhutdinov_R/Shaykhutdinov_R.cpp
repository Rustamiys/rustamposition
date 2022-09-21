#include <iostream>
#include <string>

using namespace std;

struct pipe
{
    int diam_pipe;
    int len_pipe;
    bool work_pipe;
};

struct ks
{
    string name_ks;
    int amount_ks;
    int amount_work_ks;
    float index_ks;
    bool work_ks;
};

void printmenu() {
    cout << "1. Добавить трубу\n";
    cout << "2. Добавить КС\n";
    cout << "3. Просмотр всех объектов \n";
    cout << "4. Редактировать трубу \n";
    cout << "5. Редактировать КС \n";
    cout << "6. Сохранить \n";
    cout << "7. Загрузить \n";
    cout << "0. Выход \n";
}

void enter_diam(pipe& newPipe){
    cout << "Диаметр: ";
    cin >>newPipe.diam_pipe;
    if ((cin.fail()) || (newPipe.diam_pipe < 0)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_diam(newPipe);
    }
}

void enter_len(pipe & newPipe) {
    cout << "Длина: ";
    cin >> newPipe.len_pipe;
    if ((cin.fail()) || (newPipe.len_pipe < 0)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_len(newPipe);
    }
}

void enter_work(pipe & newPipe) {
    cout << "В работе: ";
    cin >> newPipe.work_pipe;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_work(newPipe);
    }
    newPipe.work_pipe;
}

void enter_name(ks & newKS) {
    cout << "Имя: ";
    cin >> newKS.name_ks;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_name(newKS);
    }
}

void enter_amount(ks& newKS) {
    cout << "Количество цехов: ";
    cin >> newKS.amount_ks;
    if ((cin.fail()) || (newKS.amount_ks < 0)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_amount(newKS);
    }
}

void enter_amount_work(ks& newKS) {
    cout << "Количество цехов в работе:";
    cin >> newKS.amount_work_ks;
    if ((cin.fail()) || (0 > newKS.amount_work_ks > newKS.amount_ks)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_amount_work(newKS);
    }
}

void enter_index(ks& newKS) {
    cout << "Эффективность: ";
    cin >> newKS.index_ks;
    if ((cin.fail()) || (newKS.index_ks <= 0)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные\n";
        enter_index(newKS);
    }
}

void print_pipe(pipe& newPipe) {
    if (true) {
        cout << "Труба:\n";
        cout << "Диаметр: " << newPipe.diam_pipe;
        cout << "Длина: " << newPipe.len_pipe;
    }
    else {
        cout << "Труба не найдена";
    }
}

void print_ks() {
    if (true) {

    }
    else {
        cout << "КС не найдена";
    }
}

void clearcmd() {
    cin.clear();
    cin.ignore(10, '\n');
    system("cls");
}

int numbermenu() {
    int numint;
    cin >> numint;
    if ((cin.fail()) || (numint > 7)) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Введите корректные данные: ";
        numbermenu();
    }
    else {
        return numint;
    }
}

int main()
{   
    
    setlocale(LC_ALL, "Russian");

    int numint;
    pipe newPipe;
    ks newKS;
   
    for (;;) {
   
        printmenu();
        cout << "Пункт номер: ";
        numint = numbermenu();
        
            
        if (numint == 0){
            return 0;
        }
        else if (numint == 1) {      
            clearcmd();

            enter_diam(newPipe);
            enter_len(newPipe);
            enter_work(newPipe);
            
            clearcmd();
            cout << "Труба добавлена\n";
        }
        else if (numint == 2) {
            clearcmd();

            enter_name(newKS);
            enter_amount(newKS);
            enter_amount_work(newKS);
            enter_index(newKS);

            clearcmd();
            cout << "КС добавлена\n";
        }
        else if (numint == 3) {
            clearcmd();
            
            print_pipe();
            print_ks();

            clearcmd();
        }
        else if (numint == 4) {
            return 0;
        }
        else if (numint == 5) {
            return 0;
        }
        else if (numint == 6) {
            return 0;
        }
        else {
            return 0;
        }
    }
}
