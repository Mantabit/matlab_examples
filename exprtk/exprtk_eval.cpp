#include "mex.h"
#include "matrix.h"
#include "exprtk.hpp"

/*
 * Usage:       [output]=echoString('TestString');
 * A simple C function illuistrating how to pass arguments from Matlab to a C routine
 * foo="ABC"    describes a string object in Matlab (e.g. class(foo)='string')
 * bar='ABC'    describes an array of characters in Matlab (e.g. class(baz)='char')
 */

//define data types for exprtk
typedef double T;
typedef exprtk::symbol_table<T> symbol_table_t;
typedef exprtk::expression<T>     expression_t;
typedef exprtk::parser<T>             parser_t;

void checkArguments(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //check number of input and output arguments
    char errmsg[200];
    if(nrhs!=2) 
      mexErrMsgIdAndTxt("MATLAB:stringtest:invalidNumInputs","Two inputs (type string,type double array) required.");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt("MATLAB:stringtest:invalidNumOutputs","Too many output arguments. One output argument will be returned!");
    //check if the input argument is a char array (e.g. 'ABC' for example)
    if(mxIsChar(prhs[0]) != 1)
        mexErrMsgIdAndTxt("MATLAB:stringtest:inputNotString","First input must be a char array. (Hint: pass 'ABC' instead of \"ABC\")");
    if(mxIsDouble(prhs[1])!=1)
        mexErrMsgIdAndTxt("MATLAB:stringtest:inputNotString","Second input must be a double array.");
    //check if the input arguments are row vectors
    if((mxGetM(prhs[0])!=1)||(mxGetM(prhs[1])!=1)){
        sprintf(errmsg,"Inputs must be a row vector but dimension was (%d,%d) and (%d,%d)\n",mxGetM(prhs[0]),mxGetN(prhs[0]),mxGetM(prhs[1]),mxGetN(prhs[1]));
        mexErrMsgIdAndTxt("MATLAB:stringtest:inputNotRowVector",errmsg);
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{   
    //check the input arguments
    checkArguments(nlhs,plhs,nrhs,prhs);
    
    //number of characters in input array
    mwSize buflen=mxGetN(prhs[0])+1;
    //get a char array from mxArray input
    char* input_buf=mxArrayToString(prhs[0]);
    //print something to the Matlab Console
    //mexPrintf("Received c-style string: %s\n",input_buf);
    //get a pointer to the input double array
    double* times;
    times=mxGetPr(prhs[1]);
    size_t n_rows=mxGetN(prhs[1]);
    
    //time variable for exprtk expression
    T t;
    //symbol table for exprtk
    symbol_table_t symbol_table;
    symbol_table.add_variable("t",t);
    symbol_table.add_constants();
    //exprtk expression
    expression_t expression;
    expression.register_symbol_table(symbol_table);
    //compile the expression
    parser_t parser;
    parser.compile(input_buf,expression);
    
    //create a double matrix and get a pointer to it data, fill the matrix
    mxArray* output=mxCreateDoubleMatrix(1,n_rows,mxREAL);
    double* expr_vals=mxGetPr(output);
    for(int i=0; i<n_rows; i++){
        t=times[i];
        expr_vals[i]=expression.value();
        //mexPrintf("t: %f \t\t f(t): %f\n",t,expr_vals[i]);
    }
    
    //create an mxArray of char to pass to Matlab
    //mxArray* outputmx=mxCreateString(input_buf);
    //pass result to matlab
    plhs[0]=output;
}