#include "Direction.hpp"
#include <string>
#include <vector>
//#include <unordered_map>
#include<tr1/unordered_map>
namespace ariel{

    class Notebook{
        
        std::tr1::unordered_map<int, std::tr1::unordered_map<int, std::string>> pages;
        
        //std::tr1::unordered_map<int, std::tr1::unordered_map<int, char[100]>> pages;
        
        public:
            //Constructor
            Notebook();

            //Destructor
            ~Notebook();

            void write(int page, int row, int col, Direction dir, std::string msg);

            std::string read(int page, int row, int col, Direction dir, int len);

            void erase(int page, int row, int col, Direction dir, int len);

            void show(int page);
         
    };
}   