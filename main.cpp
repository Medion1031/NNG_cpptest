#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string myText;

    // Read from the text file
    ifstream MyReadFile("network.mid");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
    // Output the text from the file
    cout << myText;
    }

    // Close the file
    MyReadFile.close();
    return 0;
}
