# Eigen Solver with  Subspace Iteration Method

## Task

Implementation to get the eigen values with Subspace Iteration Method

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is a square matrix of size NxN in one file *f1*

- *f1*: Square matrix with size $N x N$.

```
4 4
6.0000000000 -1.0000000000 -1.0000000000 4.0000000000
-1.0000000000 -10.0000000000 2.0000000000 -1.0000000000
-1.0000000000 2.0000000000 8.0000000000 -1.0000000000
4.0000000000 -1.0000000000 -1.0000000000 -5.0000000000
```

``` bash
$ make run f1=[matrix_path]
```

Example:

``` bash
$ make run f1=../inputs/M_MEDIUM.txt
```

### Output

The solution through standard output

Example

```
Eigen Values
-10.3710438740 -0.0000000000 0.0000000000 0.0000000000
-0.0000000000 9.2688664888 -0.0000000000 -0.0000000000
0.0000000000 -0.0000000000 6.3568139827 0.0000000000
0.0000000000 -0.0000000000 0.0000000000 -6.2546365975

Eigen Vectors
0.0168782711 -0.5486543461 0.7754166702 -0.3121258080
0.9833352317 0.1225974752 0.0115027924 -0.1337511379
-0.0978440936 0.7976799725 0.5917778752 0.0627067875
0.1522940555 -0.2183000895 0.2199900445 0.9384859998
```

## Other options

``` bash
$ make help
```
