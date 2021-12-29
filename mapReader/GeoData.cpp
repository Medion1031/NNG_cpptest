#include "GeoData.h"

GeoData::GeoData(const std::string & name) {
    if(name.empty()) {
        throw EMPTY_NAME;
    }
    _name = name;
}

void GeoData::addOddStreetNumber(const std::tuple<int, int> & tup) {
    _oddStreetNumbers.push_back(tup);
}

void GeoData::addEvenStreetNumber(const std::tuple<int, int> & tup) {
    _evenStreetNumbers.push_back(tup);
}

//it will make easier to add mixed data to the class
void GeoData::addMixedStreetNumber(const std::tuple<int, int> & tup) {
    GeoData::addEvenStreetNumber(tup);
    GeoData::addOddStreetNumber(tup);
}

std::tuple<int, int> GeoData::intPairToTuple(const int & fstElement, const int & scndElement) {
    if(fstElement < scndElement) {
        return std::make_tuple(fstElement, scndElement);
    }

    return std::make_tuple(scndElement, fstElement);
}

std::tuple<int, int> GeoData::detectSegment(const std::tuple<int, int> & baseTuple, const std::tuple<int, int> iterateTuple) {

    int base01 = std::get<0>(baseTuple),
        base02 = std::get<1>(baseTuple),
        iterate01 = std::get<0>(iterateTuple),
        iterate02 = std::get<1>(iterateTuple);


    if(base01 < iterate01 && base02 > iterate02) {
        return iterateTuple;
    }
    else if(base01 > iterate01 && base02 < iterate02) {
        return baseTuple;
    }
    else if(base01 > iterate01 && base02 > iterate02 && base01 < iterate02) {
        return GeoData::intPairToTuple(base01, iterate02);
    }
    else if(base01 < iterate01 && base02 < iterate02 && base01 > iterate02) {
        return GeoData::intPairToTuple(iterate01, base02);
    }
    else if(base01 == iterate01 && base02 == iterate02) {
        return baseTuple;
    }

    return GeoData::intPairToTuple(-1, -1);

}


void GeoData::searchOverlaps(const int i,const std::vector<std::tuple<int, int>> baseVector) {
    for(auto k = (i+1); k != baseVector.size(); k++) {
        auto currentTuple = detectSegment(baseVector[i], baseVector[k]);
        auto foundTuple = std::find(modifiedVector.begin(), modifiedVector.end(), currentTuple);
        
        if(currentTuple != std::make_tuple(-1,-1) && foundTuple == modifiedVector.end()) {
            modifiedVector.push_back(currentTuple);
            changeCount++;
        }
    }
}

//i know i pass way more parameter than it would be elegant but i didn't wanted nested for loops.
std::vector<std::tuple<int, int>> GeoData::findOverlaps(const std::vector<std::tuple<int, int>> & _baseVector) {
    modifiedVector.clear();
    changeCount = 0;

    for(auto i = 0; i != _baseVector.size()-1; i++) {
        searchOverlaps(i, _baseVector);
    }

    dataHolder = modifiedVector;

    if(changeCount > 0 && modifiedVector.size() > 1) {
        return GeoData::findOverlaps(dataHolder);
    }

    return dataHolder;
}

void GeoData::printData(const std::vector<std::tuple<int, int>> & data, const std::string & str) {
    std::cout << str;
    for(std::tuple<int, int> d : data) {
        std::cout << std::get<0>(d) << "-" << std::get<1>(d) << ", ";
    }
    std::cout << "\n\n";
}