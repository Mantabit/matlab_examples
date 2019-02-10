ts=linspace(0,100,10000)';
xs=zeros(length(ts),1);
for i=1:1:length(ts)
    xs(i)=testsignal(ts(i));
end

inputdata=[ts,xs];