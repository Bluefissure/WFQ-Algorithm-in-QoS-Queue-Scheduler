function plotWait()
figure;
load tq0w.txt
load tq1w.txt
load tq2w.txt
hold on
[h,stw0]=cdfplot(tq0w)
[h,stw1]=cdfplot(tq1w)
[h,stw2]=cdfplot(tq2w)
legend('Queue 1','Queue 2','Queue 3')
display(stw0)
display(stw1)
display(stw2)
xlabel('Wait Time')
title('Wait Time distribution')
hold off