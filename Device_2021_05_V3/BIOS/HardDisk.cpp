#include "HardDisk.h"

#ifdef WIN32
#include <fstream>
HardDisk& HardDisk::Read(LPCHAR file_name, int size) {
	std::ifstream ifs;
	ifs.open(file_name);
	ifs.read((PCHAR)data, size ? size : capacity);

	ifs.close();
	return *this;
}

void HardDisk::Write(LPCHAR file_name, int offset, int size) {
	std::ofstream ofs;
	ofs.open(file_name);

	ofs.seekp(offset);
	ofs.write((LPCHAR)(data + offset), size ? size : (capacity - offset));

	ofs.close();
}

void HardDisk::Write(LPCHAR file_name, LPCHAR s) {
	std::ofstream ofs;
	ofs.open(file_name);

	ofs << s;

	ofs.close();
}

void HardDisk::Append(LPCHAR file_name, int size) {
	std::ofstream ofs;
	ofs.open(file_name, std::ios_base::app);
	ofs.write((LPCHAR)data, size ? size : capacity);

	ofs.close();
}

#endif // WIN32
