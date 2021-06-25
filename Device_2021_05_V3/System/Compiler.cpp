#include "Compiler.h"

/// <summary>
/// Phân loại một byte trong đoạn code
/// </summary>
/// <param name="b">byte cần phân loại</param>
/// <returns>Trạng thái</returns>
int Compiler::Compile(byte b) {
    if (Has(STRING)) {
        if (b == '\"') {
            Invert(STRING);
            return ENDSTR;
        }
        return NONE;
    }
    if (Has(JOBJECT)) {
        if (b == '}') {
            Invert(JOBJECT);
        }
        return NONE;
    }
    if (Has(JLIST)) {
        if (b == ']') {
            Invert(JLIST);
        }
        return NONE;
    }
    switch (b) {
    case ')': return Has(FUNCTION) ? SUCCESS : ERR;
    case '(': return Set(FUNCTION);
    case '\"': return Set(STRING);
    case '{': return Set(JOBJECT);
    case '[': return Set(JLIST);
    case ',': return PARAM;
    }
    return NONE;
}

