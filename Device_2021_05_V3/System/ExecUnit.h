#pragma once
#include "BTree.h"
#include "Decoder.h"
#include "Builder.h"
#include "Types.h"

class ExecUnit : public BSTree
{
public:
    static void Call(ins_ptr proc) {
        if (proc) proc();
    }
protected:
    Decoder decoder;
public:
    ExecUnit() : BSTree("NOP", 0) {
    }
public:
	void Fetch(byte* func) {
		decoder.Decode(func);
	}
	void Fetch(LPCHAR text);
	void Execute();

	Decoder::Arguments& Args() { return decoder.arguments; }

public:
	template <class T>
	friend ExecUnit& operator>>(ExecUnit& e, T& variable) {
		e.decoder >> variable;
		return e;
	}
};
