# Solver for a Lower Triangular Matrix

## Task

Implementation to Solve a Lower Triangular Matrix.

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is the augmented matrix that represents the equations system splitted in two files  *F1* and *F2*

- *F1*: Square matrix with size $N x N$ that represents the firsts members for the equations system.

```
4 4

1.0 0.0 0.0  0.0
2.0 3.0 0.0  0.0
4.0 5.0 6.0  0.0
7.0 8.0 9.0 10.0
```

- *F2*: Matrix with size $N x 1$ that represents the seconds members for the equations system.

```
4 1

1.0
2.0
3.0
4.0
```

``` bash
$ make run f1=[matrix_path] f2=[matrix_path]
```

Example:

``` bash
$ make run f1=../inputs/M_TINF.txt f2=../inputs/V_TINF.txt
```

### Output

Solution system through standard output

Example

```
1.000000 0.000000 0.000000 0.000000 1.000000
2.000000 3.000000 0.000000 0.000000 2.000000
4.000000 5.000000 6.000000 0.000000 3.000000
7.000000 8.000000 9.000000 10.000000 4.000000

X_1 = 1.000000
X_2 = 0.000000
X_3 = -0.166667
X_4 = -0.150000

Determinant: 180.000000
```

## Other options

``` bash
$ make help
```
