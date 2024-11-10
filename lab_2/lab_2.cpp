#include "pipe_ks.h"
#include "logger.h"
#include <vector>

int main() {
    vector<Pipe> pipes;  // Вектор для хранения труб
    vector<KS> kss;      // Вектор для хранения КС
    int command;
    Logger logger("log.txt");

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n1 - Добавить трубу\n2 - Добавить КС\n3 - Просмотр всех объектов\n4 - Редактировать трубу\n5 - Редактировать КС\n6 - Удалить трубу\n7 - Удалить КС\n8 - Сохранить\n9 - Загрузить\n0 - Выход\n";
        cin >> command;
        logger.log("Выбрана команда: " + to_string(command));

        switch (command) {
        case 1: {
            Pipe newPipe;
            newPipe.input();
            pipes.push_back(newPipe);  // Добавляем новую трубу в вектор
            logger.log("Добавлена новая труба.");
            break;
        }
        case 2: {
            KS newKS;
            newKS.input();
            kss.push_back(newKS);  // Добавляем новую КС в вектор
            logger.log("Добавлена новая КС.");
            break;
        }
        case 3:
            cout << "Трубы:\n";
            for (size_t i = 0; i < pipes.size(); ++i) {
                cout << "Труба " << i + 1 << ":\n";
                pipes[i].output();
            }
            cout << "\nКС:\n";
            for (size_t i = 0; i < kss.size(); ++i) {
                cout << "КС " << i + 1 << ":\n";
                kss[i].output();
            }
            logger.log("Просмотр всех объектов.");
            break;
        case 4: {
            int pipeIndex;
            cout << "Введите номер трубы для редактирования: ";
            cin >> pipeIndex;
            if (pipeIndex > 0 && pipeIndex <= pipes.size()) {
                pipes[pipeIndex - 1].toggleRepair();
                logger.log("Изменен статус ремонта трубы " + to_string(pipeIndex) + ".");
            }
            else {
                cout << "Неверный номер трубы." << endl;
                logger.log("Ошибка: неверный номер трубы для редактирования.");
            }
            break;
        }
        case 5: {
            int ksIndex;
            cout << "Введите номер КС для редактирования: ";
            cin >> ksIndex;
            if (ksIndex > 0 && ksIndex <= kss.size()) {
                kss[ksIndex - 1].edit();
                logger.log("Отредактирована КС " + to_string(ksIndex) + ".");
            }
            else {
                cout << "Неверный номер КС." << endl;
                logger.log("Ошибка: неверный номер КС для редактирования.");
            }
            break;
        }
        case 6: {
            int pipeIndex;
            cout << "Введите номер трубы для удаления: ";
            cin >> pipeIndex;
            if (pipeIndex > 0 && pipeIndex <= pipes.size()) {
                pipes.erase(pipes.begin() + pipeIndex - 1);
                logger.log("Удалена труба " + to_string(pipeIndex) + ".");
            }
            else {
                cout << "Неверный номер трубы." << endl;
                logger.log("Ошибка: неверный номер трубы для удаления.");
            }
            break;
        }
        case 7: {
            int ksIndex;
            cout << "Введите номер КС для удаления: ";
            cin >> ksIndex;
            if (ksIndex > 0 && ksIndex <= kss.size()) {
                kss.erase(kss.begin() + ksIndex - 1);
                logger.log("Удалена КС " + to_string(ksIndex) + ".");
            }
            else {
                cout << "Неверный номер КС." << endl;
                logger.log("Ошибка: неверный номер КС для удаления.");
            }
            break;
        }
        case 8: {
            ofstream file("output.txt");
            if (file.is_open()) {
                for (const auto& pipe : pipes) {
                    file << pipe;
                }
                for (const auto& ks : kss) {
                    file << ks;
                }
                file.close();
                logger.log("Данные сохранены в output.txt.");
            }
            else {
                cout << "Не получается открыть файл" << endl;
                logger.log("Ошибка при открытии файла output.txt для сохранения.");
            }
            break;
        }
        case 9: {
            ifstream file("output.txt");
            if (file.is_open()) {
                pipes.clear();
                kss.clear();
                Pipe tempPipe;
                KS tempKS;
                while (file >> tempPipe) {
                    pipes.push_back(tempPipe);
                }
                while (file >> tempKS) {
                    kss.push_back(tempKS);
                }
                file.close();
                logger.log("Данные загружены из output.txt.");
            }
            else {
                cout << "Не получается открыть файл" << endl;
                logger.log("Ошибка при открытии файла output.txt для загрузки.");
            }
            break;
        }
        case 0:
            logger.log("Завершение программы.");
            return 0;
        default:
            cout << "Неверная команда!" << endl;
            logger.log("Введена неверная команда.");
        }
    }
}

