%check if compiled mex function already available
dirconts=ls;
if(isfile(fullfile(pwd,'exprtk_eval.mexw64'))==0)
    mex exprtk_eval.cpp CFLAGS='$CFLAGS -Wa,-mbig-obj';
end

ts=linspace(0,20,5000);
%text="switch{case t<10: 10000*t/10*sin(2*pi*0*t);default:
%10000*sin(2*pi*0*t);}"
expression='sin(t*(t*10/20))';
ys=exprtk_eval(expression,ts);

if any(isnan(ys))
    fprintf("Warning: Expression could not be evaluated for certain t.\n");
end

plot(ts,ys);
grid();
ylabel("Expression expr(t)");
xlabel("Time t [s]");