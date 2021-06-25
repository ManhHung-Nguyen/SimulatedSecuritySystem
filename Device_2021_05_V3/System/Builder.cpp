//
//  Builder.cpp
//  CBuffer
//
//  Created by Vu Song Tung on 5/19/21.
//  Copyright © 2021 Vu Song Tung. All rights reserved.
//

#include "Builder.h"

int Builder::IndexOf(byte c, int startIndex) const {
	int i = startIndex;
	while (i < capacity) {
		if (data[i] == c) { return i; }
		i++;
	}
	return -1;
}
int Builder::IndexOf(LPCHAR s, int startIndex) const {
	int i = startIndex;

	while (i < capacity) {
		LPCHAR p1 = (LPCHAR)(Handle() + i);
		LPCHAR p2 = s;

		char c = 0;
		while (*p1 && *p2) {
			if (c = *p1 - *p2) { break; }

			p1++; p2++;
		}
		if (c == 0) {
			return i;
		}

		i++;
	}
	return -1;
}

Builder& Builder::ToUpper() {
	byte* p = Handle();
	while (p < it) {
		byte c = *p;
		if (c >= 'a' && 'z' >= c) { *p = c - 32; }

		p++;
	}
	return *this;
}

Builder& Builder::ToLower() {
	byte* p = Handle();
	while (p < it) {
		byte c = *p;
		if (c >= 'A' && 'Z' >= c) { *p = c + 32; }

		p++;
	}
	return *this;
}

void Builder::CopyTo(byte* dst) {
	Builder b(capacity);
	b.Mapping(dst).Copy(LPCHAR(data));
}

int Builder::Compare(LPCHAR s1, LPCHAR s2)
{
	while (*s1 || *s2) {
		int c = (*s1++ - *s2++);
		if (c)
		{
			return c;
		}
	}
	return 0;
}

char time_builder_template[20] = "0000-00-00T00:00:00";
TimeBuilder::TimeBuilder() : Builder(20) {
	data = (byte*)time_builder_template;
}

void TimeBuilder::set_value(int value, int pos) {

	int len = 4;
	it = data;

	if (pos) {
		len = 2;
		it += (pos << 1) + pos + 2;
	}
	it += len - 1;

	while (value) {
		*it-- = (value % 10) | '0';
		len--;
		value /= 10;
	}
	while (len--) {
		*it-- = '0';
	}
}
