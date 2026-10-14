#include <iostream>
#include <string>
#include <windows.h>
#include <limits>

using namespace std;

void checkInput(int& operand, const string& prompt);

class Time {
private:
    int m_hour;
    int m_minute;
public:
    Time(int hour, int minute) : m_hour(hour), m_minute(minute) {}

    void print() const {
        cout << m_hour << ":" << m_minute;
    }

    int getHour() const {
        return m_hour;
    }
};

class Date {
private:
    int m_day;
    int m_month;
    int m_year;
    // композиция
    Time m_time;
public:
    Date(int day, int month, int year, Time time) : m_day(day), m_month(month), m_year(year), m_time(time) {}

    void print() const {
        cout << m_day << "." << m_month << "." << m_year << " в ";
        m_time.print();
    }
};

// интерфейс
class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void printDocument() const = 0;
};

class Train {
private:
    string m_trainNumber;
    string m_startStation;
    string m_endStation;
    double m_price;
public:
    // Исправлено имя параметра для избежания затенения поля класса
    Train(string train_number, string startStation, string endStation, double price)
        : m_trainNumber(train_number), m_startStation(startStation), m_endStation(endStation), m_price(price) {}

    string getEndStation() const {
        return m_endStation;
    }

    double getPrice() const {
        return m_price;
    }

    string getNumber() const {
        return m_trainNumber;
    }

    void printInfo() const {
        cout << "Поезд номер " << m_trainNumber << " с " << m_startStation << " прибудет в " << m_endStation << endl;
        cout << "Цена: " << m_price << " рублей" << endl;
    }
};

class Request {
private:
    string m_passengerName;
    string m_destination;
    Date m_desiredDate;
public:
    Request(string passengerName, string destination, Date desiredDate)
        : m_passengerName(passengerName), m_destination(destination), m_desiredDate(desiredDate) {}

    string getDestination() const {
        return m_destination;
    }

    string getPassengerName() const {
        return m_passengerName;
    }

    void printRequest() const {
        cout << "Заявка от " << m_passengerName << " до станции " << m_destination << " на ";
        m_desiredDate.print();
        cout << endl;
    }
};

// счет реализует интерфейс IPrintable
class Bill : public IPrintable {
private:
    const Request* m_request;
    const Train* m_chosenTrain;
public:
    Bill(const Request* request, const Train* chosenTrain) : m_request(request), m_chosenTrain(chosenTrain) {}

    void printDocument() const override {
        cout << "\n===ЖЕЛЕЗНОДОРОЖНЫЙ_СЧЕТ===" << endl;
        cout << "Пассажир: " << m_request->getPassengerName() << endl;
        cout << "Маршрут: до станции " << m_request->getDestination() << endl;
        cout << "Выбран поезд: номер " << m_chosenTrain->getNumber() << endl;
        cout << "К оплате: " << m_chosenTrain->getPrice() << " рублей" << endl;
    }

    ~Bill() override = default;
};

class RailwayTicketOffice {
private:
    static const int MAX_TRAINS = 10;
    Train* m_trains[MAX_TRAINS];
    int m_trainCount;

public:
    RailwayTicketOffice() : m_trainCount(0) {
        for (int i = 0; i < MAX_TRAINS; ++i) {
            m_trains[i] = nullptr;
        }
    }

    void addTrain(const string& trainNumber, const string& startStation, const string& endStation, double price) {
        if (m_trainCount < MAX_TRAINS) {
            m_trains[m_trainCount] = new Train(trainNumber, startStation, endStation, price);
            m_trainCount++;
            cout << "Поезд номер " << trainNumber << " добавлен в систему" << endl;
        }
        else {
            cout << "Достигнуто максимальное количество поездов!" << endl;
        }
    }

    void findTrainsForRequest(const Request& request) const {
        cout << "\nПоиск поездов до станции " << request.getDestination() << ":" << endl;
        bool found = false;
        for (int i = 0; i < m_trainCount; i++) {
            if (m_trains[i]->getEndStation() == request.getDestination()) {
                m_trains[i]->printInfo();
                found = true;
            }
        }
        if (!found) cout << "Поездов не найдено!" << endl;
    }

    Bill* generateBill(const Request* request, const string& trainNumber) const {
        Train* selected = nullptr;
        for (int i = 0; i < m_trainCount; i++) {
            if (m_trains[i]->getNumber() == trainNumber) {
                selected = m_trains[i];
                break;
            }
        }
        if (selected) {
            return new Bill(request, selected);
        }
        return nullptr;
    }

    ~RailwayTicketOffice() {
        for (int i = 0; i < m_trainCount; i++) {
            delete m_trains[i];
        }
    }
};

// Класс Администратора
class Admin {
private:
    string m_name;
public:
    Admin(const string& name) : m_name(name) {}

    // Администратор взаимодействует с кассой, добавляя поезда
    void addTrain(RailwayTicketOffice& office, const string& trainNumber, const string& startStation, const string& endStation, double price) const {
        cout << "\n===Администратор " << m_name << " добавляет поезд===" << endl;
        office.addTrain(trainNumber, startStation, endStation, price);
    }

    // Администратор оформляет счет на основе данных пассажира
    Bill* issueTicket(RailwayTicketOffice& office, const Request& request, const string& trainNumber) const {
        cout << "\n===Администратор " << m_name << " оформляет счет===" << endl;
        return office.generateBill(&request, trainNumber);
    }
};

// Класс Пассажира
class Passenger {
private:
    string m_name;
public:
    Passenger(const string& name) : m_name(name) {}

    // Пассажир создает заявку, вводя необходимые данные
    Request createRequest() const {
        string destination;
        int day, month, year, hour, minute;

        cout << "Станция назначения: "; cin >> destination;

        checkInput(day, "День (1-31): ");
        checkInput(month, "Месяц (1-12): ");
        checkInput(year, "Год: ");
        checkInput(hour, "Часы (0-23): ");
        checkInput(minute, "Минуты (0-59): ");

        Time travelTime(hour, minute);
        Date travelDate(day, month, year, travelTime);
        return Request(m_name, destination, travelDate);
    }

    // Пассажир ищет подходящие поезда и выбирает нужный
    string chooseTrain(RailwayTicketOffice& office, const Request& request) const {
        office.findTrainsForRequest(request);

        cout << "\nВведите номер выбранного поезда: ";
        string chosenNumber;
        cin >> chosenNumber;

        return chosenNumber;
    }

    string getName() const {
        return m_name;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    RailwayTicketOffice office;
    Admin admin("Главный администратор");

    // Администратор добавляет поезда в систему
    admin.addTrain(office, "104А", "Брест", "Минск", 40);
    admin.addTrain(office, "052Ч", "Брест", "Гродно", 25);
    admin.addTrain(office, "333Е", "Москва", "Витебск", 70);

    cout << "\n===Пассажир делает заявку===" << endl;
    string name;
    cout << "Ваше имя: "; cin >> name;

    Passenger passenger(name);
    Request myRequest = passenger.createRequest();
    myRequest.printRequest();

    // Пассажир выбирает подходящий поезд
    string chosenTrainNumber = passenger.chooseTrain(office, myRequest);

    // Администратор оформляет счет
    Bill* myBill = admin.issueTicket(office, myRequest, chosenTrainNumber);

    if (myBill != nullptr) {
        IPrintable* doc = myBill;
        doc->printDocument();
        delete myBill; // Освобождение памяти
    }
    else {
        cout << "Поезд с таким номером не найден!" << endl;
    }

    return 0;
}

void checkInput(int& operand, const string& prompt) {
    cout << prompt;
    do {
        cin >> operand;
    } while (true);
}