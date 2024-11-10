#include "pipe_ks.h"

// Реализация вспомогательных функций
void check_int(int& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите корректное число!" << endl;
        cin >> x;
    }
}

void check_bool(bool& x) {
    cin >> x;
    while (cin.fail() || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Труба в ремонте? (1 - да, 0 - нет)" << endl;
        cin >> x;
    }
}

void check_double(double& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите корректную эффективность!" << endl;
        cin >> x;
    }
}

// Реализация методов класса Pipe
Pipe::Pipe() : length(0), diametr(0), repair(false) {}

void Pipe::input() {
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

void Pipe::output() const {
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

void Pipe::toggleRepair() {
    repair = !repair;
    cout << "Статус изменен на " << repair << endl;
}

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

// Реализация методов класса KS
KS::KS() : workshops(0), workshops_in_work(0), eff(0.0) {}

void KS::input() {
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

void KS::output() const {
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

void KS::edit() {
    cout << "Количество цехов в работе " << endl;
    check_int(workshops_in_work);

    while (workshops < workshops_in_work) {
        cout << "Количество работающих станций должно быть меньше количества станций" << endl;
        check_int(workshops_in_work);
    }
    cout << "Эффективность" << endl;
    check_double(eff);
}

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
