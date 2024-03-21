#include "GradientMethod.hpp"
#include "json.hpp"
#include <fstream>
#include <string>
#include <functional>
using json=nlohmann::json;

int main(int argc, char* argv[]){

    // Read parameters from JSON file
    std::ifstream ff("parameters.json");
    json datas=json::parse(ff);

    std::string func_str=datas.value("fun","");
    const unsigned int dim=datas.value("dim",1);
    std::vector<std::string> grad_func_strings(dim,"");
    for(unsigned int i=0;i<dim;i++){
        grad_func_strings[i]=datas.value("grad_fun_"+std::to_string(i+1),"");
    }
    Point x_initial(dim);
    for(unsigned int i=0;i<dim;i++){
        double val=datas.value("x_0_"+std::to_string(i+1),5.0);
        x_initial.set_i_coord(i,val);
    }
    const double tol_res=datas.value("eps_r",1e-2);
    const double tol_step=datas.value("eps_s",1e-2);
    const double alpha_init=datas.value("alpha_0",5.0);
    const unsigned int max_it=datas.value("N_MAX",1e3);

    // Creation of the function and its gradient as a MuParser class objects
    MuParserFun func(func_str,dim);
    std::vector<MuParserFun> grad_func;
    grad_func.reserve(dim);
    for(size_t i=0;i<dim;i++){
        std::string name=grad_func_strings[i];
        grad_func.emplace_back(name,dim);
    }

    // Ask the strategy to the user
    std::string strategy_string;
    std::cout<<"Choose a strategy between Exponential - Inverse - ApproxLine:\n"<<std::endl;
    std::cin>>strategy_string;
    Strategy strat=Strategy::ApproxLine;
    if(strategy_string=="Exponential"){
        strat=Strategy::Exponential;
    }
    if(strategy_string=="Inverse"){
        strat=Strategy::Inverse;
    }
    if(strategy_string=="ApproxLine"){
        strat=Strategy::ApproxLine;
    }

    
    
    
    // Solve the problem with the datas
    GradientMethod m(dim,func,grad_func,tol_res,tol_step,max_it,strat);
    m.solve(x_initial.get_coords(),alpha_init);

    // Print the solution
    m.print();

    return 0;
}

