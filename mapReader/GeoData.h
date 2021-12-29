#ifndef GEODATA
#define GEODATA

#include <iostream>
#include <vector>
#include<tuple>
#include<string> 

class GeoData {
    private: 
        //STREET_NAME + STREET_TYPE
        std::string _name;
        std::vector<std::tuple<int, int>> _oddStreetNumbers;
        std::vector<std::tuple<int, int>> _evenStreetNumbers;
        std::vector<std::tuple<int, int>> modifiedVector;
        std::vector<std::tuple<int, int>> dataHolder;
        int changeCount{};

    public: 
        enum Error { EMPTY_NAME };
        GeoData(const std::string & name);

        void addOddStreetNumber(const std::tuple<int, int> & tup);
        void addEvenStreetNumber(const std::tuple<int, int> & tup);
        void addMixedStreetNumber(const std::tuple<int, int> & tup);

        std::tuple<int, int> intPairToTuple(const int & fstElement, const int & scndElement);
        std::vector<std::tuple<int, int>> findOverlaps(const std::vector<std::tuple<int, int>> & _baseVector);
        std::tuple<int, int> detectSegment(const std::tuple<int, int> & baseTuple, const std::tuple<int, int> iterateTuple);
        void searchOverlaps(const int i,const std::vector<std::tuple<int, int>> baseVector);
        void printData(const std::vector<std::tuple<int, int>> & data, const std::string & str);
        
        std::string getName() const { return _name; }
        std::vector<std::tuple<int, int>> getEvenVector() const { return _evenStreetNumbers; }
        std::vector<std::tuple<int, int>> getOddVector() const { return _oddStreetNumbers; }
};

#endif