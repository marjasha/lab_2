#ifndef PIPE_KS_H
#define PIPE_KS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Шаблонная функция для проверки ввода
template <typename T>
void check_input(T& x, const string& prompt);

// Класс Pipe
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
    int getId() const { return id; }

    friend ofstream& operator<<(ofstream& file, const Pipe& p);
    friend ifstream& operator>>(ifstream& file, Pipe& p);
};

// Класс KS
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
    int getId() const { return id; }

    friend ofstream& operator<<(ofstream& file, const KS& ks);
    friend ifstream& operator>>(ifstream& file, KS& ks);
};

#endif

