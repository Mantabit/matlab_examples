%check if compiled mex function already available
dirconts=ls;
if(isfile(fullfile(pwd,'exprtk_eval.mexw64'))==0)
    mex exprtk_eval.cpp CFLAGS='$CFLAGS -Wa,-mbig-obj';
end

ts=linspace(0,10,1000);
expression='switch{case t<1: 1;case t<2: 2; default: 5*sin(t)*exp(-t);}';
ys=exprtk_eval(expression,ts);

if any(isnan(ys))
    fprintf("Warning: Expression could not be evaluated for certain t.\n");
end

plot(ts,ys);
grid();
ylabel("Expression expr(t)");
xlabel("Time t [s]");