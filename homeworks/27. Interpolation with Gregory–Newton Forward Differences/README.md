# Interpolation with Gregory-Newton Forward Differences

## Task

Implementation for polinomial interpolation using Gregory-Newton Forward Differences.

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

- *f3*: Value of distince h between each x

```
4 1

2
0
2
68
```

- *f4*: The path of the file with *x_samples* coordinates to evaluate


``` bash
$ make run f1=[x_dots_path] f2=[y_dots_path] f3=[h_value] f4=[x_values]
```

Example:

``` bash
$ make run f1=./x.in  f2=./y.in f3=0.25 f4=./x_samples.in
```

### Output

Generate a file called *y_samples.txt* with the polinomial evaluation for each value in *f4*


## Other options

``` bash
$ make help
```
