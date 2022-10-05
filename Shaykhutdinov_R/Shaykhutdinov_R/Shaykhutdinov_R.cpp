#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct pipe
{
	double diam_pipe;
	double len_pipe;
	bool work_pipe;
};

struct ks
{
	string name_ks;
	int amount_ks;
	int amount_work_ks;
	double index_ks;
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

void clear_buffer() {
	cin.clear();
	cin.ignore(1024, '\n');
}

int numbermenu() {
	int numint;
	for (;;) {
		cin >> numint;
		if ((cin.fail()) || (numint > 7)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			return numint;
		}
	}
}

void clearcmd() {
	clear_buffer();
	system("cls");
}

void enter_diam(pipe& newPipe) {
	cout << "Диаметр: ";
	for (;;) {
		cin >> newPipe.diam_pipe;
		if ((cin.fail()) || (newPipe.diam_pipe <= 0)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			break;
		}
	}
}

void enter_len(pipe& newPipe) {
	cout << "Длина: ";
	for (;;) {
		cin >> newPipe.len_pipe;
		if ((cin.fail()) || (newPipe.len_pipe <= 0)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			break;
		}
	}
}

void enter_work(pipe& newPipe) {
	cout << "В работе: ";
	for (;;) {
		cin >> newPipe.work_pipe;
		if (cin.fail()) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			break;
		}
	}
}


void enter_pipe(pipe& newPipe) {

	enter_diam(newPipe);
	enter_len(newPipe);
	enter_work(newPipe);

	clearcmd();
	cout << "Труба добавлена\n";

}

void enter_name(ks& newKS) {
	cout << "Имя: ";
	getline(cin, newKS.name_ks);
}

void enter_amount(ks& newKS) {
	cout << "Количество цехов: ";
	for (;;) {
		cin >> newKS.amount_ks;

		if ((cin.fail()) || (newKS.amount_ks < 0)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}

		else {
			break;
		}
	}
}

void enter_amount_work(ks& newKS) {
	cout << "Количество цехов в работе:";
	for (;;) {
		cin >> newKS.amount_work_ks;

		if ((cin.fail()) || (newKS.amount_work_ks < 0) || (newKS.amount_work_ks > newKS.amount_ks)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}

		else {
			break;
		}
	}
}

void enter_index(ks& newKS) {
	cout << "Эффективность: ";
	for (;;) {
		cin >> newKS.index_ks;

		if ((cin.fail()) || (newKS.index_ks <= 0)) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}

		else {
			break;
		}
	}
}

void enter_ks(ks& newKS) {
	enter_name(newKS);
	enter_amount(newKS);
	enter_amount_work(newKS);
	enter_index(newKS);

	clearcmd();
	cout << "КС добавлена\n";

}


void print_pipe(const pipe& newPipe) {
	cout << "Труба\n" << "<<\n";
	cout << "Диаметр: " << newPipe.diam_pipe << endl;
	cout << "Длина: " << newPipe.len_pipe << endl;
	cout << (newPipe.work_pipe ? "В работе" : "Не в работе") << endl << ">>\n";
}

void print_ks(const ks& newKS) {
	cout << "КС\n" << "<<\n";
	cout << "Имя: " << newKS.name_ks << endl;
	cout << "Количество цехов: " << newKS.amount_ks << endl;
	cout << "Количество цехов в работе: " << newKS.amount_work_ks << endl;
	cout << "Эфективность: " << newKS.index_ks << endl << ">>\n";
}

void edit_pipe(pipe& newPipe) {
	cout << (newPipe.work_pipe ? "Труба находится в работе" : "Труба не находится в работе") << endl;
	cout << "В работе: ";
	for (;;) {
		cin >> newPipe.work_pipe;
		if (cin.fail()) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			clearcmd();
			cout << "Труба успешно изменена!\n";
			break;
		}
	}
}

