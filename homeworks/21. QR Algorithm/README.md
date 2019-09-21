# Eigen Solver with QR Method

## Task

Implementation to get the eigen values with QR Algorithm.

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is a square matrix of size NxN in one file *f1*

- *f1*: Square matrix with size $N x N$.

```
3 3
4.0000000000 -14.0000000000 -12.0000000000
-14.0000000000 10.0000000000 13.0000000000
-12.0000000000 13.0000000000 1.0000000000
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
31.5356896726 -0.0000000000 -0.0000000000
-0.0000000000 -9.6436646651 -0.0000000000
-0.0000000000 -0.0000000000 -6.8920250074
```

## Other options

``` bash
$ make help
```
