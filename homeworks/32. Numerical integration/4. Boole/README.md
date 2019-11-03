# Numerical integration for composite Boole rule

## Task

Implementation for numerical integration for composite Boole rule.

## Compilation

``` bash
$ make
```

## Execution

### Input

The are 3 parameters that will be used

- *f1*: Start point: X0

- *f2*: End point: Xm

- *f3*: Number of intervals: m

``` bash
$ make run f1=[x_dots_path] f2=[y_dots_path] f3=[h_value] f4=[x_values]
```

Example:

``` bash
$ make run f1=0 f2=12.56637061435917295385 f3=20
```

### Output

Value of the defite integral sin(x+0.5)


## Other options

``` bash
$ make help
```
