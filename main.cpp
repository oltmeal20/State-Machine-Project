#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int setTime = 0;

class MobileClockState;
class ClockStateContext;
class StandardTime;
class SavingTime;

class MobileClockState {
public:
	virtual void clock(ClockStateContext* ctx) = 0;
	virtual void clockSet() = 0;

	virtual ~MobileClockState() {}
};

class SavingTime : public MobileClockState {
public:
	void clock(ClockStateContext* ctx) {
		setTime++;
		if (setTime >= 13) {
			setTime = 1;
		}
		else if (setTime <= 0) {
			setTime = 12;
		}
		cout << setTime << ":00" << endl;
	}
	void clockSet() {
		cout << "Set to Daylight Saving Time\n";
		cout << "(Moveing clock ahead 1 hour)\n";
	}
};

class StandardTime : public MobileClockState {
public:
	void clock(ClockStateContext* ctx) {
		setTime++;
		if (setTime >= 13) {
			setTime = 1;
		}
		else if (setTime <= 0) {
			setTime = 12;
		}
		cout << setTime << ":00" << endl;
	}
	void clockSet() {
		setTime -= 2;
		cout << "Set to Standard Time\n";
		cout << "(Moveing clock back 1 hour)\n";
	}
};

class ClockStateContext {
private:
	MobileClockState* currentState;

public:
	ClockStateContext(MobileClockState* state) {
		currentState = state;
	}

	void setState(MobileClockState* state) {
		currentState = state;
	}

	MobileClockState* getState() {
		return currentState;
	}

	void clock() {
		currentState->clock(this);
	}
};

int main() {
	MobileClockState* standard = new StandardTime;
	ClockStateContext* stateContext = new ClockStateContext(standard);
	stateContext->getState()->clockSet();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	MobileClockState* saving = new SavingTime;
	stateContext->setState(saving);
	stateContext->getState()->clockSet();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	stateContext->setState(standard);
	stateContext->getState()->clockSet();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	delete standard;
	stateContext->setState(saving);
	stateContext->getState()->clockSet();
	stateContext->clock();
	stateContext->clock();
	stateContext->clock();
	delete saving;
}
