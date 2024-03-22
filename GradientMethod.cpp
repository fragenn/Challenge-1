#include "GradientMethod.hpp"

GradientMethod::GradientMethod(const unsigned int dim_,MuParserFun func_,
                       std::vector<MuParserFun> grad_func_,
                       const double tol_res_,const double tol_step_,const unsigned int max_it_,const Strategy & strat_):
                       dim(dim_),func(func_),tol_res(tol_res_),tol_step(tol_step_),max_it(max_it_),strat(strat_),x_point(dim),grad_x_val(dim){
                        grad_func.reserve(dim);
                        for(size_t i=0;i<dim;i++){
                            grad_func.emplace_back(grad_func_[i]);
                        }   
                       };

void GradientMethod::solve_exact(const std::vector<double> &initial_guess,double alpha_0){
    //check if we are in the right dimension
    if(initial_guess.size()!=dim){
        return;
    }

    //estabilish the point and the initial conditions
    bool conv_flag=false;
    x_point.set_coords(initial_guess);
    n_it=0;
    Point x_new(dim);

    //start the iterations
    while(n_it<max_it && !conv_flag){
        //evaluate f and grad_f in x_point
        f_x_val=func(x_point.get_coords());
        for(size_t i=0;i<dim;i++){
            grad_x_val.set_i_coord(i,grad_func[i](x_point.get_coords()));
        }
        //choice of alpha_k
        switch(strat){
            case(Strategy::Exponential):{
                alpha_k=alpha_0*exp(-mu*n_it);
                break;
            }
            case(Strategy::Inverse):{
                alpha_k=alpha_0/(1+mu*n_it);
                break;
            }
            case(Strategy::ApproxLine):{
                // set the initial guess of alpha
                alpha_k=alpha_0;
                //calculate the vector which must be evaluated in f
                Point x_1(dim);
                x_1.set_coords((x_point-grad_x_val*alpha_k).get_coords());
                while(std::abs(f_x_val-func(x_1.get_coords()))<sigma*alpha_k*norm(grad_x_val.get_coords())*norm(grad_x_val.get_coords())){
                    alpha_k=alpha_k/2;
                }
                break;
            }
            default:
                break;
        }

        //calculate the new x guess
        x_new.set_coords((x_point-grad_x_val*alpha_k).get_coords());

        //evaluate step length and residual
        res=norm(grad_x_val.get_coords());
        step=norm((x_new-x_point).get_coords());

        //check the convergence criteria
        if(res<tol_res || step<tol_step){
                conv_flag=true;
            }
        x_point.set_coords(x_new.get_coords());
        n_it++;
    }
}

void GradientMethod::solve_computed(const std::vector<double> &initial_guess,double alpha_0){
    //check if we are in the right dimension
    if(initial_guess.size()!=dim){
        return;
    }

    //estabilish the point and the initial conditions
    bool conv_flag=false;
    x_point.set_coords(initial_guess);
    n_it=0;
    Point x_new(dim);
    double h=0.01;
    //necessary for computation of derivatives
    Point x_plus(dim);

    //start the iterations
    while(n_it<max_it && !conv_flag){
        //evaluate f in x_point
        f_x_val=func(x_point.get_coords());
        //compute the derivatives of f using the forward derivatives
        x_plus.set_coords(x_point.get_coords());
        for(size_t i=0;i<dim;i++){
            x_plus.set_i_coord(i,x_plus.get_i_coord(i)+h);
            grad_x_val.set_i_coord(i,(func(x_plus.get_coords())-func(x_point.get_coords()))/h);
        }
        //choice of alpha_k
        switch(strat){
            case(Strategy::Exponential):{
                alpha_k=alpha_0*exp(-mu*n_it);
                break;
            }
            case(Strategy::Inverse):{
                alpha_k=alpha_0/(1+mu*n_it);
                break;
            }
            case(Strategy::ApproxLine):{
                // set the initial guess of alpha
                alpha_k=alpha_0;
                //calculate the vector which must be evaluated in f
                Point x_1(dim);
                x_1.set_coords((x_point-grad_x_val*alpha_k).get_coords());
                while(std::abs(f_x_val-func(x_1.get_coords()))<sigma*alpha_k*norm(grad_x_val.get_coords())*norm(grad_x_val.get_coords())){
                    alpha_k=alpha_k/2;
                }
                break;
            }
            default:
                break;
        }

        //calculate the new x guess
        x_new.set_coords((x_point-grad_x_val*alpha_k).get_coords());

        //evaluate step length and residual
        res=norm(grad_x_val.get_coords());
        step=norm((x_new-x_point).get_coords());

        //check the convergence criteria
        if(res<tol_res || step<tol_step){
                conv_flag=true;
            }
        x_point.set_coords(x_new.get_coords());
        n_it++;
    }
}

double GradientMethod::norm(const std::vector<double> &v) const{
    double sum=0.0;
    for(size_t i=0;i<v.size();i++){
        sum += v[i]*v[i];
    }
    return sqrt(sum);
}

void GradientMethod::print() const{
    std::cout<<"The coordinates of the minimal point are:\n"<<std::endl;
    for(size_t i=0;i<dim;i++){
        std::cout<<x_point.get_i_coord(i)<<std::endl;
    }
    std::cout<<std::endl;
    return;
}