void edit_ks(ks& newKS) {
	cout << "Цехов всего: " << newKS.amount_ks << endl;
	cout << "Цехов в работе: " << newKS.amount_work_ks << endl;
	cout << "1. Увеличить количество цехов\n";
	cout << "2. Уменьшить количество цехов\n";
	cout << "0. Выход в главное меню\n";
	cout << "Пункт номер: ";
	for (;;) {
		int enter;
		cin >> enter;
		if ((cin.fail()) || ((enter != 1) && (enter != 2) && (enter != 0))) {
			clear_buffer();
			cout << "Введите корректные данные: ";
		}
		else {
			if ((enter == 1) && (newKS.amount_ks <= newKS.amount_work_ks)) {
				clear_buffer();
				cout << "Цехов в работе максимальное количество\n";
				cout << "Введите корректные данные: ";
			}
			else if ((enter == 2) && (newKS.amount_work_ks <= 0)) {
				clear_buffer();
				cout << "Цехов в работе минимальное количество\n";
				cout << "Введите корректные данные: ";
			}
			else if (enter == 1) {
				newKS.amount_work_ks++;
				clearcmd();
				cout << "КС успешно изменена!\n";
				break;
			}
			else if (enter == 2) {
				newKS.amount_work_ks--;
				clearcmd();
				cout << "КС успешно изменена!\n";
				break;
			}
			else {
				clearcmd();
				break;
			}
		}
	}
}

void save_to_file(const pipe& newPipe, const ks& newKS) {
	ofstream fout;
	fout.open("output.txt");

	if (!fout.is_open()) {
		cout << "Не получилось открыть файл!";
	}

	else {
		if ((newPipe.diam_pipe > 0) && (newPipe.len_pipe > 0) && ((newPipe.work_pipe == 1) || (newPipe.work_pipe == 0))) {

			fout << newPipe.diam_pipe << endl;
			fout << newPipe.len_pipe << endl;
			fout << newPipe.work_pipe << endl;
		}
		else {
			fout << 0 << endl << 0 << endl << 0 << endl;
		}

		if ((newKS.amount_ks >= 0) && (newKS.amount_work_ks >= 0) && (newKS.index_ks > 0) && (newKS.amount_work_ks <= newKS.amount_ks)) {
			fout << newKS.name_ks << endl;
			fout << newKS.amount_ks << endl;
			fout << newKS.amount_work_ks << endl;
			fout << newKS.amount_work_ks << endl;
		}
	}

	fout.close();
}

void download_from_file(pipe& newPipe, ks& newKS, bool& bool_pipe, bool& bool_ks) {
	ifstream fin;
	string line;
	bool_pipe = true;
	bool_ks = true;

	fin.open("output.txt");

	if (!fin.is_open()) {
		cout << "Не получилось открыть файл!";
	}
	else {
		fin >> newPipe.diam_pipe;
		fin >> newPipe.len_pipe;
		fin >> newPipe.work_pipe;

		getline(fin, newKS.name_ks);
		getline(fin, newKS.name_ks);

		fin >> newKS.amount_ks;
		fin >> newKS.amount_work_ks;
		fin >> newKS.index_ks;

		if ((newPipe.diam_pipe > 0) && (newPipe.len_pipe > 0) && ((newPipe.work_pipe == 1) || (newPipe.work_pipe == 0))) {
			bool_pipe = 1;
		}
		else {
			bool_pipe = 0;
		}
		if ((newKS.amount_ks >= 0) && (newKS.amount_work_ks >= 0) && (newKS.index_ks > 0) && (newKS.amount_work_ks <= newKS.amount_ks)) {
			bool_ks = 1;
		}
		else {
			bool_ks = 0;
		}
	}
	
	cout << (bool_pipe ? "Труба загрузилась" : "Труба не загрузилaсь") << endl;
	cout << (bool_ks ? "КС загрузилась" : "КС не загрузилaсь") << endl;
	
	fin.close();
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

		clearcmd();

		if (numint == 1) {
			enter_pipe(newPipe);

			bool_pipe = true;
		}
		else if (numint == 2) {
			enter_ks(newKS);

			bool_ks = true;
		}
		else if (numint == 3) {
			if (bool_pipe) {
				print_pipe(newPipe);
			}
			else {
				cout << "Труба не найдена!\n";
			}

			if (bool_ks) {
				print_ks(newKS);
			}
			else {
				cout << "КС не найдена!\n";
			}
		}
		else if (numint == 4) {
			if (bool_pipe) {

				edit_pipe(newPipe);
			}
			else {
				cout << "Труба не найдена\n";
			}
		}
		else if (numint == 5) {
			if (bool_ks) {
				edit_ks(newKS);
			}
			else {
				cout << "КС не найдена\n";
			}
		}
		else if (numint == 6) {
			if (bool_ks || bool_pipe) {
				save_to_file(newPipe, newKS);
				cout << "Успешно сохранено\n";
			}
			else {
				cout << "Данных недостаточно\n";
			}
		}
		else if (numint == 7) {
			download_from_file(newPipe, newKS, bool_pipe, bool_ks);
		}
		else {
			return 0;
		}
	}
}
