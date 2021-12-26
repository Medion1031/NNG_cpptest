#ifndef GEODATA
#define GEODATA

#include <iostream>
#include <vector>
#include<tuple>

class GeoData {
    private: 
        //STREET_NAME + STREET_TYPE
        std::string _name;
        std::vector<std::tuple<int, int>> _oddStreetNumbers;
        std::vector<std::tuple<int, int>> _evenStreetNumbers;
        std::vector<std::tuple<int, int>> modifiedVector;
        int changeCount{};

    public: 
        enum Error { EMTY_NAME };
        GeoData(const std::string & name);

        void addOddStreetNumber(const std::tuple<int, int> & tup);
        void addEvenStreetNumber(const std::tuple<int, int> & tup);
        void addMixedStreetNumber(const std::tuple<int, int> & tup);

        std::tuple<int, int> intPairToTuple(const int & fstElement, const int & scndElement);
        std::vector<std::tuple<int, int>> findOverlaps(const std::vector<std::tuple<int, int>> & _baseVector);

        std::string getName() const { return _name; }
};

#endif