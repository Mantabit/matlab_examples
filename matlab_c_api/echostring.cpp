#include "mex.h"
#include "matrix.h"
#include <exprtk.hpp>

/*
 * Usage:       [output]=echoString('TestString');
 * A simple C function illuistrating how to pass arguments from Matlab to a C routine
 * foo="ABC"    describes a string object in Matlab (e.g. class(foo)='string')
 * bar='ABC'    describes an array of characters in Matlab (e.g. class(baz)='char')
 */

void checkArguments(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //check number of input and output arguments
    char errmsg[200];
    if(nrhs!=1) 
      mexErrMsgIdAndTxt("MATLAB:stringtest:invalidNumInputs","One input (type string) required.");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt("MATLAB:stringtest:invalidNumOutputs","Too many output arguments. One output argument will be returned!");
    //check if the input argument is a char array (e.g. 'ABC' for example)
    if(mxIsChar(prhs[0]) != 1)
        mexErrMsgIdAndTxt("MATLAB:stringtest:inputNotString","Input must be a char array. (Hint: pass 'ABC' instead of \"ABC\")");
    //check if the input argument is a row vector
    if(mxGetM(prhs[0])!=1){
        sprintf(errmsg,"Input must be a row vector but dimension was (%d,%d)\n",mxGetM(prhs[0]),mxGetN(prhs[0]));
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
    mexPrintf("Received c-style string: %s\n",input_buf);
    //create an mxArray of char to pass to Matlab
    mxArray* outputmx=mxCreateString(input_buf);
    //pass result to matlab
    plhs[0]=outputmx;
}