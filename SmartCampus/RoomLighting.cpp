#include"RoomLighting.h"
#include <iostream>
#include<memory>

RoomLighting::RoomLighting(unsigned int id,string name,string manufacturer,unsigned int brightness_level)
	:Device(id,name,manufacturer), brightness(brightness_level){}

void RoomLighting::Interaction_Event() {
	if (!status) {
		cout << "Device is inactive. Activate it first." << endl;
		return;
	}
	cout << "Set brightness level 0-100%" << endl;
	cin >> brightness;
	cout << "Brightness is set to: " << brightness << "%" << endl;
}


void RoomLighting::ViewInfo() const {

	cout << "[  Room Lighting Info:  ]" << endl;
	Device::ViewInfo();  //View Info call from the device class so every device displays the default device information
	cout << "Brightness :" << brightness << "%" << endl;
	cout << endl;
}

void RoomLighting::EditAttributes() {
	cout << "Editing device RoomLighting" << endl;
	cout << "Enter a new device name if needed: " << endl;
	cin >> device_name;
	cout << "Enter a new manufacturer if needed: " << endl;
	cin >> manufacturer;
	cout << "Enter a new brightness 0-100%:" << endl;
	cin >> brightness;
	cout << "New device: " << device_name << " New manufacturer: " << manufacturer << " New brightness: "<<brightness<<"%" << endl;
}

unique_ptr<Device> RoomLighting::Clone(unsigned int newID, string nName) const {
	auto _copy = make_unique<RoomLighting>(newID, nName, manufacturer, brightness);
	_copy->SetConnection(connected);
	if (status) _copy->Activate();
	return _copy;
}
