#include "reader.cpp"

void start() {
    Reader r = Reader("network.mid");
    std::vector<GeoData> currentData;

    r.read();
    while(!r.end()) {
        r.next();
    }

    currentData = r.getGeoData();

    r.processData(currentData);
}

int main()
{
    start();
    return 0;
}