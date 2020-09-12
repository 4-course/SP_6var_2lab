#pragma once
enum modeType {
	cold, warm
};
class Conditioner {
	private:
	bool isTurnOn;
	bool isWorking;
	int time;
	modeType mode;
	public:
	Conditioner ();
	void changeWork();
	void changePower ();
	void changeMode ();
	int getTime();
	bool isWorkingNow();
	bool isTurnedOn();
	bool isColdMode();
	~Conditioner ();
};

