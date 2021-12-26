#include <iostream>

#include "reader.cpp"

//TODO: elkuloniteni az adatokkal valo jatekot a readertol

int main()
{
    Reader r = Reader("network.mid");
    r.first();
    return 0;
}
