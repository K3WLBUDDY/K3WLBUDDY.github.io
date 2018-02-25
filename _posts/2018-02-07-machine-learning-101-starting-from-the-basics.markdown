---
layout: post
title:  "Machine Learning 101 - Starting from the Basics"
excerpt: "Understanding the building blocks of the Machine Learning world"
date:   2018-02-07 22:00:00
---
This is the first in a series of blog posts I'm calling <strong>"Machine Learning 101"</strong>. The main purpose of this series is for me to remind myself of things I've learnt ( I have the habit of forgetting things ) and help any noob understand a lot of things about Machine Learning. If you're new to ML and have absolutely no clue whatsoever about it then this is one of the places to start learning from. 

So, let's dive into ML - 101.

## Getting the intuition for Machine Learning

The first thing I'd want you to do is forget whatever you would've heard about Machine Learning. Words like CNN, LSTM, R-CNN etc. should mean nothing to you. We'll come to those topics in due time but for now the goal is to understand the basics of Machine Learning. 

I'm going to start off on a blank slate with a small example

Imagine you're the owner of a house and looking to rent it out to make some extra $$$ on the side. You're having a problem figuring out what the monthly rent should be. Ideally the rent shouldn't be too expensive so that nobody bothers about your place nor should it be too cheap so that you're making no cash from it. 

Now, when it comes to deciding the rent for a house, a lot of factors come into play. Things like the Square Feet occupied, the amenities provided like covered car parking etc. all play a role in the final price.

Our job for now is going to be: Given the necessary details about a house i.e Area, No. of Bedrooms etc., predict a reasonable rent for it.

The best way to define what "Reasonable Rent" means is to get details about the rental prices of other properties and extrapolate information from it.

And I've done just that by scraping 99acres.com and obtaining around 8000 properties and their rental information. Below you'll find a few of them. Analyze the data for a minute or two.

### Rental prices in Chennai

<table>
<tr>
<th>Area (sq.ft)</th>
<th>No. of Bedrooms (BHK)</th>
<th>Age (years)</th>
<th>Rent per month (&#x20b9;)</th>
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
<td>1000 </td>
<td>2</td>
<td>10</td>
<td>25000</td>
</tr>
<tr>
<td>1500</td>
<td>3</td>
<td>1</td>
<td>38000</td>
</tr>
<tr>
<td>435</td>
<td>1</td>
<td>10+</td>
<td>10000</td>
</tr>
</table>

The first thing to note is that the final rent depends on three <strong>features</strong> namely the Area, BHK and age. 

Each of the three features have some <strong>weight</strong> of say in the final price. You might give more weight/importance to the Area of the house while others might care more about the No. of bedrooms. The exact preferences of each individual doesn't matter here. What does matter is the overall weight contributed to the final rent of the house by each feature. 

Let's generalize that last sentence into a neat equation :

$$ rent[i] =  \theta_1 * size[i] + \theta_2 * bhk[i] + \theta_3 * age[i] $$

Here $$ i $$ refers to the i-th entry.

Converting our dataset into the above form we get:

Equation 1 : $$ 35000 = 1200(\theta_1) + 3(\theta_2) + 10(\theta_3) $$

Equation 2 : $$ 14000 = 600(\theta_1) + \theta_2 + 5(\theta_3) $$

Equation 3 : $$ 25000 = 1000(\theta_1) + 2(\theta_2) + 10(\theta_3) $$

Equation 4 : $$ 38000 = 1500(\theta_1) + 3(\theta_2) + \theta_3 $$

Equation 5 : $$ 10000 = 435(\theta_1) + \theta_2 + 10(\theta_3) $$

The variables $$ \theta_1 , \theta_2 $$ and $$ \theta_3 $$ are called weights. You can think of them as the importance each feature plays in the final price of the house. For example if the No. of Bedrooms is more important in deciding the rent than the age of the house then $$ \theta_2 > \theta_3 $$ but if the size of the House is the biggest deciding factor than anything else then $$ \theta_1 > \theta_2 > \theta_3 $$.

Now here's the important bit:

>Machine Learning is almost entirely about finding values of the weights 

<strong>NOTE: </strong>The values of the weights are not unique to each individual example in our dataset. We have to find a value for the weights such that all the examples in our dataset obey the equation stated above.


Hopefully by now you have a very small-ish idea of what Machine Learning is about.

## Finding the Weights - <a href="https://www.youtube.com/watch?v=uL0ROeZw7wA">How hard can it be?</a>

To make life easier for us I'm going to remove two features from our dataset and have just the Area of each house as the lone feature.

This is what our dataset looks like now:

<table>
<tr>
<th>Area (sq.Ft)</th>
<th>Rent per month (&#x20b9;)</th>
</tr>
<tr>
<td>1200</td>
<td>35000</td>
</tr>
<tr>
<td>600</td>
<td>14000</td>
</tr>
<tr>
<td>1000</td>
<td>25000</td>
</tr>
<tr>
<td>1500</td>
<td>38000</td>
</tr>
<tr>
<td>435</td>
<td>10000</td>
</tr>
</table>

(You can get the complete datset of 8000 properties <a href = "https://raw.githubusercontent.com/K3WLBUDDY/K3WLBUDDY.github.io/master/datasets/housingPrices.csv ">here</a>)

Our equations will now become : 

Equation 1 : $$ 35000 = 1200(\theta_1) $$

Equation 2 : $$ 14000 = 600(\theta_1)  $$

Equation 3 : $$ 25000 = 1000(\theta_1)  $$

Equation 4 : $$ 38000 = 1500(\theta_1) $$

Equation 5 : $$ 10000 = 435(\theta_1)  $$

Now let's tackle the biggie : Finding the value of $$\theta_1$$

### Method 1 : Solving by substitution 

One easy way to find the value of $$\theta_1$$ would be to just solve the equations. They technically are linear equations in just one variable right?

Problem is we want our value of $$\theta_1$$ to fit all our examples. Not just one. Let me illustrate more by solving the equations.

By solving Equation 1, the value of $$\theta_1$$ will become $$29.16$$. Let's plug that into Equation 2 and see what happens.

$$ 14000 = 600(\theta_1)  $$

$$ RHS = 600(\theta_1) $$

$$     = 600 * 29.16 $$

$$     = 17496 $$

Welp. That didn't work obviously. The $$ RHS $$ we calculated is no way near the $$ LHS $$. 

You could say the <strong>error</strong> or the <strong>loss</strong> in our calcuation was $$ 17496 - 14000 $$ which is $$ 3496 $$.

After substituting the value of $$\theta_1$$ in all our equations the loss for each Equation turns out to be : 

Loss 1 = $$ 0 $$

Loss 2 = $$ 3496 $$

Loss 3 = $$ 4160 $$

Loss 4 = $$ 5740 $$

Loss 5 = $$ 2684.6 $$

That's pretty horrible in terms of accuracy. We need to find a way where we can assign values to our weight $$\theta_1$$ in a way that minimizes the loss for each and every individual example from our dataset as much as possible. It'd be pretty impossible to get a Loss of $$ 0 $$ for the entire dataset so we have to aim to obtain values for weights that would keep the loss as low as possible. 

### Method 2 - Randomly initializing values

No. Just no. Why? 

You could take an entire decade trying to find the correct combination of weights.

### Method 3 - The most commonly used method for finding weights 

Plotting our dataset we get the following graph : <img src ="https://i.imgur.com/RAD4qn5.jpg">