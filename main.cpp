#include  <iostream>
#include   <fstream>
#include   <sstream>
#include <exception>

namespace Token {
    enum Token {
        
    };
}

int main(int argc, char *argv[]) {
    static std::istream *Stream;

    switch(argc) {
        case 1:
            Stream = &std::cin;
            break;

        case 2:
            Stream = new std::ifstream(argv[1]);
            break;

        case 3:
            if(argv[2] == "-c") {
                Stream = new std::istringstream(argv[3]);
                break;
            }

        default:
            std::cerr<<"error: invalid arguments."<< std::endl;
            return 0;
    }

    if(Stream != &std::cin) {
        delete Stream;
    }
}
