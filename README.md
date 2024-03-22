# Challenge-1

## Abstract
Here I have uploaded my solution for the first Challenge of the Advanced Programming and Scientific Computing (PACS) course in Politecnico di Milano.
The main purpose of the challenge is to implement a program which computes the minimum of a function of n variables using the **gradient method**.
In particular, this method is combined with a precise rule to find out the decay parameter, chosen by the user between the Exponential Decay, the Inverse Decay or an Approximation Line Search (which in our case was implemented using the Armijo rule) (see more informations on the Challenge23-24-1.pdf file).

## Rules
In order to execute the program correctly, it is compulsory to change correctly in the `Makefile` section the path where to include the muParser library. In particular, change the `/path/to/host/folder` with your own path; after this, open a Terminal and do the following in order to execute correctly the file:
```bash
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/host/folder/pacs-examples/Examples/lib
make
./main
```
Then, you will be ask to choose your own strategy between the three proposed in order to use it to compute the decay parameter and gain the computed minimum.

## General overview
My followed path was to create a class named `GradientMethod` which takes care of all the necessary datas to compute the minimum; in particular, to work better with the coordinates of the variable x, I created an appropriate `Point` class in order to correctly guarantee the usage of all the necessary operations between vectors (sum, difference and product by a scalar). Lastly, we use the `MuParserFun` class in order to manage the functions by taking their expression written as a string inside the `parameters.json` file (this works both for the function and all the n components of the exact gradient). Moreover, you can choose to compute the gradient with the numerical method of forward finite differences, which is implemented in the `GradientMethod.cpp` as a different solver method. The user can choose the computational strategy by writing "Exact" or "Computed" on the terminal at run-time.





