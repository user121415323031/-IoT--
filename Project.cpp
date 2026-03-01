#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Генерация данных датчика температуры
int generateSensorData() {
    return 15 + rand() % 21;
}

// XOR-шифрование
string encryptDecrypt(string data, char key) {
    for (size_t i = 0; i < data.length(); i++) {
        data[i] = data[i] ^ key;
    }
    return data;
}

// Контроль целостности
int calculateChecksum(string data) {
    int checksum = 0;
    for (size_t i = 0; i < data.length(); i++) {
        checksum += (int)data[i];
    }
    return checksum;
}

// Небезопасная передача
void insecureTransmission() {
    int sensorData = generateSensorData();
    string message = "Temperature=" + to_string(sensorData);

    cout << "[НЕБЕЗОПАСНАЯ ПЕРЕДАЧА]\n";
    cout << "IoT-устройство передало: " << message << endl;
    cout << "[Злоумышленник перехватил]: " << message << endl;
    cout << "[Сервер получил]: " << message << endl;
}

// Защищённая передача
void secureTransmission() {
    int sensorData = generateSensorData();
    string message = "Temperature=" + to_string(sensorData);

    char key;
    cout << "Введите ключ (1 символ): ";
    cin >> key;

    int checksumBefore = calculateChecksum(message);
    string encrypted = encryptDecrypt(message, key);

    cout << "[ЗАЩИЩЕННАЯ ПЕРЕДАЧА]" << endl;
    cout << "Зашифрованные данные: " << encrypted << endl;
    cout << "[Злоумышленник видит]: " << encrypted << endl;

    string decrypted = encryptDecrypt(encrypted, key);
    int checksumAfter = calculateChecksum(decrypted);

    cout << "[Сервер расшифровал]: " << decrypted << endl;

    if (checksumBefore == checksumAfter) {
        cout << "Целостность данных сохранена" << endl;
    }
    else {
        cout << "Целостность данных нарушена" << endl;
    }
}

// Главное меню
int main() {
    setlocale(LC_ALL, "RU"); 
    srand((unsigned)time(0));
    int choice;

    do {
        cout << "=== МОДЕЛЬ IoT-СИСТЕМЫ ===" << endl;
        cout << "1. Небезопасная передача" << endl;
        cout << "2. Защищённая передача" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            insecureTransmission();
            break;
        case 2:
            secureTransmission();
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный ввод.\n";
        }
    } while (choice != 0);

    return 0;
}
