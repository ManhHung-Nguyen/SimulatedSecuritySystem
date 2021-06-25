#include "Counter.h"
#include "System.h"

Counter::Counter() { 
	duration = value = 0; 
	System::Clock += this;
}

Counter::~Counter() {
	System::Clock -= this;
}
