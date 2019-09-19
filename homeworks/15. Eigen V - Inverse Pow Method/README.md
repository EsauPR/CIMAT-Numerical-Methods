# Eigen Solver with Inverse Pow Method

## Task

Implementation to find the eigen values and eigen vector using the Inverse Pow Method

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is a square matrix in one file, *f1*

- *f1*: Square matrix with size $N x N$.

```
4 4

2.402822 4.425232 1.929374 1.370355
1.201411 2.212616 0.964687 0.685178
1.119958 0.964687 2.053172 0.566574
0.742142 0.685178 0.566574 1.696828
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
2.402822 4.425232 1.929374 1.370355
1.201411 2.212616 0.964687 0.685178
1.119958 0.964687 2.053172 0.566574
0.742142 0.685178 0.566574 1.696828

5290922.867794 -10581846.610143 -0.602503 3.672447
-1792383.492965 3584767.889953 -0.035834 -1.409393
-1767970.895007 3535941.842308 0.832539 -1.341029
-1000000.000082 2000000.000165 0.000000 0.000000

1.000000 -0.000000 0.000000 0.000000
0.000000 1.000000 0.000000 0.000000
0.000000 -0.000000 1.000000 0.000000
0.000000 -0.000000 0.000000 1.000000
```

## Other options

``` bash
$ make help
```
