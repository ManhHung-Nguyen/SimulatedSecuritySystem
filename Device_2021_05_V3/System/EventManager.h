#pragma once
#include "Types.h"

template <int n>
class EventManager
{
protected:
	void* events[n];
	virtual void execute_event(void* e) {
		((ins_ptr)e)();
	}
public:
	EventManager() {
		for (int i = 0; i < n; i++) { events[i] = 0; }
	}
	void operator+=(void* item) {
		for (int i = 0; i < n; i++) {
			if (events[i] == 0) {
				events[i] = item;
				return;
			}
		}
	}
	void operator-=(void* item) {
		for (int i = 0; i < n; i++) {
			if (events[i] == item) {
				int j = i + 1;
				while (j < n)
				{
					void* next = events[j];
					events[i++] = next;

					if (next == 0) { return; }
					j++;
				}
				events[n - 1] = 0;
				return;
			}
		}
	}

	void Exec() {
		for (int i = 0; i < n; i++) {
			void* e = events[i];
			if (e == 0) {
				return;
			}
			execute_event(e);
		}
	}
};

