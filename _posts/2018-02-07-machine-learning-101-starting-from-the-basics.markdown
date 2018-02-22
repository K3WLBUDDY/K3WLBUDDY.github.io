---
layout: post
title:  "Machine Learning 101 - Starting from the Basics"
excerpt: "Understanding the building blocks of the Machine Learning world"
date:   2018-02-07 22:00:00
---
This is the first in a series of blog posts that I've elegantly called <strong>"Machine Learning 101"</strong>. The main purpose of these posts is for me to remind myself of things I've learnt ( I have the habit of forgetting things easily ) and to help any noob understand a lot of things about Machine Learning. If you're new to ML and have absolutely no clue whatsoever about it then this is one of the places to start from. 

So without further ado, let's get into ML - 101. This is a long post so get some chips or something.

## Getting the intuition for Machine Learning

For the purpose of this post, I'd like you to forget whatever passing comments you would have heard about Machine Learning from your nerdy friends or the internet. We're going to start on a blank slate.

I'm going to start off with an example.

Imagine that you're the owner of a house and you're looking to rent it out to make some extra $$$ on the side. You're having a problem figuring out what the monthly rent should be. 

Now, when it comes to deciding the rent for a house, a lot of factors come into play. Things like the Square Feet occupied, the amenities provided like covered car parking etc. all play a role in the final price.

To get a clearer picture I've collected some rental prices for homes in T. Nagar from 99acres.com. To make the understanding easier and for brevity I've taken into consideration only 3 features that decide the rent.

### Rental prices in T. Nagar

<table>
<tr>
<th>Square Feet (sq.ft)</th>
<th>No. of Bedrooms (BHK)</th>
<th>Age (years)</th>
<th>Rent per Month (&#x20b9;)</th>
</tr>
<tr>
<td>1200</td>
<td>3</td>
<td>10+</td>
<td>35000</td>
</tr>
<tr>
<td>600</td>
<td>1</td>
<td>5+</td>
<td>14000</td>
</tr>
<tr>
<td>1200 </td>
<td>2</td>
<td>10</td>
<td>25000</td>
</tr>
<tr>
<td>1800</td>
<td>3</td>
<td>1</td>
<td>37000</td>
</tr>
<tr>
<td>435</td>
<td>1</td>
<td>10+</td>
<td>10000</td>
</tr>
</table>

Have a look at the table and analyze the data for a minute or two.

The first thing to note is that the final rent depends on three <strong>features</strong> namely the Area, BHK and age. 

Each of the three features have some <strong>weight</strong> of say in the final price. You might give more weight/importance to the Area of the house while others might care more about the No. of bedrooms. The exact preferences of each individual doesn't matter here. What does matter is the overall weight contributed to the final rent of the house by each feature. 

Let's generalize that last sentence into a neat equation :

$$ rent[i] =  \theta_1 * size[i] + \theta_2 * bhk[i] + \theta_3 * age[i] $$

Here $$ i $$ refers to the i-th entry.

For example if the value of $$ i $$ is $$ 1 $$ then $$ rent[1] = 35000 , size[1] = 1200, bhk[1] = 3, age[1] = 10$$.

The variables $$ \theta_1 , \theta_2 $$ and $$ \theta_3 $$ are called weights. You can think of them as the importance each feature plays in the final price of the house. For example if the No. of Bedrooms is more important in deciding the rent than the age of the house then $$ \theta_2 > \theta_3 $$ but if the size of the House is the biggest deciding factor than anything else then $$ \theta_1 > \theta_2 > \theta_3 $$.

Now our goal is to find the values of the Three weights 

<strong>One VERY important thing: </strong>The values of the weights are not unique to each individual example in our dataset. We have to find a value for the weights such that all the examples in our dataset obey the equation stated above.

## Finding the Weights

I'm going to convert all the examples in our dataset into an equation form

Equation 1 : $$ 35000 = 1200(\theta_1) + 3(\theta_2) + 10(\theta_3) $$

Equation 2 : $$ 14000 = 600(\theta_1) + \theta_2 + 5(\theta_3) $$

Equation 3 : $$ 25000 = 1200(\theta_1) + 2(\theta_2) + 10(\theta_3) $$

Equation 4 : $$ 37000 = 1800(\theta_1) + 3(\theta_2) + \theta_3 $$

Equation 5 : $$ 10000 = 435(\theta_1) + \theta_2 + 10(\theta_3) $$

### Method 1 - Solving via Substitution

<strong>SPOILER ALERT - It won't work</strong>

We could use some high school algebra to find the values of the Three weights right? There are atleast three equations we could use from the set of 5 find the respective weights but there is no guarantee that the values we get would fit for the entire dataset. 

Keep in mind that real life datasets are in the order of ten thousands so localizing your solution to just a few is a terrible way to go ahead. 

Also there is no guarantee that the set of equations are solvable either. So there are too many obstacles to face and hence treating the problem of finding weights as a simple solve for the weights by substitution is not the way to go ahead.











