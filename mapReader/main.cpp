#include <iostream>
#include <clocale>
#include<tuple>

#include "reader.cpp"

bool checker(const std::vector<Street> & vector, GeoData gd) {
    if(vector.size() > 1 && gd.findOverlaps(vector).size() > 0) {
        return true;
    }

    return false;
}

void checkVector(const std::string & type, const std::vector<Street> & vector, GeoData gd) {
    if(checker(vector, gd)) {
        gd.printData(gd.findOverlaps(vector), type);
    }
}

void iterate(const std::vector<GeoData> & geoData) {
    for(auto gd : geoData) {

        auto evenVector = gd.getEvenVector();
        auto oddVector = gd.getOddVector();

        if(checker(evenVector, gd) || checker(oddVector, gd)) {
            
            std::cout << gd.getName() << "\n";
        }

        checkVector("E: ", evenVector, gd);
        checkVector("O: ", oddVector, gd);
    }
}

void start() {
    Reader r = Reader("network.mid");
    r.read();
    while(!r.end()) {
        r.next();
    }

    iterate(r.getGeoData());
}

int main()
{
    start();
    return 0;
}