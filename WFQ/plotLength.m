function plotLength()
figure;
load tq0l.txt
load tq1l.txt
load tq2l.txt
hold on
[h,stl0]=cdfplot(tq0l)

[h,stl1]=cdfplot(tq1l)
[h,stl2]=cdfplot(tq2l)
legend('Queue 1','Queue 2','Queue 3')
display(stl0)
display(stl1)
display(stl2)
xlabel('Queue Length')
title('Queue Length distribution')
hold off