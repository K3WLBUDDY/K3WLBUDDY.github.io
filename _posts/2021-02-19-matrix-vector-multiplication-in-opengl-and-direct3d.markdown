---
layout: post
title:  "Matrix-Vector multiplication in OpenGL and Direct3D"
excerpt: "Taking a look at the differences in the semantics of matrix-vector multiplication between OpenGL and Direct3D"
date:   2021-02-17 22:00:00
---

This post contains some of my learnings while figuring out the workings of matrices in OpenGL and Direct3D.

I'll first go over some of the theory of matrix multiplication and then cover how this theory can be applied on matrices that are stored in computers.

## On Paper

### The Basics of Matrix multiplication

Since the rules of matrix multiplication is applicable to both matrix and vectors, I'll refer to both these objects as operands of matrix multiplications.

Let's assume two operands $$ A $$  and $$ B $$.These operands can be either matrices or vectors (a vector anyway is just a matrix with either a single row or a single column). Matrix multiplication between these operands is possible only if the following rule holds true:

If $$ A $$ has $$ m $$ rows and $$ n $$ columns (a $$ m \times n $$ matrix), $$ B $$ must have $$ n $$ columns.

If $$ B $$ were to be a $$ n \times p $$ matrix, $$ AB $$ would result in a $$ m \times p $$ matrix.

#### Multiplying Matrices with Vectors

There can only be two types of Vectors, a row vector or a column vector.
A row vector is a matrix with dimensions $$ 1 \times n $$ and a column vector has the dimensions $$ n \times 1 $$.

#### Pre-multiplication - Row Vectors

For row vectors, the vector needs to be pre multiplied with the matrix. If $$ M $$ is a matrix of dimensions $$ m \times n $$ and
$$ v $$ is a row vector of dimensions $$ 1 \times m $$, the matrix multiplication can be performed as:
$$ \bar{v} = vM $$

#### Post-multiplication - Column Vectors

For column vectors, the vector needs to be post multiplied with the matrix. If $$ M $$ is a matrix of dimensions $$ m \times n $$ and
$$ v $$ is a column vector of dimensions $$ n \times 1 $$, the matrix multiplication can be performed as:
$$ \bar{v} = Mv $$

### Matrix-Vector multiplication in Graphics

Matrix-Vector multiplications are used widely in Computer Graphics to transform 2D / 3D points in a 2D / 3D space.

One usage of a matrix-vector multiplication is to translate a vector in 3D space.

Consider a column vector $$ v = \begin{bmatrix}x \\ y \\ z \\ 1\end{bmatrix} $$. Let's say you want to move this vector to $$ \bar{v} = \begin{bmatrix}x + T_x \\ y + T_y \\ z + T_z \\ 1\end{bmatrix}  $$.

The transformation matrix that can achieve this is $$ M = \begin{bmatrix}1 & 0 & 0 & T_x \\ 0 & 1 & 0 & T_y \\ 0 & 0 & 1 & T_z \\ 0 & 0 & 0 & 1\end{bmatrix} $$

Since $$ v $$ is a column vector, the vector must be post multiplied to the matrix as $$ Mv $$.

But what if $$ v $$ is a row vector?

If $$ v = \begin{bmatrix}x & y & z & 1\end{bmatrix} $$, the transformation matrix becomes $$ \bar{M} = \begin{bmatrix}1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ T_x & T_y & T_z & 1\end{bmatrix}$$

This also proves that $$ Mv = v\bar{M} $$. Also worth noting is that $$ \bar{M} $$ is a transpose of $$ M $$.

#### Combining transformation matrices

Let's say you want to apply multiple matrix transformations to a vector. Taking the same column vector $$ v $$ as before, instead of just translating $$ v $$ by $$ T $$, we now also want to translate it once more by $$ \bar{T} $$ :

$$ v = \begin{bmatrix}x \\ y \\ z \\ 1\end{bmatrix} $$ is the original vector.

$$ \bar{v} = \begin{bmatrix}x + T_x \\ y + T_y \\ z + T_z \\ 1\end{bmatrix}  $$ is the first transformation of the vector we want.

$$ \overline{\overline{v}} = \begin{bmatrix}\bar{v}_x + \bar{T}_x \\ \bar{v}_y + \bar{T}_y \\ \bar{v}_z + \bar{T}_z \\ 1\end{bmatrix}  $$ is the second transformation.

Let's denote the matrices that achieve these transformations as $$ M $$ and $$ \bar{M} $$.

Logically, we'd first multiply $$ v $$ with $$ M $$ and multiply the result of this with $$ \bar{M} $$ to get our final translated vector.

On paper this would look like $$ \overline{\overline{v}} = vM\bar{M} $$.

But this will NOT WORK since we assumed our vectors to be column vectors at the beginning. And column vectors need to be post multiplied with matrices for the rules of matrix multiplication to apply.

