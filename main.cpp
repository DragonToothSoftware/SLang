#include  <iostream>
#include   <fstream>
#include   <sstream>
#include <exception>

int main(int argc, char *argv[]) {
    try {
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
    }

    catch(std::bad_alloc &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::bad_exception &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::invalid_argument &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::length_error &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::out_of_range &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::overflow_error &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::range_error &Error) {
        std::cerr<< Error.what() << std::endl;
    }

    catch(const std::underflow_error &Error) {
        std::cerr<< Error.what() << std::endl;
    }
}
