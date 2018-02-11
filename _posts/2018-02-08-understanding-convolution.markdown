---
layout: post
title:  "Understanding the Convolution Process"
excerpt: "A technical deep dive into what Convolution is"
date:   2018-02-08 22:00:00
---

This is my first blog and a technical one at that. So please excuse me if the quality doesn't exactly blow your brains out. I'll try my best to keep improving as time goes by.

Soppy stuff aside let's get on with Convolution. 

### The Basics

I'd like to define something by first giving an example and deriving the definition intuitively from it.

So, here's a small example

Consider a time dependent function $$ f(t) $$. 

For the sake of this example let's assume the values of $$ f(t) $$ for $$ t $$ $$ \in \{0,1,2\} $$ as :

$$ f(0) = 2 $$

$$ f(1) = 3 $$

$$ f(2) = 1 $$

Plotting this as a graph we get :

<img src = "https://i.imgur.com/omRE7ju.jpg">

Now let's take up another time function, say $$ g(t) $$. Just as the previous function $$ g(t) $$ is also time dependent and we're going to assign some random values to it :

$$ g(0) = 2 $$

$$ g(1) = 1 $$

$$ g(2) = 0 $$

Plotting this we get :

<img src = "https://i.imgur.com/BfaKvwr.jpg">

So far we have two functions $$ f(t) $$ and $$ g(t) $$, both with some random values and more importantly both are <strong>dependent on time</strong>.

Did I tell you both the functions are time dependent? I guess I did. A lot of times. And with good reason for it too.

Now we're going to see what happens when we pass $$ g(t) $$ over $$ f(t) $$

Visualise <sub>(yeah, I follow the Brits)</sub> the graph of $$ f(t) $$ in your mind.

Now imagine the graph of $$ g(t) $$ sliding into your mind from the left. 

When the graphs of both the functions start to overlap you'll notice that $$ f(0) $$ is being overlapped by $$ g(2) $$. This isn't good as we want to see how the functions react with each other at the same time.

So let's just reflect our function $$ g(t) $$ so that for $$ t = \tau $$ the function  $$ f(\tau) $$ will be overlapped with $$ g(t-\tau) $$

Visually $$ g(t) $$ gets reflected as :

<img src = "https://screenshotscdn.firefoxusercontent.com/images/e879f1b2-8695-4427-b363-0c92bff844cb.png"> 

Now let's start the sliding process. We're going to keep $$ f(t) $$ stationary and move the reflected $$ g(t) $$ over it left to right.

Let's call the output $$ h(t) $$

$$ t = 0 $$ $$ f(0) $$ gets overlapped with $$ g(0) $$ the overall value of the output is going to be $$ f(0) * g(0) $$ which is equal to $$ 4 $$

In the next step $$ f(1) $$ gets overlapped with $$ g(0) $$ while $$ f(0) $$ gets overlapped with $$ g(1) $$. So the output is going to be $$ (f(0)*g(1)) + (f(1)*g(0)) $$
which is equal to $$ something $$

In the next step $$ f(2) $$ gets overlapped with $$ g(0) $$, $$ f(1) $$ with $$ g(1) $$ and $$ f(0) $$ gets overlapped with $$ g(2) $$

### Starting from the Basics - Convolution in 1D

