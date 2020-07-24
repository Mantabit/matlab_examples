%%simulation parameters

%charge integrators
Cs=5e-12;
dC=1e-2*Cs;
CI=10e-12;
Rb=10e6;

%instrumentation amplifier
Rgain=5555.6;
Rinstr=25e3;
A_instr=(1+2*Rinstr/Rgain);

%sinngle ended inverted amp
R11=5.5e3;
R10=2.4e3;
A_inv=-R11/R10;

%low pass filter
Clp=1e-6;
Rlp=2.4e3;
taulp=Clp*Rlp;