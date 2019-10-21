# Hermite polinomial interpolation

## Task

Implementation for polinomial interpolation using Hermite method.

## Compilation

``` bash
$ make
```

## Execution

### Input

The are 4 parameters that will be used

- *f1*: The path of the file with *x* coordinates in vector format

```
4 1

-1
0
1
2
```

- *f2*: The path of the file with *y* coordinates in vector format

```
4 1

2
2
2
26
```

- *f3*: The path of the file with *dy* coordinates in vector format

```
4 1

2
0
2
68
```

- *f4*: *Start* point in x to begin the evaluation

- *f5*: *End* point in x to begin the evaluation

``` bash
$ make run f1=[x_dots_path] f2=[y_dots_path] f3=[start] f4=[end]
```

Example:

``` bash
$ make run f1=./x.in  f2=./y.in f3=./dy.in f4=-10 f5=10
```

### Output

Generate a file called *samples.txt* with the polinomial evaluation form the start to end points with increments of 0.1


## Other options

``` bash
$ make help
```
