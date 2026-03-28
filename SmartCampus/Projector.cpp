#include "Projector.h"
#include <memory>
#include<iostream>
using namespace std;

Projector::Projector(unsigned int id,string name,string manufacturer,string inputSource,unsigned int brightnessPr)
	:Device(id,name,manufacturer),input_source(inputSource),brightnessProjector(brightnessPr){}

void Projector::Interaction_Event() {
	if (!status) {
		cout << "Device is inactive. Activate it first." << endl;
		return;
	}
	cout << "Enter projector input source HDMI|VGA|Wireless: " << endl;
	cin >> input_source;
	cout << "Enter projector preferred brightness level 0-100%:" << endl;
	cin >> brightnessProjector;
	cout << "Projector updated to input source set to " << input_source << " and brightness set to " << brightnessProjector << "%" << endl;
}

void Projector::ViewInfo() const {
	cout << "[  Projector Info:  ]" << endl;
	Device::ViewInfo();//View Info call from the device class so every device displays the default device information
	cout << "Input source: " << input_source << endl;
	cout << "Brightness level: " << brightnessProjector << "%" << endl;
	cout << endl;
}


void Projector::EditAttributes() {
	cout << "Editing device Projector" << endl;
	cout << "Enter a new device name if needed: " << endl;
	cin >> device_name;
	cout << "Enter a new manufacturer if needed: " << endl;
	cin >> manufacturer;
	cout << "Enter a new  input source HDMI|VGA|Wireless: " << endl;
	cin >> input_source;
	cout << "Enter a new  brightness level 0-100%: " << endl;
	cin >> brightnessProjector;
	cout << "New device: " << device_name << " New manufacturer: " << manufacturer 
	<< " New input Source: "<<input_source<<" New brightness level "<<brightnessProjector<<"%" << endl;
}


unique_ptr<Device> Projector::Clone(unsigned int newID, string nName) const {
	auto _copy = make_unique<Projector>(newID, nName, manufacturer, input_source,brightnessProjector);
	_copy->SetConnection(connected);
	if (status) _copy->Activate();
	return _copy;
}
