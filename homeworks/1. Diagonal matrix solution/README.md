# Solver for a Diagonal Matrix

## Task

Implementation to Solve a Diagonal Matrix.

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

1.0 0.0 0.0 0.0
0.0 2.0 0.0 0.0
0.0 0.0 3.0 0.0
0.0 0.0 0.0 4.0
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
$ make run f1=../inputs/M_DIAG.txt f2=../inputs/V_DIAG.txt
```

### Output

Solution system through standard output

Example

```
1.000000 0.000000 0.000000 0.000000 1.000000
0.000000 2.000000 0.000000 0.000000 2.000000
0.000000 0.000000 3.000000 0.000000 3.000000
0.000000 0.000000 0.000000 4.000000 4.000000

X_1 = 1.000000
X_2 = 1.000000
X_3 = 1.000000
X_4 = 1.000000

Determinant: 24.000000
```

## Other options

``` bash
$ make help
```
