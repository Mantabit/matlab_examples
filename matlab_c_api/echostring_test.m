%compile the C++ source file
mex echostring.cpp
%call the C function from Matlab
output=echostring('Test')