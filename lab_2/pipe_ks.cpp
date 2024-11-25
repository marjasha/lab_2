#include "pipe_ks.h"

// ������������� ����������� �����
int Pipe::nextId = 1;
int KS::nextId = 1;

// ���������� ������������� ������� �������� �����
template <typename T>
void check_input(T& x, const string& prompt) {
    cout << prompt;
    cin >> x;
    while (cin.fail() || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "������� ���������� ��������!" << endl;
        cout << prompt;
        cin >> x;
    }
}

// ���������� ������� ������ Pipe
Pipe::Pipe() : id(nextId++), length(0), diametr(0), repair(false) {}

void Pipe::input() {
    cout << "������� �������� �����" << endl;
    cin.ignore();
    getline(cin, kilometr);

    check_input(length, "������� �����: ");
    check_input(diametr, "������� �������: ");
    check_input(repair, "����� � �������? (1 - ��, 0 - ���): ");
}

void Pipe::output() const {
    if (kilometr.empty()) {
        cout << "��� ������" << endl;
    }
    else {
        cout << "ID: " << id << endl;
        cout << "���: " << kilometr << endl;
        cout << "�����: " << length << endl;
        cout << "�������: " << diametr << endl;
        cout << "� �������: " << (repair ? "��" : "���") << endl;
    }
}

void Pipe::toggleRepair() {
    repair = !repair;
    cout << "������ ������� �� " << (repair ? "��" : "���") << endl;
}

ofstream& operator<<(ofstream& file, const Pipe& p) {
    if (p.kilometr.empty()) {
        file << "��� ������ � �����" << endl;
    }
    else {
        file << "�����" << endl;
        file << "ID " << p.id << endl;
        file << "��� " << p.kilometr << endl;
        file << "����� " << p.length << endl;
        file << "������� " << p.diametr << endl;
        file << "� ������� " << (p.repair ? "��" : "���") << endl;
    }
    return file;
}

ifstream& operator>>(ifstream& file, Pipe& p) {
    string line;
    getline(file, line);
    if (line == "��� ������ � �����") {
        cout << "��� ������ � �����" << endl;
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
        p.repair = (line.substr(10) == "��");
    }
    return file;
}

// ���������� ������� ������ KS
KS::KS() : id(nextId++), workshops(0), workshops_in_work(0), eff(0.0) {}

void KS::input() {
    cout << "������� �������� ��" << endl;
    cin.ignore();
    getline(cin, name);

    check_input(workshops, "������� ���������� �����: ");
    check_input(workshops_in_work, "������� ���������� ����� � ������: ");

    while (workshops < workshops_in_work) {
        cout << "���������� ���������� ����� ������ ���� ������ ������ ���������� �����" << endl;
        check_input(workshops_in_work, "������� ���������� ����� � ������: ");
    }

    check_input(eff, "������� �������������: ");
}

void KS::output() const {
    if (name.empty()) {
        cout << "��� ������" << endl;
    }
    else {
        cout << "ID: " << id << endl;
        cout << "���: " << name << endl;
        cout << "���������� �����: " << workshops << endl;
        cout << "���������� ����� � ������: " << workshops_in_work << endl;
        cout << "�������������: " << eff << endl;
    }
}

void KS::edit() {
    check_input(workshops_in_work, "������� ���������� ����� � ������: ");

    while (workshops < workshops_in_work) {
        cout << "���������� ���������� ����� ������ ���� ������ ������ ���������� �����" << endl;
        check_input(workshops_in_work, "������� ���������� ����� � ������: ");
    }

    check_input(eff, "������� �������������: ");
}

ofstream& operator<<(ofstream& file, const KS& ks) {
    if (ks.name.empty()) {
        file << "��� ������ � ��" << endl;
    }
    else {
        file << "��" << endl;
        file << "ID " << ks.id << endl;
        file << "��� " << ks.name << endl;
        file << "���������� ����� " << ks.workshops << endl;
        file << "���������� ����� � ������ " << ks.workshops_in_work << endl;
        file << "������������� " << ks.eff << endl;
    }
    return file;
}

ifstream& operator>>(ifstream& file, KS& ks) {
    string line;
    getline(file, line);
    if (line == "��� ������ � ��") {
        cout << "��� ������ � ��" << endl;
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


