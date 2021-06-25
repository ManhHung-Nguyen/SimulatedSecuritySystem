#include "Buffer.h"

#define TOTAL_MEMORY_CAPACITY   (1 << 12)
#define STATIC_MEMORY_CAPACITY  256

//byte* Segment::it = 0;
//MemoryPage* Memory::currentPage = 0;
//
//Segment* first_segment = 0;
//Segment* last_segment = 0;
//MemoryPage* memory_page[4] = { 0, 0, 0, 0 };
//
//Segment Segment::Common = 256;
//
//Segment::Segment(int capacity)
//	: capacity(capacity)
//	, location(-1)
//	, next_segment(0) {
//
//	if (!Memory::IsReady()) {
//		if (first_segment == 0) {
//			first_segment = this;
//		}
//		else {
//			last_segment->next_segment = this;
//		}
//		last_segment = this;
//	}
//	else {
//		Relocate();
//	}
//}
//
//void Segment::Copy(const byte* source, int length) {
//	if (source == 0) { return; }
//	for (int i = 0; i < length && i < capacity; i++) {
//		*it++ = source[i];
//	}
//}
//
//void Segment::Copy(LPCHAR source) {
//	if (source == 0) { return; }
//	byte* end = Handle() + capacity - 1;
//	while (*source && it < end) {
//		*it++ = *source++;
//	}
//	*it = 0;
//}
//Memory::Memory(int size) {
//	for (int i = 0; i < 4; i++) {
//		if (memory_page[i] == 0) {
//			currentPage = memory_page[i] = new MemoryPage(size, 0);
//			break;
//		}
//	}
//	if (first_segment) {
//		first_segment->Relocate();
//		first_segment = last_segment = 0;
//	}
//}
//
//void Memory::SetPage(MemoryPage* page) {
//	if (page) {
//		currentPage = page;
//	}
//}
//
//void Memory::SetPage(int index) {
//	SetPage(memory_page[index]);
//}
//
//#pragma region class Buffer
//#pragma endregion

#define DEFAUT_BUFFER_SIZE	256
byte default_buffer_template[DEFAUT_BUFFER_SIZE];

byte* Buffer::it = 0;
Buffer::Buffer()
	: capacity(DEFAUT_BUFFER_SIZE)
	, data(default_buffer_template) {
	it = data;
}
Buffer::Buffer(int size)
	: capacity(size)
	, data(default_buffer_template) {
	it = data;
}

void Buffer::Reset(byte value) {
	for (auto& a : *this) { a = value; }
	it = data;
}

void Buffer::Copy(const byte* source, int length) {
	if (source == 0) { return; }
	for (int i = 0; i < length && i < capacity; i++) {
		*it++ = source[i];
	}
}

void Buffer::Copy(LPCHAR source) {
	if (source == 0) { return; }
	byte* end = data + capacity - 1;
	byte* s = (byte*)source;
	while (*s && it < end) {
		*it++ = *s++;
	}
	*it = 0;
}

byte default_memory[DEFAUT_BUFFER_SIZE];
Memory::Memory() 
	: Buffer(default_memory, DEFAUT_BUFFER_SIZE) {
	available = capacity;
}

Memory::Memory(int size) 
	: Buffer(new byte[size], size) 
	, available(size) {}

void Array::operator+=(void* item) {
	int v = Cast(item);
	for (int i = 0; i < (capacity >> 2); i++) {
		int a = GetAt(i);
		if (a == 0) {
			SetAt(i, v);
			return;
		}

		if (a == v) {
			return;
		}
	}
}

void Array::operator-=(void* item) {
	int v = Cast(item);
	int len = capacity >> 2;
	for (int i = 0; i < len; i++) {
		int a = GetAt(i);
		if (a == 0) {
			return;
		}

		if (a == v) {
			--len;
			while (i < len) {
				++i;
				SetAt(i - 1, GetAt(i));
			}
			SetAt(len, 0);
			return;
		}
	}

}
