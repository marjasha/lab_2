#include "pipe_ks.h"

int main() {
    Pipe newPipe;
    KS newKS;
    int command;

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n1 - Добавить трубу\n2 - Добавить КС\n3 - Просмотр всех объектов\n4 - Редактировать трубу\n5 - Редактировать КС\n6 - Сохранить\n7 - Загрузить\n0 - Выход\n";
        cin >> command;

        switch (command) {
        case 1:
            newPipe.input();
            break;
        case 2:
            newKS.input();
            break;
        case 3:
            cout << "Трубы\n";
            newPipe.output();
            cout << "КС\n";
            newKS.output();
            break;
        case 4:
            newPipe.toggleRepair();
            break;
        case 5:
            newKS.edit();
            break;
        case 6: {
            ofstream file("output.txt");
            if (file.is_open()) {
                file << newPipe << newKS;
                file.close();
            }
            else {
                cout << "Не удалось открыть файл для сохранения" << endl;
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
                cout << "Не удалось открыть файл для загрузки" << endl;
            }
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Неверная команда!" << endl;
        }
    }
}
