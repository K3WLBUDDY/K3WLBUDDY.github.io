---
layout: post
title:  "Machine Learning 101 - Convolution and its misuse"
excerpt: "A technincal deep dive into what Convolution is and its screwed up usage in Machine Learning"
date:   2018-02-08 22:00:00
---


If you're a Computer Science student right now, you would've come across the term <strong>Machine Learning</strong> being thrown all around you. ML has taken over the position that was previously held by Cloud Computing; the position of the most marketed Buzz word used with the utmost disrespect for technical accuracy. 

And Oh boy isn't Machine Learning full of bullcrap made up by God knows who just to make the life of noobies that bit more difficult.

<strong> In this and the upcoming 2 or 3 posts we'll be tackling the first fallacy present in the Machine Learning Community : Convolutional Neural Networks</strong>

Now, CNNs are a thing of beauty. People use them to trick Computers into thinking that they have the same power as the human eye (and sometime <strong>even better</strong>).If you've seen computers tell what something in a Picture or a Video is, it's mostly a CNN spinning the wheels in the background. So let's start getting into CNN.

### The C in CNN - Convolutions 

Let's try to understand what Convolution exactly is. This will later on help us tackle other important details of how computers can act as a low key Human Eye.

We're going to start off with a small example. 

Consider a function $$ f(t) $$ where $$ t $$ stands for time. 

For this example we're going to consider only integer values for time i.e only the seconds and not milli or nanoseconds. In other words we're going to work only with discrete values of time.

Now let's assume the values of $$ f(t) $$ for $$ t $$ $$ \in \{0,1,2\} $$ as :

$$ f(0) = 2 $$

$$ f(1) = 3 $$

$$ f(2) = 1 $$

Plotting this as a graph we get :

<img src = "https://i.imgur.com/omRE7ju.jpg">

Now let's take up another time function, say $$ g(t) $$ and just as above we're going to assign some random values to it :

$$ g(0) = 2 $$

$$ g(1) = 1 $$

$$ g(2) = 0 $$

Plotting this we get :

<img src = "https://i.imgur.com/BfaKvwr.jpg">

So far we have two functions $$ f(t) $$ and $$ g(t) $$, both with some random values and more importantly both are <strong>dependent on time</strong>.

Did I tell you both the functions are time dependent? I guess I did. A lot of times. And with good reason for it too which we will come to in a bit.

Now we're going to see what happens when we pass $$ g(t) $$ over $$ f(t) $$

Visualise <sub>(yeah, I follow the Brits)</sub> the graph of $$ f(t) $$ in your mind.

Now imagine the graph of $$ g(t) $$ sliding into your mind from the left. 

When the graphs of both the functions start to overlap you'll notice that $$ f(0) $$ is being overlapped by $$ g(2) $$. Now this doesn't bode well for us because we are in time domain and so we need to know how both the functions react at the same instance. That means knowing what happens when $$ f(0) $$ reacts with $$ g(0) $$.


So let's just reflect our function $$ g(t) $$ as shown below:

This way when we slide the function over the the times remain constant for both the functions.

<img src = "https://i.imgur.com/Y18VuTT.jpg"> 

Now let's start the sliding process. We're going to keep $$ f(t) $$ stationary and move the reflected $$ g(t) $$ over it left to right.

Let's call the output $$ h(t) $$.

We're going to calcuate the value of the output by finding all the overlaps of both the functions at a particular time and multiply them

To help the visualisation I've created a small animation that you can watch here : 

<iframe width="480" height="270" src="https://www.youtube.com/embed/Jd_SpIOA85A" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Let's see what happens step by step : 

<strong>Step 1:</strong> When $$ t = 0 $$ the values of $$ f(0) $$ and $$ g(0) $$ overlap so we just multiply them to get the overall value for $$ h[0] $$ which is $$ 4$$


<strong>Step 2:</strong> When $$ t = 1 $$ the overlaps are $$ [f(0), g(1)], [f(1), g[0)] $$ thereby the output is $$ h[1] = [f(0) * g(1)] + [f(1) * g(0)] $$ which adds up to $$ 7 $$


We find the values of $$ h[2], h[3] and h[4] $$ in the same way; find the overlaps, multiply them and add.

What we just did is find the convolution of Two functions.

The convolution operation is denoted by a $$ * $$.

Let's derive a general formula for Convolution : 

Consider we have $$ n $$ distinct time values for which we're finding the example.





