
#include "Simulator.h"


int get_milisecond_circle() {
	Sleep(1);
	return 1;
}

#define _mem(n) file_buffer.Malloc(n), n

LPCHAR simulation_path = "d:\\test\\";
Memory file_buffer = 1024;
Builder file_name_buider(64);
Builder old_command(128);

class FileStream : public HardDisk {
public:
	FileStream()
		: HardDisk(128) {
		file_buffer.Reset();
		file_buffer.Malloc(file_name_buider);
		file_buffer.Malloc(old_command);
		file_buffer.Malloc(*this);
	}
public:
} fs;

LPCHAR Simulator::bin_path(LPCHAR name)
{
	file_name_buider = simulation_path;
	return file_name_buider << name << ".bin";
}

byte* Simulator::Read(LPCHAR name, int size)
{
	*fs.Seekp(0) = 0;
	return File(name).Read(file_name_buider, size).Handle();
}

void Simulator::Write(LPCHAR name, LPCHAR content)
{
	File(name) << content;
	fs.Write(file_name_buider, LPCHAR(fs.Handle()));
}

HardDisk& Simulator::File(LPCHAR name)
{
	bin_path(name);
	fs.Seek(0);

	return fs;
}

bool Simulator::Receive() {
	Read("system", fs.Capacity());
	byte* p = fs.Handle();

	if (p[0] == 0) return false;
	if (Builder::Compare(old_command, LPCHAR(p))) {
		if (p[0] == '{') {
			int i = fs.IndexOf("Value");
			if (i > 0) {
				p += i + 8;
			}
		}

		System::EU.Fetch(p);
		System::EU.Execute();

		return true;
	}
	return false;
}

void Simulator::Send(LPCHAR action, LPCHAR value, LPCHAR id) {
	ObjectBuilder js;
	js << "action" << action;
	if (value) {
		js << "value" << value;
	}
	if (id) {
		js << "deviceId" << id;
	}
	Write("device", js);
}

//void Internet::connect() {
//	byte v = *Simulator::Read("internet", 1);
//	if (v == 1) {
//		Simulator::Write("connect", System::Device.GetClientId());
//	}
//}
//
//void Internet::send(LPCHAR text) {
//}
//
//void Device::request_id() {
//	ObjectBuilder js;
//	js() << "url" << "manage/deviceid";
//
//	Simulator::Write("publish", js);
//}
//
//void Device::request_time() {
//	ObjectBuilder js;
//	js() << "url" << "manage/time";
//
//	Simulator::Write("publish", js);
//}
//
//#include "EU.h"
//class Subscriber : Counter {
//public:
//	Subscriber() {
//		max_value = current_value = MILISECOND_LIMIT / 2;
//	}
//protected:
//	bool is_running() override { return true; }
//	void on_tick() override {
//		byte* text = Simulator::Read("subscribe");
//		if (*text) {
//			System::Device.AnalyseMessage(text);
//			Simulator::Write("subscribe", "");
//		}
//	}
//};
//void Device::start_listener() {
//	new Subscriber();
//}
//
//
//#include "States.h"
//extern void write_led(int r, int c, int v);
//void States::on_value_changed(int bit) {
//	write_led(bit, 0, data[bit]);
//}
