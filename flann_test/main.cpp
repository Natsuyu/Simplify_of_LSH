#include <iostream>
#include "flann/flann.hpp"
#include "flann/io/vecs.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    int nn = 3;
    
//    Matrix<unsigned char> dataset;
//    Matrix<unsigned char> query;
//    load_file(dataset, "/Users/summer/Downloads/sift/sift_base.fvecs","dataset");
//    load_file(query, "/Users/summer/Downloads/sift/sift_query.fvecs","query");
//
//    Matrix<unsigned int> dists(new unsigned int[query.rows*nn], query.rows, nn);
//    Matrix<size_t> indices(new size_t[query.rows*nn], query.rows, nn);
//    
//    // construct an randomized kd-tree index using 4 kd-trees
//    std::cout<<"read all"<<std::endl;
//    Index<Hamming<unsigned char>> index(dataset, LinearIndexParams());
//    index.buildIndex();
//    std::cout<<index<<std::endl;
//    // do a knn search, using 128 checks
//    index.knnSearch(query, indices, dists, nn, SearchParams(-1));
//
//    
//    flann::save_file(indices,"/Users/summer/Downloads/result.txt","result");
//    
//    delete[] dataset.ptr();
//    delete[] query.ptr();
//    delete[] indices.ptr();
//    delete[] dists.ptr();
    
    typedef flann::Hamming<unsigned char> Distance;
    typedef Distance::ElementType ElementType;
    typedef Distance::ResultType DistanceType;
    flann::Matrix<ElementType> data;
    flann::Matrix<ElementType> query;
    flann::Matrix<int> gt_indices;
    flann::Matrix<DistanceType> dists;
    flann::Matrix<DistanceType> gt_dists;
    flann::Matrix<int> indices;
    unsigned int k_nn_;
    
    k_nn_ = 3;
    printf("Reading test data...");
    fflush(stdout);
    flann::load_file(data, "/Users/summer/Downloads/sift/sift_base.fvecs", "dataset");
    flann::load_file(query, "/Users/summer/Downloads/sift/sift_query.fvecs", "query");

    dists = flann::Matrix<DistanceType>(new DistanceType[query.rows * k_nn_], query.rows, k_nn_);
    indices = flann::Matrix<int>(new int[query.rows * k_nn_], query.rows, k_nn_);
    
    printf("done\n");
    
    // The matches are bogus so we compute them the hard way
    //    flann::load_from_file(match,"brief100K.h5","indices");
    
    flann::Index<Distance> index(data, flann::LshIndexParams());
    index.buildIndex();
    
    gt_indices = flann::Matrix<int>(new int[query.rows * k_nn_], query.rows, k_nn_);
    gt_dists = flann::Matrix<DistanceType>(new DistanceType[query.rows * k_nn_], query.rows, k_nn_);
    index.radiusSearch(query, gt_indices, gt_dists, 10, flann::SearchParams(-1));
    
    flann::showDataset(gt_indices);
    flann::save_file(gt_indices,"/Users/summer/Downloads/result.txt","result");
    return 0;
}
