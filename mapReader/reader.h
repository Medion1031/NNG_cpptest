#ifndef READER
#define READER

#include <fstream>
#include <iostream>
#include <vector>

#include "GeoData.h"

class Reader {
    private: 
        enum Status { NORM, ABNORM };
        std::vector<GeoData> _geoData;
        //collect the names to search easier for an element
        std::vector<std::string> _geoDataNames;
        Status _currentStatus;
        std::ifstream _file;
        bool _end;

    public:
        enum Error { FILE_NOT_FOUND, EMPTY_FILE };

        Reader(const std::string & str);

        void first();
        void next();
        Status checkStatus();

        bool end() const { return _end; }
};

#endif //READER