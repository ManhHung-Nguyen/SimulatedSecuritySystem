#pragma once
class MqttEngine {
public:
	void Init();
	void Connect();
	void Disconnect();
	void Subscribe();
	void Publish();
};

