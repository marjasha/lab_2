#include "pipe_ks.h"

int Pipe::nextId = 1;
int KS::nextId = 1;

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

Pipe::Pipe() : id(nextId++), length(0), diametr(0), repair(false) {}

void Pipe::input() {
    cout << "������� �������� �����: ";
    cin.ignore();
    getline(cin, kilometr);

    check_input(length, "������� �����: ");
    check_input(diametr, "������� �������: ");
    check_input(repair, "����� � �������? (1 - ��, 0 - ���): ");
}


void Pipe::output() const {
    cout << "ID: " << id << endl;
    cout << "��������: " << kilometr << endl;
    cout << "�����: " << length << endl;
    cout << "�������: " << diametr << endl;
    cout << "� �������: " << (repair ? "��" : "���") << endl;
}

void Pipe::toggleRepair() {
    repair = !repair;
    cout << "������ ������� �� " << (repair ? "��" : "���") << endl;
}

ofstream& operator<<(ofstream& file, const Pipe& p) {
    file << "�����" << endl;
    file << "ID " << p.id << endl;
    file << "��� " << p.kilometr << endl;
    file << "����� " << p.length << endl;
    file << "������� " << p.diametr << endl;
    file << "� ������� " << (p.repair ? "��" : "���") << endl;
    return file;
}

ifstream& operator>>(ifstream& file, Pipe& p) {
    string line;


    getline(file, line);
    istringstream(line.substr(line.find(' ') + 1)) >> p.id;
    getline(file, line);
    p.kilometr = line.substr(line.find(' ') + 1);
    getline(file, line);
    istringstream(line.substr(line.find(' ') + 1)) >> p.length;
    getline(file, line);
    istringstream(line.substr(line.find(' ') + 1)) >> p.diametr;
    getline(file, line);
    string repairStatus = line.substr(line.find(' ') + 1);
    p.repair = (repairStatus == "��");

    return file;
}



KS::KS() : id(nextId++), workshops(0), workshops_in_work(0), eff(0.0) {}

void KS::input() {
    cout << "������� �������� ��: ";
    cin.ignore();
    getline(cin, name);

    check_input(workshops, "������� ���������� �����: ");
    check_input(workshops_in_work, "������� ���������� ����� � ������: ");

    while (workshops_in_work > workshops) {
        cout << "���������� ���������� ����� ������ ���� ������ ������ ���������� �����." << endl;
        check_input(workshops_in_work, "������� ���������� ����� � ������: ");
    }

    check_input(eff, "������� �������������: ");
}

void KS::output() const {
    cout << "ID: " << id << endl;
    cout << "��������: " << name << endl;
    cout << "���������� �����: " << workshops << endl;
    cout << "���������� ����� � ������: " << workshops_in_work << endl;
    cout << "������� ����������������� �����: " << getIdlePercentage() << "%" << endl;
    cout << "�������������: " << eff << endl;
}

void KS::edit() {
    check_input(workshops_in_work, "������� ���������� ����� � ������: ");
    while (workshops_in_work > workshops) {
        cout << "���������� ���������� ����� ������ ���� ������ ������ ���������� �����." << endl;
        check_input(workshops_in_work, "������� ���������� ����� � ������: ");
    }

    check_input(eff, "������� �������������: ");
}

double KS::getIdlePercentage() const {
    if (workshops == 0) return 0.0;
    return 100.0 * (workshops - workshops_in_work) / workshops;
}

ofstream& operator<<(ofstream& file, const KS& ks) {
    file << "��" << endl;
    file << "ID " << ks.id << endl;
    file << "��� " << ks.name << endl;
    file << "���������� ����� " << ks.workshops << endl;
    file << "���������� ����� � ������ " << ks.workshops_in_work << endl;
    file << "������� ����������������� ����� " << ks.getIdlePercentage() << "%" << endl;
    file << "������������� " << ks.eff << endl;
    return file;
}

ifstream& operator>>(ifstream& file, KS& ks) {
    string line;

    getline(file, line);
    istringstream(line.substr(line.find(' ') + 1)) >> ks.id;

    getline(file, line);
    ks.name = line.substr(line.find(' ') + 1);

    getline(file, line);
    istringstream(line.substr(17)) >> ks.workshops;

    getline(file, line);
    istringstream(line.substr(26)) >> ks.workshops_in_work;


    getline(file, line);
    string percentStr = line.substr(line.find(' ') + 1);
    percentStr.pop_back(); // ������� ������ '%'
    istringstream(percentStr) >> ks.percent_idle;

    getline(file, line);
    istringstream(line.substr(line.find(' ') + 1)) >> ks.eff;

    return file;
}


// ���������� ������� ������ ����
void searchPipeByName(const vector<Pipe>& pipes, const string& nameFilter) {
    bool found = false;
    for (const auto& pipe : pipes) {
        if (pipe.getName() == nameFilter) {
            pipe.output();
            found = true;
        }
    }
    if (!found) {
        cout << "����� � ������ \"" << nameFilter << "\" �� �������." << endl;
    }
}

void searchPipeByRepairStatus(const vector<Pipe>& pipes, bool repairStatus) {
    bool found = false;
    for (const auto& pipe : pipes) {
        if (pipe.isInRepair() == repairStatus) {
            pipe.output();
            found = true;
        }
    }
    if (!found) {
        cout << "����� � ��������� ������� \"" << (repairStatus ? "� �������" : "�� � �������") << "\" �� �������." << endl;
    }
}

void searchKSByName(const vector<KS>& kss, const string& nameFilter) {
    bool found = false;
    for (const auto& ks : kss) {
        if (ks.getName() == nameFilter) {
            ks.output();
            found = true;
        }
    }
    if (!found) {
        cout << "�� � ������ \"" << nameFilter << "\" �� �������." << endl;
    }
}

void searchKSByIdlePercentage(const vector<KS>& kss, double percentage) {
    bool found = false;
    for (const auto& ks : kss) {
        if (abs(ks.getIdlePercentage() - percentage) < 1e-6) {
            ks.output();
            found = true;
        }
    }
    if (!found) {
        cout << "�� � ��������� ����������������� ����� \"" << percentage << "\"% �� �������." << endl;
    }
}
