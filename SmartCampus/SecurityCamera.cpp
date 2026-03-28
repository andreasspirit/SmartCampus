#include "SecurityCamera.h"
#include <iostream>
#include <memory>
using namespace std;

SecurityCamera::SecurityCamera(unsigned int id, string name, string manufacturer, string quality, string power)
    : Device(id, name, manufacturer), cam_quality(quality), power_source(power) {}

void SecurityCamera::Interaction_Event() {
    if (!status) {
        cout << "ERROR: Device is not active. Camera must be activated first!\n";
        return;
    }
    
        cout << "Now viewing camera:" << device_name << endl;
    
}


//information for security camera
void SecurityCamera::ViewInfo() const {

    cout << "[  Security Camera Info  ]"<<endl;
    Device::ViewInfo();//View Info call from the device class so every device displays the default device information
    cout << "Camera Quality:" << cam_quality << endl;
    cout << "Power Souce:" << power_source << endl;
    cout << endl;

}


//Edit Attributes of Security Camera
void SecurityCamera::EditAttributes()
{
    
    cout << "Enter new device name: ";
    cin>>device_name;

    cout << "Enter new manufacturer: ";
    cin>>manufacturer;

    cout << "Enter new input camera resolution 4K|1080p|720p : ";
    cin >> cam_quality;

    cout << "Enter new power supply Battery|Wireless|Solar Battery : ";
    cin >> power_source;

    cout << "New device name: " << device_name << " New manufacturer: " << manufacturer << "  New camera quality: " << cam_quality << " New power supply: "
        << power_source << endl;
}


unique_ptr<Device> SecurityCamera::Clone(unsigned int newID, string nName) const {
    auto _copy = make_unique<SecurityCamera>(newID, nName, manufacturer, cam_quality,power_source);
    _copy->SetConnection(connected);
    if (status) _copy->Activate();
    return _copy;
}
