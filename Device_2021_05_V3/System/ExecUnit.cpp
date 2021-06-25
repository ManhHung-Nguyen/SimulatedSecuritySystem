#include "ExecUnit.h"
#include "Builder.h"

void ExecUnit::Fetch(LPCHAR text) {
    FunctionBuilder fb;
    fb.Copy(text);

    decoder.Decode(fb.Handle());
}

void ExecUnit::Execute() {
    Call((ins_ptr)BSTree::Find(LPCHAR(decoder.Handle())));
}
