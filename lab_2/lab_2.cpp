#include "pipe_ks.h"
#include "logger.h"

int main() {
    Pipe newPipe;
    KS newKS;
    int command;
    Logger logger("log.txt");  // Создаем объект для логирования

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n1 - Добавить трубу\n2 - Добавить КС\n3 - Просмотр всех объектов\n4 - Редактировать трубу\n5 - Редактировать КС\n6 - Сохранить\n7 - Загрузить\n0 - Выход\n";
        cin >> command;
        logger.log("Выбрана команда: " + to_string(command));  // Логируем команду

        switch (command) {
        case 1:
            newPipe.input();
            logger.log("Добавлена труба.");
            break;
        case 2:
            newKS.input();
            logger.log("Добавлена КС.");
            break;
        case 3:
            cout << "Трубы\n";
            newPipe.output();
            cout << "КС\n";
            newKS.output();
            logger.log("Просмотр всех объектов.");
            break;
        case 4:
            newPipe.toggleRepair();
            logger.log("Изменен статус ремонта трубы.");
            break;
        case 5:
            newKS.edit();
            logger.log("Отредактирована КС.");
            break;
        case 6: {
            ofstream file("output.txt");
            if (file.is_open()) {
                file << newPipe << newKS;
                file.close();
                logger.log("Данные сохранены в output.txt.");
            }
            else {
                cout << "Не получается открыть файл" << endl;
                logger.log("Ошибка при открытии файла output.txt для сохранения.");
            }
            break;
        }
        case 7: {
            ifstream file("output.txt");
            if (file.is_open()) {
                file >> newPipe >> newKS;
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
