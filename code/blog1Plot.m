data = csvread('../datasets/housingPricesMini.csv');
area = data(:,1);
price = data(:,2);
xlabel("Area");
ylabel("Price");
title("Housing Prices - 1000 Nos");
s = scatter(area, price, "filled");
hold on
saveas(s, "test.png");


