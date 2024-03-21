#ifndef POINT_HPP_
#define POINT_HPP_
#include <vector>
#include <iostream>

class Point{

    private:
        // Coordinates
        std::vector<double> coords;
        // Dimension
        const unsigned int dim;
    public:
        // Constructors
        Point(unsigned int dim_):dim(dim_){    coords.resize(dim,0.0);};
        Point(const std::vector<double> &coords_):coords(coords_),dim(coords_.size()){};

        //Getters and setters
        unsigned int get_dim() const{return dim;};
        double get_i_coord(const unsigned int i) const{return coords[i];};
        void set_i_coord(const unsigned int i, double value){coords[i]=value;};
        std::vector<double> get_coords() const{return coords;};
        void set_coords(const std::vector<double> &coords_) {coords=coords_;};

        // Overloaded operators
        Point operator+(Point y){
            Point res(coords.size());
            if(coords.size()!=y.get_dim()){
                std::cerr<<"The two points must have the same dimension"<<std::endl;
            return (*this);
            }
            for(size_t i=0;i<y.get_dim();i++){
                res.set_i_coord(i,coords[i]+y.get_i_coord(i));
            }
            return res;
        };

        Point operator-(Point y){
            Point res(coords.size());
            if(coords.size()!=y.get_dim()){
                std::cerr<<"The two points must have the same dimension"<<std::endl;
            return (*this);
            }
            for(size_t i=0;i<y.get_dim();i++){
                res.set_i_coord(i,coords[i]-y.get_i_coord(i));
            }
            return res;
        };
        Point operator*(const double c){
            Point res(coords.size());
            for(size_t i=0;i<dim;i++){
                res.set_i_coord(i,coords[i]*c);
            }
            return res;
        };
};

#endif /*POINT_HPP_*/