Rather, we can apply the above multiplication order with row vectors.

For column vectors, the order needs to be reversed as:

$$ \overline{\overline{v}} = \bar{M}Mv $$.

This should cover the theory of matrices that apply in the logical world outside computers. Now let's see how this applies to computers.

## On a Computer

### Vectors

Vectors are stored as a one dimensional array of objects in computers. Since there is only one dimension, there is no concept
of a row or a column vector. This lack of concept not only finds its way into Graphics APIs like OpenGL, Direct3D, Vulkan and Metal, GPU Hardware too does not care about the distinction between row and column vectors and stores vectors as an array of objects.

### Matrices

The way computers store Matrices is similar to Vectors in that they are also stored as a one dimensional array of objects. What gets complicated here is the method in which a n-dimensional matrix on paper is converted to a one dimensional array.

There are two methods that computers use to store matrices:

#### Row major Ordering

In row major ordering, matrices are stored linearly row-wise. Consider a $$ 2 \times 2 $$ matrix $$ M = \begin{bmatrix}a & b \\ c & d\end{bmatrix}$$.

In row major, $$ M $$ will be stored as $$ abcd $$

#### Column major Ordering

In column major ordering, matrices are stored linearly column-wise.
The matrix $$ M $$ from above will be stored in column major as $$ acdb $$.

Programming languages such as C++ store matrices in row-major order but many Graphics APIs such as OpenGL and Direct3D default to reading and writing matrices in column major fashion. There are ways to modify this behaviour but each API has its own limitiations when it comes to interpreting matrices in row major fashion. The ordering used by the Graphics API needs to be considered before performing matrix math on Shaders.

I'll skip over row major ordering since getting intuition for this is pretty straightforward and I'll focus more on column major ordering.

Let's go back to our original example of translating a vector $$ v $$ to $$ \bar{v} $$.

The matrix we were using for the translation was $$ M = \begin{bmatrix}1 & 0 & 0 & T_x \\ 0 & 1 & 0 & T_y \\ 0 & 0 & 1 & T_z \\ 0 & 0 & 0 & 1 \end{bmatrix}$$

To translate the vector, we post multiply it to the matrix as $$ Mv $$.

If the matrix were read in column major fashion, the matrix would be stored as $$ 1 0 0 0 0 1 0 0 0 0 1 0 T_x T_y T_z 1 $$ and if this matrix was post multiplied with $$ v $$, we will not get the expected result since the first component of $$ \bar{v} $$ would be multiplied as $$ \begin{bmatrix} 1 & 0 & 0 & 0 \end{bmatrix}\begin{bmatrix} x \\ y \\ z \\ 1\end{bmatrix} $$ which results in $$ x $$ and not $$ x + T_x $$!!

This means that for our matrices to work in a column major system, we'll have to transpose the matrices before it is read in column major. With this transformation in place, the matrix math can now work as we've understood on paper.

Now let's look at the differences in how Graphics APIs and Shading languages interpret matrices.


#### OpenGL / GLSL

OpenGL defaults to loading matrices in column major order. The spec provides a transform parameter via the glUniformMatrix* set of APIs that when set to true, allows row major matrices to be transformed on the CPU before being read by the GPU in column major order so that the matrix math works as intended.

GLSL provides a layout(row_major) qualifier that can be applied to UBOs/SSBOs and any matrices declared in these blocks will be read in row major order. This qualifier does not apply for matrices declared as independent uniform variables and those are still loaded as column major.

GLSL's nomenclature for matrix types is also weird in that a variable of the type mat3x4 is considered as a matrix having 3 columns and 4 rows and NOT the other way round.

#### DirectX / HLSL

D3D also defaults to loading matrices in column major order. For some reason, most resources on the internet (looking at you StackOverflow) call out D3D as loading matrices in row-major order but that does not seem to be the case, atleast from my experiments with D3d11 and HLSL.

HLSL provides a global #pragma pack_matrix(row_major) that can be used to modify the ordering of matrices and this applies to all matrix variables.

### Ending notes

There's a lot of incorrect information and unnecessary complications when it comes to matrix multiplication and ordering. Some people (like me when I started learning graphics) associate the vector type with the storage ordering (using row vectors with row-major matrices and vice-versa) but that is outright confusing and incorrect.

All that matters is the matrix you're using. If your matrix is made to work with row-vectors, use premultiplication else postmultiplication is the way to go. When working with a cross API engine, make sure to stick to either row vectors or column vectors in your math library across all APIs and DOCUMENT IT!!

It could've also helped if the bazillion number of graphics APIs and their various versions could've decided on a standard for their matrix layouts and stick with it but ofcourse that didn't happen.

That's pretty much it for this post. Huge thanks to the OpenGL driver devs at Nvidia for being patient and answering all my dumb questions.





