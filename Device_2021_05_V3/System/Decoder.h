#pragma once
#include "Compiler.h"
#include "Buffer.h"

class Decoder : Compiler, public Buffer {
public:
    class Arguments {
        byte* function_handle;
        byte* position_handle;
        byte length;
        byte index;

        long long ToInt();
        double ToDouble();
    public:
        operator int() { return (int)ToInt(); }
        operator long long() { return ToInt(); }
        operator double() { return ToDouble(); }
        operator LPCHAR () { return LPCHAR(Handle()); }
    public:
        byte* Handle() { return function_handle + position_handle[index]; }
        Arguments()
            : length(0)
            , index(-1) {
            function_handle = position_handle = 0;
        }
        Arguments(byte* function)
            : length(0)
            , index(-1) {
            function_handle = function;
            
            Buffer b;
            b.Offset(b.Capacity() - 16);
            position_handle = b.Handle();
        }
    public:
        //void Reset(byte* handle) { data = handle; capacity = 0; it = pos - 1; }
        void operator+=(int index) { position_handle[length++] = byte(index); }
        void operator-=(int index) { position_handle[length - 1] = byte(index); }
        
        Arguments& operator[](int index) { this->index = index; return *this; }
        Arguments& operator++() { ++index; return *this; }

        int Count() const { return length; }
        
    } arguments;
public:
    Decoder(int len = 64) : Buffer(len) {}
    void Decode(byte* data);
};

template <class T>
Decoder& operator>>(Decoder& dec, T& variable) {
    variable = (T)++dec.arguments;
    return dec;
}

