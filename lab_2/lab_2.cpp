#include "pipe_ks.h"
#include "logger.h"

int main() {
    vector<Pipe> pipes;  // Вектор для хранения труб
    vector<KS> kss;      // Вектор для хранения КС
    int command;
    Logger logger("log.txt");

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n1 - Добавить трубу\n2 - Добавить КС\n3 - Просмотр всех объектов\n4 - Редактировать трубу\n5 - Редактировать КС\n6 - Удалить трубу\n7 - Удалить КС\n8 - Сохранить\n9 - Загрузить\n10 - Поиск труб\n11 - Поиск КС\n0 - Выход\n";
        cin >> command;
        logger.log("Выбрана команда: " + to_string(command));

        switch (command) {
        case 1: {
            Pipe newPipe;
            newPipe.input();
            pipes.push_back(newPipe);
            logger.log("Добавлена новая труба с ID " + to_string(newPipe.getId()) + ".");
            break;
        }
        case 2: {
            KS newKS;
            newKS.input();
            kss.push_back(newKS);
            logger.log("Добавлена новая КС с ID " + to_string(newKS.getId()) + ".");
            break;
        }
        case 3: {
            for (const auto& pipe : pipes) pipe.output();
            for (const auto& ks : kss) ks.output();
            break;
        }
        case 4: {
            int id;
            cout << "Введите ID трубы для редактирования: ";
            cin >> id;
            auto it = find_if(pipes.begin(), pipes.end(), [id](const Pipe& p) { return p.getId() == id; });
            if (it != pipes.end()) {
                it->toggleRepair();
                logger.log("Изменён статус ремонта трубы с ID " + to_string(id) + ".");
            }
            else {
                cout << "Труба с таким ID не найдена." << endl;
                logger.log("Ошибка: неверный ID трубы.");
            }
            break;
        }
        case 5: {
            int id;
            cout << "Введите ID КС для редактирования: ";
            cin >> id;
            auto it = find_if(kss.begin(), kss.end(), [id](const KS& ks) { return ks.getId() == id; });
            if (it != kss.end()) {
                it->edit();
                logger.log("Изменена КС с ID " + to_string(id) + ".");
            }
            else {
                cout << "КС с таким ID не найдена." << endl;
                logger.log("Ошибка: неверный ID КС.");
            }
            break;
        }
        case 6: {
            int id;
            cout << "Введите ID трубы для удаления: ";
            cin >> id;
            auto it = remove_if(pipes.begin(), pipes.end(), [id](const Pipe& p) { return p.getId() == id; });
            if (it != pipes.end()) {
                pipes.erase(it, pipes.end());
                logger.log("Удалена труба с ID " + to_string(id) + ".");
            }
            else {
                cout << "Труба с таким ID не найдена." << endl;
                logger.log("Ошибка: неверный ID трубы.");
            }
            break;
        }
        case 7: {
            int id;
            cout << "Введите ID КС для удаления: ";
            cin >> id;
            auto it = remove_if(kss.begin(), kss.end(), [id](const KS& ks) { return ks.getId() == id; });
            if (it != kss.end()) {
                kss.erase(it, kss.end());
                logger.log("Удалена КС с ID " + to_string(id) + ".");
            }
            else {
                cout << "КС с таким ID не найдена." << endl;
                logger.log("Ошибка: неверный ID КС.");
            }
            break;
        }
        case 8: {
            ofstream file("data.txt");
            for (const auto& pipe : pipes) file << pipe;
            for (const auto& ks : kss) file << ks;
            file.close();
            logger.log("Данные сохранены.");
            break;
        }
        case 9: {
            ifstream file("data.txt");
            pipes.clear();
            kss.clear();
            while (!file.eof()) {
                string type;
                getline(file, type);
                if (type == "Труба") {
                    Pipe pipe;
                    file >> pipe;
                    pipes.push_back(pipe);
                }
                else if (type == "КС") {
                    KS ks;
                    file >> ks;
                    kss.push_back(ks);
                }
            }
            file.close();
            logger.log("Данные загружены.");
            break;
        }
        case 10: {
            cout << "Выберите фильтр для поиска:\n1 - По названию\n2 - По признаку \"в ремонте\"\n";
            int searchCommand;
            cin >> searchCommand;

            if (searchCommand == 1) {
                string nameFilter;
                cout << "Введите название трубы: ";
                cin.ignore();
                getline(cin, nameFilter);
                searchPipeByName(pipes, nameFilter);
            }
            else if (searchCommand == 2) {
                bool repairStatus;
                cout << "Введите 1 для поиска труб в ремонте или 0 для не в ремонте: ";
                cin >> repairStatus;
                searchPipeByRepairStatus(pipes, repairStatus);
            }
            else {
                cout << "Неверный выбор фильтра." << endl;
            }
            break;
        }
        case 11: {
            cout << "Выберите фильтр для поиска:\n1 - По названию\n2 - По проценту незадействованных цехов\n";
            int searchCommand;
            cin >> searchCommand;

            if (searchCommand == 1) {
                string nameFilter;
                cout << "Введите название КС: ";
                cin.ignore();
                getline(cin, nameFilter);
                searchKSByName(kss, nameFilter);
            }
            else if (searchCommand == 2) {
                double percentage;
                cout << "Введите процент незадействованных цехов (например, 20.0): ";
                cin >> percentage;
                searchKSByIdlePercentage(kss, percentage);
            }
            else {
                cout << "Неверный выбор фильтра." << endl;
            }
            break;
        }
        case 0:
            logger.log("Завершение работы программы.");
            return 0;
        default:
            cout << "Неверная команда" << endl;
            logger.log("Ошибка: неверная команда.");
        }
    }
}
