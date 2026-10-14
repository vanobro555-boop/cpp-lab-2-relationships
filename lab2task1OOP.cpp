#include <iostream>
#include <string>

using namespace std;

//класс колесо
class Wheel {
private:
	string m_stamp;
	float m_diameter;
public:
	Wheel(string stamp, float diameter) : m_stamp(stamp), m_diameter(diameter) {
		cout << "Обьект успешно создан!" << endl;
	}

	void objWorking() const {
		cout << "Колесо крутится" << endl;
	}

	~Wheel() {
		cout << "Обьект удален!" << endl;
	}
};

//класс автомобиль
class Vehicle {
private:
	string m_name;
	int m_power;
	string m_id;
	//агрегация
	Wheel* obj_wheel;
public:
	Vehicle(string name, string id, int power, Wheel* wheel) : m_name(name), m_power(power), m_id(id), obj_wheel(wheel) {
		cout << "Обьект " << m_name << m_id << " создан!" << endl;
	}

	void moveVehicle() const {
		obj_wheel->objWorking();
	}

	~Vehicle() {
		cout << "Обьект удален!" << endl;
	}
};

int main(void) {
	setlocale(LC_ALL, "RU");

	int diametr = 100;
	string stamp = "belarus";
	Wheel wheel_1(stamp, diametr);

	string name = "Wolksvagen";
	int power = 90;
	string id = "AB_3523-1";
	{
		Vehicle vahicle_1(name, id, power, &wheel_1);
		vahicle_1.moveVehicle();
	}

	cout << endl;

	wheel_1.objWorking();

	return 0;
}