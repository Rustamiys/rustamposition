#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//https://proginfo.ru

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

void clearcmd() {
	cin.clear();
	cin.ignore(10, '\n');
	system("cls");
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
	getline(cin, newKS.name_ks);
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
	if ((cin.fail()) || (0 > newKS.amount_work_ks) || (newKS.amount_work_ks > newKS.amount_ks)) {
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
		cout << "Труба\n" << "<<\n";
		cout << "Диаметр: " << newPipe.diam_pipe << endl;
		cout << "Длина: " << newPipe.len_pipe << endl;
		if (newPipe.work_pipe == 1) {
			cout << "В работе\n" << ">>\n";
		}
		else {
			cout << "Не в работе\n" << ">>\n";
		}
		
	}
	else {
	cout << "Труба не найдена\n";
	}
}

void print_ks(bool bool_ks, ks& newKS) {
	if (bool_ks) {
		cout << "КС\n" << "<<\n";
		cout << "Имя: " << newKS.name_ks << endl;
		cout << "Количество цехов: " << newKS.amount_ks << endl;
		cout << "Количество цехов в работе: " << newKS.amount_work_ks << endl;
		cout << "Эфективность: " << newKS.index_ks << "\n" << ">>\n";
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

void edit_ks(ks& newKS) {
	cout << "Ввод: ";
	int enter;
	cin >> enter;
	if ((cin.fail()) || ((enter != 1) && (enter != 2) && (enter != 0))) {
		cin.clear();
		cin.ignore(10, '\n');
		cout << "Введите корректные данные\n";
		edit_ks(newKS);
	}
	else {
		if ((enter == 1) && (newKS.amount_ks - newKS.amount_work_ks <= 0)) {
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Цехов в работе максимальное количество\n";
			edit_ks(newKS);
		}
		else if ((enter == 2) && (newKS.amount_work_ks <= 0)) {
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Цехов в работе минимальное количество\n";
			edit_ks(newKS);
		}
		else if (enter == 1) {
			newKS.amount_work_ks++;
			clearcmd();
			cout << "КС успешно изменена!\n";
		}
		else if (enter == 2) {
			newKS.amount_work_ks--;
			clearcmd();
			cout << "КС успешно изменена!\n";
		}
		else clearcmd();
	}
}

void save_to_file(pipe& newPipe, ks& newKS) {
	ofstream fout;
	fout.open("output.txt");

	if (!fout.is_open()) {
		cout << "Не получилось открыть файл!";
	}
	else {
		fout << newPipe.diam_pipe << endl;
		fout << newPipe.len_pipe << endl;
		fout << newPipe.work_pipe << endl;

		fout << newKS.name_ks << endl;
		fout << newKS.amount_ks << endl;
		fout << newKS.amount_work_ks << endl;
		fout << newKS.amount_work_ks << endl;
	}
	fout.close();
}

bool download_from_file(pipe& newPipe, ks& newKS) {
	ifstream fin;
	fin.open("input.txt");
	bool bool_valid = true;
	if (!fin.is_open()) {
		cout << "Не получилось открыть файл!";
	}
	else {
		int i = 0;
		for (i == 0; i <= 6; i++) {
			if (i == 0) {
				fin >> newPipe.diam_pipe;
				if (newPipe.diam_pipe < 0){
					bool_valid = false;
				}
			}
			else if (i == 1) {
				fin >> newPipe.len_pipe;
				if (newPipe.len_pipe < 0) {
					bool_valid = false;
				}
			}
			else if (i == 2) {
				fin >> newPipe.work_pipe;
				if ((newPipe.work_pipe != 0) && (newPipe.work_pipe != 1)) {
					bool_valid = false;
				}
			}
			else if (i == 3) {
				fin >> newKS.name_ks;
			}
			else if (i == 4) {
				fin >> newKS.amount_ks;
				if (newKS.amount_ks < 0) {
					bool_valid = false;
				}
			}
			else if (i == 5) {
				fin >> newKS.amount_work_ks;
				if ((newKS.amount_work_ks < 0) || (newKS.amount_ks < newKS.amount_work_ks)) {
					bool_valid = false;
				}
			}
			else if (i == 6) {
				fin >> newKS.index_ks;
				if (newKS.index_ks < 0) {
					bool_valid = false;
				}
			}
		}
	}
	fin.close();
	return bool_valid;
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
				cout << "Труба успешно изменена!\n";
			}
			else {
				clearcmd();
				cout << "Труба не найдена\n";
			}
		}
		else if (numint == 5) {
			if (bool_ks) {
				clearcmd();
				cout << "Цехов всего: " << newKS.amount_ks << endl;
				cout << "Цехов в работе: " << newKS.amount_work_ks << endl;
				cout << "1. Увеличить количество цехов\n";
				cout << "2. Уменьшить количество цехов\n";
				cout << "0. Выход в главное меню\n";
				edit_ks(newKS);
			}
			else {
				clearcmd();
				cout << "КС не найдена\n";
			}
		}
		else if (numint == 6) {
			if (bool_ks && bool_pipe) {
				save_to_file(newPipe, newKS);
			}
			else {
				cout << "Данных не достаточно\n";
			}
			clearcmd();
			cout << "Успешно сохранено\n";
		}
		else if (numint == 7) {
			clearcmd();
			if (download_from_file(newPipe, newKS)) {
				bool_ks = true;
				bool_pipe = true;
			}
			else {
				cout << "Ошибка\n";
			}
			 
		}
		else {
			return 0;
		}
	}
}
