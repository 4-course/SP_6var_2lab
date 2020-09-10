#pragma once
enum modeType {
	cold, warm
};
class Conditioner {
	private:
	bool isTurnOn;
	bool isWorking;
	modeType mode;
	public:
	Conditioner ();
	void changeWork();
	void changePower ();
	void changeMode ();
	~Conditioner ();
};

