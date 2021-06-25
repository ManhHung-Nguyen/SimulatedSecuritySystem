#include "Decoder.h"

long long Decoder::Arguments::ToInt()
{
    long long a = 0;
    const byte* p = function_handle + position_handle[index];
    if (*p == '-') { p++; }
    while (char c = *p++)
    {
        if (c < '0' || c > '9') { break; }
        a = (a << 1) + (a << 3) + (c & 15);
    }
    return (*Handle() == '-' ? -a : a);
}
double Decoder::Arguments::ToDouble()
{
    long a = 0, b = 0;
    const byte* p = function_handle + position_handle[index];
    if (*p == '-') { p++; }
    while (char c = *p++)
    {
        if (c == '.') { b = 1; continue; }
        if (c < '0' || c > '9') { break; }
        a = (a << 1) + (a << 3) + (c & 15);
        if (b) { b = (b << 1) + (b << 3); }
    }
    if (*Handle() == '-') { a = -a; }

    return (b > 1 ? (double)a / b : a);
}

void Decoder::Decode(byte* handle) {
    Buffer::Mapping(handle);
    arguments = Arguments(handle);
    flags = 0;

    for (int i = 0; i < capacity; i++) {
        byte b = Handle()[i];
        if (b == 0) {
            return;
        }
        int r = Compile(b);
        switch (r) {
        case PARAM:
        case FUNCTION:
            arguments += (i + 1);
            break;

        case STRING:
            arguments -= (i + 1);
            break;
        }
        switch (r) {
        case FUNCTION:
        case ENDSTR:
            Handle()[i] = 0;
            break;

        case SUCCESS:
            Handle()[i] = 0;
            return;
        }
    }
}
