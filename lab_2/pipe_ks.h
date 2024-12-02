#ifndef PIPE_KS_H
#define PIPE_KS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath> 

using namespace std;

// Шаблонная функция для проверки ввода
template <typename T>
void check_input(T& x, const string& prompt);


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

// Класс KS
class KS {
private:
    static int nextId;
    int id;
    string name;
    int workshops;
    int workshops_in_work;
    double eff;
    int percent_idle;

public:
    KS();
    void input();
    void output() const;
    void edit();
    double getIdlePercentage() const;

    string getName() const { return name; }
    int getId() const { return id; }

    friend ofstream& operator<<(ofstream& file, const KS& ks);
    friend ifstream& operator>>(ifstream& file, KS& ks);
};

// Функции для поиска
void searchPipeByName(const vector<Pipe>& pipes, const string& nameFilter);
void searchPipeByRepairStatus(const vector<Pipe>& pipes, bool repairStatus);
void searchKSByName(const vector<KS>& kss, const string& nameFilter);
void searchKSByIdlePercentage(const vector<KS>& kss, double percentage);

#endif
