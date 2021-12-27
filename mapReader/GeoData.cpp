#include "GeoData.h"

GeoData::GeoData(const std::string & name) {
    if(name.empty()) {
        throw EMPTY_NAME;
    }
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

    if(std::get<0>(baseTuple) >= std::get<0>(iterateTuple) && std::get<1>(baseTuple) <= std::get<1>(iterateTuple)) {
        return baseTuple;
    }
    if(std::get<0>(baseTuple) >= std::get<0>(iterateTuple)) {
        return GeoData::intPairToTuple(std::get<0>(baseTuple), std::get<1>(iterateTuple));
    }
    if(std::get<1>(baseTuple) <= std::get<1>(iterateTuple)) {
        return GeoData::intPairToTuple(std::get<0>(iterateTuple), std::get<1>(baseTuple));
    }

    return GeoData::intPairToTuple(-1, -1);

}


void GeoData::searchOverlaps(const int i, int *changeCount, std::vector<std::tuple<int, int>> *modifiedVector,const std::vector<std::tuple<int, int>> baseVector) {
    for(auto k = (i+1); k != baseVector.size(); k++) {
        if(detectSegment(baseVector[i], baseVector[k]) != std::make_tuple(-1,-1)) {
            modifiedVector->push_back(detectSegment(baseVector[i], baseVector[k]));
            changeCount++;
        }
    }
}

//i know i pass way more parameter than it would be elegant but i didn't wanted nested for loops.
std::vector<std::tuple<int, int>> GeoData::findOverlaps(const std::vector<std::tuple<int, int>> & _baseVector) {
    modifiedVector.clear();
    changeCount = 0;

    for(auto i = 0; i != _baseVector.size()-1; i++) {
        searchOverlaps(i, &changeCount, &modifiedVector, _baseVector);
    }

    if(changeCount > 0) {
        return GeoData::findOverlaps(modifiedVector);
    }
    return modifiedVector;
}

void GeoData::printData(const std::vector<std::tuple<int, int>> & data) {
    for(std::tuple<int, int> d : data) {
        std::cout << std::to_string(std::get<0>(d)) << "-" << std::to_string(std::get<1>(d)) << ", ";
    }
    std::cout << "\n";
}