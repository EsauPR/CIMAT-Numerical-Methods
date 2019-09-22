# Solver for a Square Matrix by Gaussian Elimination

## Task

Implementation to Solve a Matrix System by Gaussian Elimination.

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is the augmented matrix that represents the equations system splitted in two files  *f1* and *F2*

- *f1*: Square matrix with size $N x N$ that represents the firsts members for the equations system.

```
4 4

2.402822 4.425232 1.929374 1.370355
1.201411 2.212616 0.964687 0.685178
1.119958 0.964687 2.053172 0.566574
0.742142 0.685178 0.566574 1.696828
```

- *F2*: Matrix with size $N x 1$ that represents the seconds members for the equations system.

```
4 1

0.060000
0.542716
0.857204
0.761270
```

``` bash
$ make run f1=[matrix_path] f2=[matrix_path]
```

Example:

``` bash
$ make run f1=../inputs/M_SMALL.txt  f2=../inputs/V_SMALL.txt
```

### Output

Solution system through standard output

Example

```
2.402822 4.425232 1.929374 1.370355 0.060000
1.201411 2.212616 0.964687 0.685178 0.542716
1.119958 0.964687 2.053172 0.566574 0.857204
0.742142 0.685178 0.566574 1.696828 0.761270

X_1 = -5425480.766483
X_2 = 1837967.142749
X_3 = 1812934.000000
X_4 = 1025431.999682
```

## Other options

``` bash
$ make help
```
