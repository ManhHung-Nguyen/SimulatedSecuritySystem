#include "ClientID.h"
#include "../BIOS/HardDisk.h"

char topic[40] = "response/default/ZERO-AKS-V3";
LPCHAR device_file_name = "device.bin";

ClientID::ClientID() : Builder(20) {
    Mapping((byte*)(topic + 17));
}

bool ClientID::IsEmpty() {
    return data[0] == 'Z';
}

void ClientID::GetExisting() {
    Builder temp;
    HardDisk f;

    byte& b = temp[0];

    b = 255;
    f.Mapping(temp.Handle());
    f.Read(device_file_name);

    if (b >= '0' && '9' >= b) {
        int i = temp.IndexOf(' ');
        temp[i] = 0;
        Seek(0).Copy(LPCHAR(temp.Handle()));
    }
}

void ClientID::SetValue(LPCHAR id) {
    HardDisk f;

    Seek(0).Copy(id);
    f.Mapping(data);
    f.Write(device_file_name, 0, capacity);
}

LPCHAR ClientID::GetTopic() {
	return LPCHAR(topic);
}
