#include <iostream>
#include <vector>
#include<tuple>

#include "GeoData.h"

GeoData::GeoData(const std::string & name) {
    if(name == "") {
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

std::tuple<int, int> detectSegment(const std::tuple<int, int> & baseTuple, const std::tuple<int, int> iterateTuple) {
    switch {
        case get<0>(baseTuple) >= get<0>(iterateTuple) && get<1>(baseTuple) <= get<1>(iterateTuple): 
            return baseVector[i-1];
            break;

        case get<0>(baseTuple) >= get<0>(iterateTuple):
            return GeoData::intPairToTuple(baseNum01, iterateNum02);
            break;

        case get<1>(baseTuple) <= get<1>(iterateTuple):
            return GeoData::intPairToTuple(iterateNum01, baseNum02);
            break;

        default: 
            return null;
            break;
    }
}


void searchOverlaps(const int i, int *changeCount, std::vector<std::tuple<int, int>> *modifiedVector,const std::vector<std::tuple<int, int>> baseVector) {
    for(auto k = (i+1); k != baseVector.end(); k++) {
        if(detectSegment(baseVector[i], baseVector[k]) != null) {
            modifiedVector->push_back(detectSegment(baseVector[i], baseVector[k]));
            changeCount++;
        }
    }
}

//i know i pass way more parameter than it would be elegant but i didn't wanted nested for loops.
std::vector<std::tuple<int, int>> GeoData::findOverlaps(const std::vector<std::tuple<int, int>> & _baseVector) {
    modifiedVector.clear();
    changeCount = 0;

    for(auto i = 0; i != _baseVector.end()[-2]; i++) {
        searchOverlaps(i, &changeCount, &modifiedVector, _baseVector);
    }

    if(changeCount > 0) {
        return GeoData::findOverlaps(modifiedVector);
    }

    return modifiedVector;
}

//TODO: kiiratni rendesen az adatokat illetve modositani az elerhetosegeken