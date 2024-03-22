#ifndef GRADIENTMETHOD_HPP_
#define GRADIENTMETHOD_HPP_
#include <vector>
#include <cmath>
#include <functional>
#include "Point.hpp"
#include "MuParserFun.hpp"

enum class Strategy {
    Exponential,
    Inverse,
    ApproxLine
};

class GradientMethod{
    private:
        // Dimension of the space n
        const unsigned int dim;
        // Function expression f:R^n--->R
        MuParserFun func;
        // Function gradient expression (in a vector of functions) D_f:R^n--->R^n
        std::vector<MuParserFun> grad_func;
        // Residual tolerance
        const double tol_res;
        // Step Length tolerance
        const double tol_step;
        // Max iterations number
        const unsigned int max_it;
        // Strategy for decay
        Strategy strat;

        // Variables used by the solver method
        // Point x in R^n
        Point x_point;
        // Value of the function in the point x
        double f_x_val;
        // Value of the gradient of the function in the point x
        Point grad_x_val;
        // Parameter of decay (current at every iteration k)
        double alpha_k;
        double mu=0.2;
        double sigma=0.25;
        // Current number of iterations
        unsigned int n_it;
        // Current residual
        double res;
        // Current step
        double step;
        

    public:
        // Gradient Method Constructor
        GradientMethod(const unsigned int dim_,MuParserFun func_,
                       std::vector<MuParserFun> grad_func_,
                       const double tol_res_,const double tol_step_,const unsigned int max_it_,const Strategy & strat_);
        
        // Solvers
        void solve_exact(const std::vector<double> &initial_guess,double alpha_0);
        void solve_computed(const std::vector<double> &initial_guess,double alpha_0);

        // Norm of a vector
        double norm(const std::vector<double> &v) const;

        // Getters
        std::vector<double> get_x_coordinates() const{return x_point.get_coords();};
        Strategy get_strat() const{return strat;};
        unsigned int get_iterations() const{return n_it;};
        std::vector<double> get_grad_x_val() const{return grad_x_val.get_coords();};
        MuParserFun get_function() const{return func;};

        // Print the solution
        void print() const;
};

#endif /* GRADIENTMETHOD_HPP_*/