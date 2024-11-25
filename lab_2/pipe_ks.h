#ifndef PIPE_KS_H
#define PIPE_KS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ��������� ������� ��� �������� �����
template <typename T>
void check_input(T& x, const string& prompt);

// ����� Pipe
class Pipe {
private:
    static int nextId;
    int id;
    string kilometr;
    int length;
    int diametr;
    bool repair;

public:
    Pipe();
    void input();
    void output() const;
    void toggleRepair();

    string getName() const { return kilometr; }
    bool isInRepair() const { return repair; }
    int getId() const { return id; }

    friend ofstream& operator<<(ofstream& file, const Pipe& p);
    friend ifstream& operator>>(ifstream& file, Pipe& p);
};

// ����� KS
class KS {
private:
    static int nextId;
    int id;
    string name;
    int workshops;
    int workshops_in_work;
    double eff;

public:
    KS();
    void input();
    void output() const;
    void edit();

    string getName() const { return name; }
    int getId() const { return id; }

    friend ofstream& operator<<(ofstream& file, const KS& ks);
    friend ifstream& operator>>(ifstream& file, KS& ks);
};

#endif
