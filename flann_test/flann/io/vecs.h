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
    void load_file(flann::Matrix<T>& dataset, const std::string& filename, const std::string& name, int number = 100000)
    {
        int col;
        
        std::ifstream file(filename,std::ios::in|std::ios::binary);
        size_t l = file.tellg();
        file.read((char*)&col, 4);

        file.seekg(0, std::ios::end);
        size_t m = file.tellg();
        
        int row = (m-l)/(4+4*col);
        if(row>number) row=number;

        int multy = sizeof(float)/sizeof(T);
        dataset = flann::Matrix<T>(new T[row*col*multy], row, col*multy);

        int x;
        file.seekg(0, std::ios::beg);
        for(int i=0;i<row;i++)
        {
            file.read((char*)&x,4);
            for(int j=0;j<col*multy;j++)
            {
                file.read((char*)&dataset[i][j], sizeof(T));
            }
        }
        
        
        file.close();
    }
    
    template<typename T>
    void save_file(flann::Matrix<T>& dataset, const std::string& filename, const std::string& name)
    {
        std::ofstream file(filename, std::ios::out|std::ios::binary);
        
//        file.write((char*)dataset[0], sizeof(dataset));
        
        for(int i=0;i<dataset.rows;i++)
        {
//            file.write((char*)&dataset.cols, 4);
            for(int j=0;j<dataset.cols;j++)
            {
                file<<dataset[i][j]<<" ";
//                file.write((char*)&dataset[i][j], sizeof(T));
            }
            file<<"\n";

        }
        file.close();
    }
    
    template<typename T>
    void showDataset(flann::Matrix<T>& dataset)
    {
        for(int i=0;i<dataset.rows;i++)
        {
            for(int j=0;j<dataset.cols;j++)
            {
                std::cout<<dataset[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
}

#endif