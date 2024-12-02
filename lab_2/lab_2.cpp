#include "pipe_ks.h"
#include "logger.h"

int main() {
    vector<Pipe> pipes;  // Вектор для хранения труб
    vector<KS> kss;      // Вектор для хранения КС
    int command;
    Logger logger("log.txt");

    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введите:\n"
            << "1 - Добавить трубу\n"
            << "2 - Добавить КС\n"
            << "3 - Просмотр всех объектов\n"
            << "4 - Редактировать трубу\n"
            << "5 - Редактировать КС\n"
            << "6 - Удалить трубу\n"
            << "7 - Удалить КС\n"
            << "8 - Сохранить\n"
            << "9 - Загрузить\n"
            << "10 - Поиск труб\n"
            << "11 - Поиск КС\n"
            << "12 - Пакетное редактирование труб\n"
            << "0 - Выход\n";

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
        case 8: { // Сохранение данных
            string filename;
            cout << "Введите имя файла для сохранения данных (например, data.txt): ";
            cin >> filename;

            ifstream checkFile(filename);
            if (checkFile.is_open()) {
                cout << "Файл " << filename << " уже существует. Перезаписать его? (1 - Да, 0 - Нет): ";
                int choice;
                cin >> choice;
                if (choice != 1) {
                    cout << "Сохранение отменено." << endl;
                    logger.log("Сохранение в файл " + filename + " отменено пользователем.");
                    break;
                }
            }
            checkFile.close();

            ofstream file(filename);
            if (file.is_open()) {
                for (const auto& pipe : pipes) file << pipe;
                for (const auto& ks : kss) file << ks;
                file.close();
                cout << "Данные успешно сохранены в файл " << filename << "." << endl;
                logger.log("Данные сохранены в файл: " + filename);
            }
            else {
                cout << "Ошибка: не удалось открыть файл " << filename << " для записи." << endl;
                logger.log("Ошибка при сохранении данных в файл: " + filename);
            }
            break;
        }
        case 9: {
            string filename;
            cout << "Введите имя файла для загрузки данных (например, data.txt): ";
            cin >> filename;

            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Ошибка: не удалось открыть файл " << filename << " для чтения." << endl;
                logger.log("Ошибка при загрузке данных из файла: " + filename);
                break;
            }

            while (file) {
                string line;
                getline(file, line);
                if (line == "Труба") {
                    Pipe newPipe;
                    file >> newPipe;
                    pipes.push_back(newPipe);
                    logger.log("Загружена труба с ID " + to_string(newPipe.getId()) + ".");
                }
                else if (line == "КС") {
                    KS newKS;
                    file >> newKS;
                    kss.push_back(newKS);
                    logger.log("Загружена КС с ID " + to_string(newKS.getId()) + ".");
                }
            }

            file.close();
            cout << "Данные успешно загружены из файла " << filename << "." << endl;
            logger.log("Данные успешно загружены из файла: " + filename);
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
        case 12: { // Пакетное редактирование труб
            cout << "Выберите вариант пакетного редактирования:\n1 - Изменить статус всех труб\n2 - Изменить статус определённой трубы\n";
            int batchCommand;
            cin >> batchCommand;

            if (batchCommand == 1) { // Редактировать все трубы
                for (auto& pipe : pipes) {
                    pipe.toggleRepair();
                }
                cout << "Статус всех труб успешно изменён." << endl;
                logger.log("Статус всех труб изменён.");
            }
            else if (batchCommand == 2) { // Редактировать одну трубу по ID
                int id;
                cout << "Введите ID трубы для изменения статуса: ";
                cin >> id;
                auto it = find_if(pipes.begin(), pipes.end(), [id](const Pipe& p) { return p.getId() == id; });
                if (it != pipes.end()) {
                    it->toggleRepair();
                    cout << "Статус трубы с ID " << id << " успешно изменён." << endl;
                    logger.log("Статус трубы с ID " + to_string(id) + " изменён.");
                }
                else {
                    cout << "Труба с таким ID не найдена." << endl;
                    logger.log("Ошибка: неверный ID трубы.");
                }
            }
            else {
                cout << "Неверный выбор опции." << endl;
                logger.log("Ошибка: неверный выбор опции пакетного редактирования.");
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
