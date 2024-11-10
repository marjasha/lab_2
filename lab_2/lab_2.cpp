#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

// Функция для проверки корректности ввода целого числа
void check_int(int& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите корректное число!" << endl;
        cin >> x;
    }
}

// Функция для проверки корректности ввода булевого значения
void check_bool(bool& x) {
    cin >> x;
    while (cin.fail() || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Труба в ремонте? (1 - да, 0 - нет)" << endl;
        cin >> x;
    }
}

// Функция для проверки корректности ввода числа с плавающей точкой
void check_double(double& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите корректную эффективность!" << endl;
        cin >> x;
    }
}

class Pipe {
private:
    string kilometr;
    int length;
    int diametr;
    bool repair;

public:
    Pipe() : length(0), diametr(0), repair(false) {}

    void input() {
        cout << "Введите название трубы" << endl;
        cin.ignore();
        getline(cin, kilometr);

        cout << "Введите длину" << endl;
        check_int(length);

        cout << "Введите диаметр" << endl;
        check_int(diametr);

        cout << "Труба в ремонте? (1 - да, 0 - нет):" << endl;
        check_bool(repair);
    }

    void output() const {
        if (kilometr.empty()) {
            cout << "Нет данных" << endl;
        }
        else {
            cout << "Имя " << kilometr << endl;
            cout << "Длина " << length << endl;
            cout << "Диаметр " << diametr << endl;
            cout << "В ремонте " << (repair ? "да" : "нет") << endl;
        }
    }

    void toggleRepair() {
        repair = !repair;
        cout << "Статус изменен на " << repair << endl;
    }

    friend ofstream& operator<<(ofstream& file, const Pipe& p);
    friend ifstream& operator>>(ifstream& file, Pipe& p);
};

ofstream& operator<<(ofstream& file, const Pipe& p) {
    if (p.kilometr.empty()) {
        file << "Нет данных о трубе" << endl;
    }
    else {
        file << "Труба" << endl;
        file << "Имя " << p.kilometr << endl;
        file << "Длина " << p.length << endl;
        file << "Диаметр " << p.diametr << endl;
        file << "В ремонте " << (p.repair ? "да" : "нет") << endl;
    }
    return file;
}

ifstream& operator>>(ifstream& file, Pipe& p) {
    string line;
    getline(file, line);
    if (line == "Нет данных о трубе") {
        cout << "Нет данных о трубе" << endl;
    }
    else {
        getline(file, line);
        p.kilometr = line.substr(4);
        getline(file, line);
        istringstream(line.substr(7)) >> p.length;
        getline(file, line);
        istringstream(line.substr(9)) >> p.diametr;
        getline(file, line);
        p.repair = (line.substr(10) == "да");
    }
    return file;
}

class KS {
private:
    string name;
    int workshops;
    int workshops_in_work;
    double eff;

public:
    KS() : workshops(0), workshops_in_work(0), eff(0.0) {}

    void input() {
        cout << "Введите название КС" << endl;
        cin.ignore();
        getline(cin, name);

        cout << "Введите количество цехов" << endl;
        check_int(workshops);

        cout << "Введите количество цехов в работе" << endl;
        check_int(workshops_in_work);

        while (workshops < workshops_in_work) {
            cout << "Количество работающих станций должно быть меньше количества станций" << endl;
            check_int(workshops_in_work);
        }

        cout << "Эффективность" << endl;
        check_double(eff);
    }

    void output() const {
        if (name.empty()) {
            cout << "Нет данных" << endl;
        }
        else {
            cout << "Имя " << name << endl;
            cout << "Количество цехов " << workshops << endl;
            cout << "Количество цехов в работе " << workshops_in_work << endl;
            cout << "Эффективность " << eff << endl;
        }
    }

    void edit() {
        cout << "Количество цехов в работе " << endl;
        check_int(workshops_in_work);

        while (workshops < workshops_in_work) {
            cout << "Количество работающих станций должно быть меньше количества станций" << endl;
            check_int(workshops_in_work);
        }
        cout << "Эффективность" << endl;
        check_double(eff);
    }

    friend ofstream& operator<<(ofstream& file, const KS& ks);
    friend ifstream& operator>>(ifstream& file, KS& ks);
};

ofstream& operator<<(ofstream& file, const KS& ks) {
    if (ks.name.empty()) {
        file << "Нет данных о КС" << endl;
    }
    else {
        file << "КС" << endl;
        file << "Имя " << ks.name << endl;
        file << "Количество цехов " << ks.workshops << endl;
        file << "Количество цехов в работе " << ks.workshops_in_work << endl;
        file << "Эффективность " << ks.eff << endl;
    }
    return file;
}

ifstream& operator>>(ifstream& file, KS& ks) {
    string line;
    getline(file, line);
    if (line == "Нет данных о КС") {
        cout << "Нет данных о КС" << endl;
    }
    else {
        getline(file, line);
        ks.name = line.substr(4);
        getline(file, line);
        istringstream(line.substr(17)) >> ks.workshops;
        getline(file, line);
        istringstream(line.substr(26)) >> ks.workshops_in_work;
        getline(file, line);
        istringstream(line.substr(12)) >> ks.eff;
    }
    return file;
}

int main() {
    Pipe newPipe;
    KS newKS;
    int command;

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n1 - Добавить трубу\n2 - Добавить КС\n3 - Просмотр всех объектов\n4 - Редактировать трубу\n5 - Редактировать КС\n6 - Сохранить\n7 - Загрузить\n0 - Выход\n";
        cin >> command;

        switch (command) {
        case 1: newPipe.input(); break;
        case 2: newKS.input(); break;
        case 3:
            cout << "Трубы\n"; newPipe.output();
            cout << "КС\n"; newKS.output();
            break;
        case 4: newPipe.toggleRepair(); break;
        case 5: newKS.edit(); break;
        case 6: {
            ofstream file("output.txt");
            if (file.is_open()) {
                file << newPipe << newKS;
                file.close();
            }
            else {
                cout << "Не получается открыть файл" << endl;
            }
            break;
        }
        case 7: {
            ifstream file("output.txt");
            if (file.is_open()) {
                file >> newPipe >> newKS;
                file.close();
            }
            else {
                cout << "Не получается открыть файл" << endl;
            }
            break;
        }
        case 0: return 0;
        default: cout << "Неверная команда!" << endl;
        }
    }
}
