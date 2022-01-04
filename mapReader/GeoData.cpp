#include "GeoData.h"

GeoData::GeoData(const std::string & name) {
    if(name.empty()) {
        throw EMPTY_NAME;
    }
    _name = name;
}

void GeoData::addOddStreetNumber(const Street & tup) {
    _oddStreetNumbers.push_back(tup);
}

void GeoData::addEvenStreetNumber(const Street & tup) {
    _evenStreetNumbers.push_back(tup);
}

void GeoData::addMixedStreetNumber(const Street & tup) {
    GeoData::addEvenStreetNumber(tup);
    GeoData::addOddStreetNumber(tup);
}

Street GeoData::intPairToStreet(const int & fstElement, const int & scndElement) {
    if(fstElement < scndElement) {
        return Street{fstElement, scndElement};
    }

    return Street{scndElement, fstElement};
}

Street GeoData::checkSegment(const Street & baseStreet, const Street iterateStreet) {
    int baseStart = baseStreet.start,
        baseEnd = baseStreet.end,
        iterateStart = iterateStreet.start,
        iterateEnd = iterateStreet.end;

    if(baseStart <= iterateStart && baseEnd >= iterateEnd) {
        return iterateStreet;
    }
    if(baseStart > iterateStart && baseEnd < iterateEnd) {
        return baseStreet;
    }
    if(baseEnd >= iterateStart && baseStart <= iterateStart) {
        return Street{iterateStart, baseEnd};
    }

    return Street{baseStart, iterateEnd};
}

Street GeoData::detectSegment(const Street & baseStreet, const Street iterateStreet) {

    if(!(baseStreet.end < iterateStreet.start || baseStreet.start > iterateStreet.end)) {
        return checkSegment(baseStreet, iterateStreet);
    }

    return Street{-1,-1};

}

void GeoData::searchOverlaps(const int i,const std::vector<Street> baseVector) {
    for(auto k = (i+1); k != baseVector.size(); k++) {
        auto currentStreet = detectSegment(baseVector[i], baseVector[k]);
        auto foundStreet = std::find(modifiedVector.begin(), modifiedVector.end(), currentStreet);

        if(currentStreet != Street{-1,-1} && foundStreet == modifiedVector.end()) {
            modifiedVector.push_back(currentStreet);
        }
    }
}

void GeoData::connectPairs() {
    for(int j = 0; j < modifiedVector.size(); j++) {
        if(compressedData.start <= modifiedVector[j].start && compressedData.end >= modifiedVector[j].end) {
            modifiedVector.erase(modifiedVector.begin() + j);
            j--;
        }
        else if(compressedData.start > modifiedVector[j].start && compressedData.end < modifiedVector[j].end) {
            compressedData = Street{modifiedVector[j].start, modifiedVector[j].end};
            modifiedVector.erase(modifiedVector.begin() + j);
            j--;
        }
        else if(compressedData.start <= modifiedVector[j].start && compressedData.end >= modifiedVector[j].start) {
            compressedData = Street{compressedData.start, modifiedVector[j].end};
            modifiedVector.erase(modifiedVector.begin() + j);
            j--;
        }
        else if(modifiedVector[j].start <= compressedData.start & modifiedVector[j].end >= compressedData.start) {
            compressedData = Street{modifiedVector[j].start, compressedData.end};
            modifiedVector.erase(modifiedVector.begin() + j);
            j--;
        }
    }
}

void GeoData::simplify() {
    dataHolder.clear();

    while(modifiedVector.size() != 0) {
        compressedData = modifiedVector[0];
        modifiedVector.erase(modifiedVector.begin());

        connectPairs();

        dataHolder.push_back(compressedData);
    }
    modifiedVector = dataHolder;
}

std::vector<Street> GeoData::overlaps(const std::vector<Street> & _baseVector) {
    modifiedVector.clear();

    for(auto i = 0; i != _baseVector.size()-1; i++) {
        searchOverlaps(i, _baseVector);
    }

    simplify();

    return modifiedVector;
}

void GeoData::printData(const std::vector<Street> & data, const std::string & str) {
    std::cout << str;
    for(Street d : data) {
        std::cout << d.start << "-" << d.end << ", ";
    }
    std::cout << "\n\n";
}