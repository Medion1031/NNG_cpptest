#include "reader.h"


Reader::Reader(const std::string & str) {
    _file.open(str.c_str());

    if(_file.fail()) {
        throw FILE_NOT_FOUND;
    }
}

void Reader::read() {
    next();

    if(currentLine.empty()) {
        throw EMPTY_FILE;
    }
}

Reader::Status Reader::checkStatus() {
    if(_file.fail()) {
        return ABNORM;
    }
    return NORM;
}

std::tuple<int, int> Reader::intPairToTuple(const int & fstElement, const int & scndElement) {
    if(fstElement < scndElement) {
        return std::make_tuple(fstElement, scndElement);
    }

    return std::make_tuple(scndElement, fstElement);
}

std::vector<std::string> Reader::lineSplit(const std::string & str) {
   std::vector<std::string> outputArray;
   std::stringstream streamData(str);
   std::string val;

   while(std::getline(streamData, val, ',')) {
       if(val[0] == '"') {
           val = val.substr(1, val.size() - 2);
           outputArray.push_back(val);
           continue;
       }
       outputArray.push_back(val);
   } 

   return outputArray;
}

void Reader::createStreet(const std::string & name) {
    _geoDataNames.push_back(name);
    _geoData.push_back(GeoData(name));
}

int Reader::searchForStreetIndex(const std::string & str) {
    std::string currentName = lineSplit(str)[16] + " " + lineSplit(str)[17];
    std::vector<std::string>::iterator  it = std::find(_geoDataNames.begin(), _geoDataNames.end(), currentName);

    if(it != _geoDataNames.end()) {
        return it - _geoDataNames.begin();
    }

    createStreet(currentName);

    return _geoDataNames.size() - 1;
}

void Reader::processLine(const std::string & str, const int & index) {
    int indexOfStreet = searchForStreetIndex(str);
    auto currentTuple = Reader::intPairToTuple(std::stoi(lineSplit(str)[index+1]), std::stoi(lineSplit(str)[index+2]));
    std::string splittedChar = lineSplit(str)[index];

    switch (splittedChar[0]) {
        case 'O' :
            _geoData[indexOfStreet].addOddStreetNumber(currentTuple);
            break;
        case 'E' :
            _geoData[indexOfStreet].addEvenStreetNumber(currentTuple);
            break;
        case 'M' :
            _geoData[indexOfStreet].addMixedStreetNumber(currentTuple);
            break;
        

    }
}

bool Reader::checkEmpty(const int & index, const std::string & str) {
    return lineSplit(str)[index] != "";
}

void Reader::checkRoadsAreEmpty(const std::string & str, const int & index) {
    if(checkEmpty(index, str)) {
        processLine(str, index);
    }
}

void Reader::next() {
    getline(_file, currentLine);

    _currentStatus = checkStatus();
    _end = _currentStatus == ABNORM;
    iterator++;
    if(!_end && checkEmpty(16, currentLine) && checkEmpty(17, currentLine)) {
        checkRoadsAreEmpty(currentLine, 20);
        checkRoadsAreEmpty(currentLine, 23);
    }
}