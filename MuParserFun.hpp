#include <muParser.h>
#include "Point.hpp"

#include <memory>
#include <string>
#include <iostream>

class MuParserFun{
    private:
        unsigned int dim;
        std::vector<double> var;
        mu::Parser parser;
        std::string func_string;
    public:
        // Constructors
        MuParserFun(const MuParserFun &p):dim(p.dim),parser(p.parser){
            func_string=p.func_string;
            parser.SetExpr(func_string);
            var.resize(dim);
            for(size_t i=0;i<dim;i++){
                parser.DefineVar("x_"+std::to_string(i+1),&var[i]);
            }
        };

        MuParserFun(const std::string &s, unsigned int n):dim(n),func_string(s){
            try{
                var.resize(n);
                parser.SetExpr(s);
                for(size_t i=0;i<dim;i++){
                    parser.DefineVar("x_"+std::to_string(i+1),&var[i]);
                }
            }catch(mu::Parser::exception_type &e){
                std::cerr<<e.GetMsg()<<std::endl;
            }
        };

        // Operators
        double operator()(const std::vector<double>& x){
            if(x.size()!=var.size()){
                std::cerr<<"The dimensions do not coincide"<<std::endl;
                return std::numeric_limits<double>::quiet_NaN();
            }

            for(size_t i=0;i<x.size();i++){
                var[i]=x[i];
            }

            return parser.Eval();
        };
};