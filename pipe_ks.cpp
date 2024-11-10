#include "pipe_ks.h"

// ���������� ��������������� �������
void check_int(int& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "������� ���������� �����!" << endl;
        cin >> x;
    }
}

void check_bool(bool& x) {
    cin >> x;
    while (cin.fail() || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "����� � �������? (1 - ��, 0 - ���)" << endl;
        cin >> x;
    }
}

void check_double(double& x) {
    cin >> x;
    while (!x || x < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "������� ���������� �������������!" << endl;
        cin >> x;
    }
}

// ���������� ������� ������ Pipe
Pipe::Pipe() : length(0), diametr(0), repair(false) {}

void Pipe::input() {
    cout << "������� �������� �����" << endl;
    cin.ignore();
    getline(cin, kilometr);

    cout << "������� �����" << endl;
    check_int(length);

    cout << "������� �������" << endl;
    check_int(diametr);

    cout << "����� � �������? (1 - ��, 0 - ���):" << endl;
    check_bool(repair);
}

void Pipe::output() const {
    if (kilometr.empty()) {
        cout << "��� ������" << endl;
    }
    else {
        cout << "��� " << kilometr << endl;
        cout << "����� " << length << endl;
        cout << "������� " << diametr << endl;
        cout << "� ������� " << (repair ? "��" : "���") << endl;
    }
}

void Pipe::toggleRepair() {
    repair = !repair;
    cout << "������ ������� �� " << repair << endl;
}

ofstream& operator<<(ofstream& file, const Pipe& p) {
    if (p.kilometr.empty()) {
        file << "��� ������ � �����" << endl;
    }
    else {
        file << "�����" << endl;
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
KS::KS() : workshops(0), workshops_in_work(0), eff(0.0) {}

void KS::input() {
    cout << "������� �������� ��" << endl;
    cin.ignore();
    getline(cin, name);

    cout << "������� ���������� �����" << endl;
    check_int(workshops);

    cout << "������� ���������� ����� � ������" << endl;
    check_int(workshops_in_work);

    while (workshops < workshops_in_work) {
        cout << "���������� ���������� ������� ������ ���� ������ ���������� �������" << endl;
        check_int(workshops_in_work);
    }

    cout << "�������������" << endl;
    check_double(eff);
}

void KS::output() const {
    if (name.empty()) {
        cout << "��� ������" << endl;
    }
    else {
        cout << "��� " << name << endl;
        cout << "���������� ����� " << workshops << endl;
        cout << "���������� ����� � ������ " << workshops_in_work << endl;
        cout << "������������� " << eff << endl;
    }
}

void KS::edit() {
    cout << "���������� ����� � ������ " << endl;
    check_int(workshops_in_work);

    while (workshops < workshops_in_work) {
        cout << "���������� ���������� ������� ������ ���� ������ ���������� �������" << endl;
        check_int(workshops_in_work);
    }
    cout << "�������������" << endl;
    check_double(eff);
}

ofstream& operator<<(ofstream& file, const KS& ks) {
    if (ks.name.empty()) {
        file << "��� ������ � ��" << endl;
    }
    else {
        file << "��" << endl;
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
