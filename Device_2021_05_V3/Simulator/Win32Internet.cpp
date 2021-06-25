#include "../Device/Internet.h"
#include "../Device/Device.h"
#include "../System/Builder.h"
#include "Simulator.h"

byte publish_message[64];

class InternetListener : public Counter {
protected:
	void on_tick() override {
		Simulator::Receive();
	}
public:
	
} internet_listener;

void Internet::on_reveived(LPCHAR content) {

}

void Internet::start_listener() {
	Simulator::Send("subscribe", Device::CLIENT_ID.GetTopic());
	internet_listener.Reset(MILISECOND_LIMIT / 10);
}

bool Internet::is_connected() {
	if (Simulator::Receive()) {
		return int(_args[0]) == 1;
	}
	return false;
}

void Internet::Connect() {
	Simulator::Send("connect", 0, Device::CLIENT_ID);
}

void Internet::Send(LPCHAR content) {
	Builder b(64);
	b.Mapping(publish_message);
	b.Copy(content);

	ObjectBuilder js;
	js << "action" << "publish";
	js.SetValue("value", b);

	Simulator::Write("device", js);
}
