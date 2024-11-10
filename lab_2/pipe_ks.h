#ifndef PIPE_KS_H
#define PIPE_KS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Вспомогательные функции для проверки ввода
void check_int(int& x);
void check_bool(bool& x);
void check_double(double& x);

// Класс Pipe
class Pipe {
private:
    string kilometr;
    int length;
    int diametr;
    bool repair;

public:
    Pipe();
    void input();
    void output() const;
    void toggleRepair();

    friend ofstream& operator<<(ofstream& file, const Pipe& p);
    friend ifstream& operator>>(ifstream& file, Pipe& p);
};

// Класс KS
class KS {
private:
    string name;
    int workshops;
    int workshops_in_work;
    double eff;

public:
    KS();
    void input();
    void output() const;
    void edit();

    friend ofstream& operator<<(ofstream& file, const KS& ks);
    friend ifstream& operator>>(ifstream& file, KS& ks);
};

#endif
