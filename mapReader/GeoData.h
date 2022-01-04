#ifndef GEODATA
#define GEODATA

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include<tuple>
#include<bits/stdc++.h>

struct Street {
    int start;
    int end;
};

bool operator==(const Street& lhs, const Street& rhs){
    return (lhs.start == rhs.start && lhs.end == rhs.end);
}
bool operator!=(const Street& lhs, const Street& rhs){
    return !(lhs.start == rhs.start && lhs.end == rhs.end);
}

class GeoData {
    private: 
        //STREET_NAME + STREET_TYPE
        std::string _name;
        std::vector<Street> _oddStreetNumbers;
        std::vector<Street> _evenStreetNumbers;
        std::vector<Street> modifiedVector;
        std::vector<Street> dataHolder;
        Street compressedData;
        int changeCount{};
        
        Street intPairToStreet(const int & fstElement, const int & scndElement);
        Street detectSegment(const Street & baseStreet, const Street iterateStreet);
        Street checkSegment(const Street & baseStreet, const Street iterateStreet);
        void searchOverlaps(const int i,const std::vector<Street> baseVector);
        void simplify();
        void connectPairs();


    public: 
        enum Error { EMPTY_NAME };
        GeoData(const std::string & name);

        void addOddStreetNumber(const Street & tup);
        void addEvenStreetNumber(const Street & tup);
        void addMixedStreetNumber(const Street & tup);

        void printData(const std::vector<Street> & data, const std::string & str);
        std::vector<Street> overlaps(const std::vector<Street> & _baseVector);
        
        std::string getName() const { return _name; }
        std::vector<Street> getEvenVector() const { return _evenStreetNumbers; }
        std::vector<Street> getOddVector() const { return _oddStreetNumbers; }
};

#endif