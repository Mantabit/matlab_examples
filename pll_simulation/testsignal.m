function [y] = testsignal(t)
switchtime=5;
if t<switchtime
    y=360*t;
else
    y=360*switchtime+720*(t-switchtime);
end
end

