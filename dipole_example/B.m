function [B] = B(r,m)
r_hat=r/norm(r);
B=3/norm(r)^3*(3*(r_hat'*m)*r_hat-m);
end

