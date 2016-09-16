#ifndef VECS_H_
#define VECS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include "flann/util/matrix.h"

namespace flann{
    template<typename T>
    void load_file(flann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
    {
        size_t col;
        
        std::ifstream file(filename,std::ios::in|std::ios::binary);
        size_t l = file.tellg();
        file.read((char*)&col, sizeof(T));
        file.seekg(0, std::ios::end);
        size_t m = file.tellg();
        
        size_t row = (m-l)/(4+sizeof(T)*col);
        
        dataset = flann::Matrix<T>(new T[row*col], row, col);
        
        file.close();
    }
    
    template<typename T>
    void save_file(flann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
    {
        std::ofstream file(filename, std::ios::out|std::ios::binary);
        
        file.write((char*)dataset[0], sizeof(dataset));
        
        file.close();
    }
}

#endif