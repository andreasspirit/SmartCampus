#include "AirConditioning.h"
#include <iostream>
#include <memory>

using namespace std;

AirConditioning::AirConditioning(unsigned int id,string name,string manufacturer,unsigned int temp)
	:Device(id,name,manufacturer), temperature(temp){}

void AirConditioning::Interaction_Event() {
	if (!status) {
		cout << "Device is inactive. Activate it first." << endl;
		return;
	}
cout << "Current  Air Condition temperature: " << temperature << "°C" << endl;
cout << "Set a new temperature from 15-34: ";
cin >> temperature;
cout << "The new target temperature is set to: " << temperature << "°C" << endl;

}

void AirConditioning::ViewInfo() const {

	cout << "[  Air Condition Info:  ]" << endl;
	Device::ViewInfo(); //View Info call from the device class so every device displays the default device information
	cout << "Target Temperature:" << temperature << "°C" << endl;
	cout << endl;
}

void AirConditioning::EditAttributes() {
	cout << "Editing device AirCondition" << endl;
	cout << "Enter a new device name if needed: " << endl;
	cin >> device_name;
	cout << "Enter a new manufacturer if needed: " << endl;
	cin >> manufacturer;
	cout << "Enter a new target temperature:" << endl;
	cin >> temperature;
	cout << "New device: " << device_name << " New manufacturer: " << manufacturer << " New temperature: " << temperature << endl;
}

unique_ptr<Device> AirConditioning::Clone(unsigned int newID, string nName) const {
	auto _copy = make_unique<AirConditioning>(newID, nName, manufacturer, temperature);
	_copy->SetConnection(connected);
	if (status) _copy->Activate();
	return _copy;
}