---
layout: post
title: "Stages of Compiling C Programs"
ecverpt: "Understanding the process of converting high level languages into machine code"
date: 2018-04-02 22:00:00
---

A computer's CPU does not understand high level languages such as C, Rust or English. Only two numbers make sense to the CPU, zeroes and ones. In this post we're going to understand how compilers like GCC make it easier for programmers to write and focus only on writing high level code while taking care of making the CPU understand that code.

We're going to be using GNU's compiler collection (GCC) as our C compiler.

###Input program

To keep things simple, we're going to use a simple hello world program as shown below

{%highlight c %}
/* helloWorld.c */

#include <stdio.h>

int main()
{
	printf("Hello World");
	return 0;
}
{% endhighlight %}

##Stage 1 - Preprocessing 
