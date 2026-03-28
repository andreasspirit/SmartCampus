#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "Device.h"
#include<string>
#include <memory>
using namespace std;

class SecurityCamera : public Device
{

private:
	string cam_quality;
	string power_source;

public:
	//Constructor for security camera attributes and inherits from device class
	SecurityCamera(unsigned int id, string name, string manufacturer, string quality, string power);



void Interaction_Event() override;

void ViewInfo() const override;

void EditAttributes() override;

unique_ptr<Device>Clone(unsigned int newID, string nName) const override;

};



#endif