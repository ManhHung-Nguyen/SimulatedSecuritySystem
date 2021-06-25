#include "Config.h"
#include "../System/System.h"
#include "../BIOS/BIOS.h"

LPCHAR config_file_name = "config.bin";
Memory config_data = 256;

byte* ConfigManager::GetBuffer(int size) {
	return config_data.Malloc(size);
}

void ConfigManager::Save() {
	HardDisk fs(config_data.Capacity());
	fs.Mapping(config_data.Handle());
	fs.Write(config_file_name);

}

void ConfigManager::Load()
{
	config_data.Reset(255);
	HardDisk fs(config_data.Capacity());
	fs.Mapping(config_data.Handle());
	fs.Read(config_file_name);
}