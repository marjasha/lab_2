#include "pipe_ks.h"

// Инициализация статических полей
int Pipe::nextId = 1;
int KS::nextId = 1;

// Реализация универсальной функции проверки ввода
template <typename T>
void check_input(T& x, const string& prompt) {
    cout << prompt;
    cin >> x;
    while (cin.fail() || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите корректное значение!" << endl;
        cout << prompt;
        cin >> x;
    }
}

// Реализация методов класса Pipe
Pipe::Pipe() : id(nextId++), length(0), diametr(0), repair(false) {}

void Pipe::input() {
    cout << "Введите название трубы" << endl;
    cin.ignore();
    getline(cin, kilometr);

    check_input(length, "Введите длину: ");
    check_input(diametr, "Введите диаметр: ");
    check_input(repair, "Труба в ремонте? (1 - да, 0 - нет): ");
}

void Pipe::output() const {
    if (kilometr.empty()) {
        cout << "Нет данных" << endl;
    }
    else {
        cout << "ID: " << id << endl;
        cout << "Имя: " << kilometr << endl;
        cout << "Длина: " << length << endl;
        cout << "Диаметр: " << diametr << endl;
        cout << "В ремонте: " << (repair ? "да" : "нет") << endl;
    }
}

void Pipe::toggleRepair() {
    repair = !repair;
    cout << "Статус изменен на " << (repair ? "да" : "нет") << endl;
}

ofstream& operator<<(ofstream& file, const Pipe& p) {
    if (p.kilometr.empty()) {
        file << "Нет данных о трубе" << endl;
    }
    else {
        file << "Труба" << endl;
        file << "ID " << p.id << endl;
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
        istringstream(line.substr(3)) >> p.id;
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

// Реализация методов класса KS
KS::KS() : id(nextId++), workshops(0), workshops_in_work(0), eff(0.0) {}

void KS::input() {
    cout << "Введите название КС" << endl;
    cin.ignore();
    getline(cin, name);

    check_input(workshops, "Введите количество цехов: ");
    check_input(workshops_in_work, "Введите количество цехов в работе: ");

    while (workshops < workshops_in_work) {
        cout << "Количество работающих цехов должно быть меньше общего количества цехов" << endl;
        check_input(workshops_in_work, "Введите количество цехов в работе: ");
    }

    check_input(eff, "Введите эффективность: ");
}

void KS::output() const {
    if (name.empty()) {
        cout << "Нет данных" << endl;
    }
    else {
        cout << "ID: " << id << endl;
        cout << "Имя: " << name << endl;
        cout << "Количество цехов: " << workshops << endl;
        cout << "Количество цехов в работе: " << workshops_in_work << endl;
        cout << "Эффективность: " << eff << endl;
    }
}

void KS::edit() {
    check_input(workshops_in_work, "Введите количество цехов в работе: ");

    while (workshops < workshops_in_work) {
        cout << "Количество работающих цехов должно быть меньше общего количества цехов" << endl;
        check_input(workshops_in_work, "Введите количество цехов в работе: ");
    }

    check_input(eff, "Введите эффективность: ");
}

ofstream& operator<<(ofstream& file, const KS& ks) {
    if (ks.name.empty()) {
        file << "Нет данных о КС" << endl;
    }
    else {
        file << "КС" << endl;
        file << "ID " << ks.id << endl;
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
        istringstream(line.substr(3)) >> ks.id;
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


