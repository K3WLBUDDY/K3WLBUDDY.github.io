#!/usr/bin/octave -qf
data = csvread("../datasets/housingPricesMini.csv")
area = data(:,1);
price = data(:,2);
xlabel("Area");
ylabel("Price");
title("Housing Prices - 1000 Nos");
x = 1:5000;
s = scatter(area, price, "filled");
hold on
plot(x, 16.310*x);
hold off
saveas(s, "testCLI.png");


