#include <iostream>
#include <string>
#include <ctime>
#include "flann/flann.hpp"
#include "flann/io/vecs.h"


int main(int argc, const char * argv[]) {
    
    unsigned int k_nn_ = 100;
    unsigned int data_size = 10000;
    unsigned int query_size = 10;
    std::string input_file = "/Users/summer/Downloads/sift/sift_base.fvecs";
    std::string query_file = "/Users/summer/Downloads/sift/sift_query.fvecs";
    std::string out_put = "/Users/summer/Downloads/result.txt";
    
    time_t stime, etime;
    
    if (argc > 1) {
        for(int i=1;i<argc;i+=2)
        {
            switch(argv[i][1])
            {
                case 'n': k_nn_ = atoi(argv[i+1]);break;
                case 'd': data_size = atoi(argv[i+1]);break;
                case 'q': query_size = atoi(argv[i+1]);break;
                case 'I': input_file = std::string(argv[i+1]);break;
                case 'Q': query_file = std::string(argv[i+1]);break;
                case 'O': out_put = std::string(argv[i+1]);break;
            }
        }
    }
    
    if(data_size>1000000) data_size=1000000;
    if(query_size>10000) query_size=10000;
    
    typedef flann::Hamming<unsigned char> Distance;
    typedef Distance::ElementType ElementType;
    typedef Distance::ResultType DistanceType;
    flann::Matrix<ElementType> data;
    flann::Matrix<ElementType> query;
    flann::Matrix<int> gt_indices;
    flann::Matrix<DistanceType> dists;
    flann::Matrix<DistanceType> gt_dists;
    flann::Matrix<int> indices;

    fflush(stdout);
    flann::load_file(data, input_file, "dataset", data_size);
    flann::load_file(query, query_file, "query", query_size);
    
    flann::Index<Distance> index(data, flann::LshIndexParams());
    index.buildIndex();
    gt_indices = flann::Matrix<int>(new int[query.rows * k_nn_], query.rows, k_nn_);
    gt_dists = flann::Matrix<DistanceType>(new DistanceType[query.rows * k_nn_], query.rows, k_nn_);
    
    stime = clock();
    index.knnSearch(query, gt_indices, gt_dists, k_nn_, flann::SearchParams(-1));
    etime = clock();
    
    std::cout<<etime-stime<<" ";
    flann::save_file(gt_indices,out_put,"result");
    
    typedef flann::L2<float> Distance_;
    typedef Distance_::ElementType ElementType_;
    typedef Distance_::ResultType DistanceType_;
    flann::Matrix<ElementType_> data_;
    flann::Matrix<ElementType_> query_;
    flann::Matrix<int> gt_indices_;
    flann::Matrix<DistanceType_> dists_;
    flann::Matrix<DistanceType_> gt_dists_;
    flann::Matrix<int> indices_;
    
    flann::load_file(data_, input_file, "dataset", data_size);
    flann::load_file(query_, query_file, "query", query_size);
    
    flann::Index<Distance_> index_(data_, flann::KDTreeIndexParams(4));
    index_.buildIndex();
    gt_indices_ = flann::Matrix<int>(new int[query_.rows * k_nn_], query_.rows, k_nn_);
    gt_dists_ = flann::Matrix<DistanceType_>(new DistanceType_[query_.rows * k_nn_], query_.rows, k_nn_);
    
    stime = clock();
    index_.knnSearch(query_, gt_indices_, gt_dists_, k_nn_, flann::SearchParams(256));
    etime = clock();
    std::cout<<etime-stime<<std::endl;
    
    flann::save_file(gt_indices_,out_put+".2","result");

    return 0;
}
