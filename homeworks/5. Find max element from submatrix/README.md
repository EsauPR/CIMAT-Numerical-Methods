# Find the max element into a matrix

## Task

Implementation to find the maximun element into a matrix

## Compilation

``` bash
$ make
```

## Execution

### Input
The executable input is a square matrix in one file, *f1*

- *f1*: Square matrix with size $N x N$.

Example input:

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
$ make run f1=../inputs/M_SMALL.txt
```

### Output

Solution through standard output

Example

```
2.402822 4.425232 1.929374 1.370355
1.201411 2.212616 0.964687 0.685178
1.119958 0.964687 2.053172 0.566574
0.742142 0.685178 0.566574 1.696828

The element with the highest absolute value is: 4.425232, in (1, 2)
```

## Other options

``` bash
$ make help
```
