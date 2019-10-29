# Lagrange polinomial interpolation

## Task

Implementation for polinomial interpolation using Lagrange method.

## Compilation

``` bash
$ make
```

## Execution

### Input

The are 4 parameters that will be used

- *f1*: The path of the file with *x* coordinates in vector format

```
2 1

-10
10.0
```

- *f2*: The path of the file with *y* coordinates in vector format

```
2 1

95
95.0
```

- *f3*: *Start* point in x to begin the evaluation

- *f4*: *End* point in x to begin the evaluation

``` bash
$ make run f1=[x_dots_path] f2=[y_dots_path] f3=[start] f4=[end]
```

Example:

``` bash
$ make run f1=./x.in  f2=./y.in f3=-10 f4=10
```

### Output

Generate a file called *samples.txt* with the polinomial evaluation form the start to end points with increments of 0.1


## Other options

``` bash
$ make help
```
