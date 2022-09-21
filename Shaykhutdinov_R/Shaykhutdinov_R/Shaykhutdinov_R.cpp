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

void enter_diam(pipe& newPipe) {
	cout << "Диаметр: ";
	cin >> newPipe.diam_pipe;
	if ((cin.fail()) || (newPipe.diam_pipe < 0)) {
		cin.clear();
		cin.ignore(10, '\n');
		cout << "Введите корректные данные\n";
		enter_diam(newPipe);
	}
}

void enter_len(pipe& newPipe) {
	cout << "Длина: ";
	cin >> newPipe.len_pipe;
	if ((cin.fail()) || (newPipe.len_pipe < 0)) {
		cin.clear();
		cin.ignore(10, '\n');
		cout << "Введите корректные данные\n";
		enter_len(newPipe);
	}
}

void enter_work(pipe& newPipe) {
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

void enter_name(ks& newKS) {
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

void print_pipe(bool bool_pipe, pipe& newPipe) {
	if (bool_pipe) {
		cout << "Труба\n" << "{\n";
		cout << "Диаметр: " << newPipe.diam_pipe << endl;
		cout << "Длина: " << newPipe.len_pipe << endl;
		if (newPipe.work_pipe == 1) {
			cout << "В работе\n" << "}\n";
		}
		else {
			cout << "Не в работе\n" << "}\n";
		}
		
	}
	else {
		cout << "Труба не найдена\n";
	}
}

void print_ks(bool bool_ks, ks& newKS) {
	if (bool_ks) {
		cout << "КС:\n";
		cout << "Имя: " << newKS.name_ks << endl;
		cout << "Количество цехов: " << newKS.amount_ks << endl;
		cout << "Количество цехов в работе: " << newKS.amount_work_ks << endl;
		cout << "Эфективность: " << newKS.index_ks;
	}
	else {
		cout << "КС не найдена\n";
	}
}

void edit_pipe(pipe& newPipe) {
	if (newPipe.work_pipe) {
		cout << "Труба находится в работе\n";
		enter_work(newPipe);
	}
	else {
		cout << "Труба не находится в работе\n";
		enter_work(newPipe);
	}
}

/*void edit_ks(ks&newKS) {
	if (newKS.) {
		cout << "Труба находится в работе\n";
		enter_work(newPipe);
	}
	else {
		cout << "Труба не находится в работе\n";
		enter_work(newPipe);
	}
}*/

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
	bool bool_pipe = false, bool_ks = false;
	int numint;
	pipe newPipe;
	ks newKS;

	for (;;) {

		printmenu();
		cout << "Пункт номер: ";
		numint = numbermenu();


		if (numint == 0) {
			return 0;
		}
		else if (numint == 1) {
			clearcmd();

			enter_diam(newPipe);
			enter_len(newPipe);
			enter_work(newPipe);

			clearcmd();
			bool_pipe = 1;
			cout << "Труба добавлена\n";
		}
		else if (numint == 2) {
			clearcmd();

			enter_name(newKS);
			enter_amount(newKS);
			enter_amount_work(newKS);
			enter_index(newKS);

			clearcmd();
			bool_ks = 1;
			cout << "КС добавлена\n";
		}
		else if (numint == 3) {
			clearcmd();

			print_pipe(bool_pipe, newPipe);
			print_ks(bool_ks, newKS);

		}
		else if (numint == 4) {
			if (bool_pipe) {
				clearcmd();

				edit_pipe(newPipe);
				
				clearcmd();
				cout << "Труба успешно изменена!";
			}
			else {
				cout << "Труба не найдена";
			}
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
