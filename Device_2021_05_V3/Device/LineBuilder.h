#pragma once
#include "../System/Builder.h"
class LineBuilder : public Builder {
    byte line_index;
public:
    static byte LineWidth;
public:
    LineBuilder(int index = 0);
    LineBuilder GetNextLine() {
        LineBuilder lb = LineBuilder(line_index + 1);
        return lb;
    }
    byte LineIndex() const {
        return line_index;
    }
public:
    LineBuilder& operator()(LPCHAR s) { Seek(0).Copy(s); return *this; }

public:
    LPCHAR ToString() override;
    void Write();
    void Write(LPCHAR s) { Seek(0).Copy(s); Write(); }
};
