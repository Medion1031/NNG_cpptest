#include <iostream>
#include<tuple>

#include "reader.cpp"

//TODO: elkuloniteni az adatokkal valo jatekot a readertol

void start() {
    Reader r = Reader("network.mid");
    r.read();
    while(!r.end()) {
        r.next();
    }

    for(GeoData gd : r.getGeoData()) {
        std::cout << gd.getName() << "\n";
        gd.printData(gd.getEvenVector());
        gd.printData(gd.findOverlaps(gd.getEvenVector()));
    }
}

int main()
{
     // for C and C++ where synced with stdio
    start();
    return 0;
}