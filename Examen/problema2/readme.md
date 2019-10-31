# Problema 1

Resolución de sistema Ax=b con diversos métodos

## Compilación

## Compiles the executable program by default main.c

### Método de Gauss

```
$ make gauss
```

### Método de Doolittle

```
$ make doolittle
```

### Métodod de Choolesky

```
$ make choolesky
```


### Método de Jacobi

```
$ make jacobi
```

### Método de Gauss Seidel


```
$ make gauss_seidel
```

### Método de Gradiente

```
$ make gradient
```

## Ejecución


### Método de Gauss

```
$ ./gauss ../A_5000.mtx ../b_5000.vec
```

### Método de Doolittle

```
$ ./doolittle ../A_5000.mtx ../b_5000.vec
```

### Métodod de Choolesky

```
$ ./choolesky ../A_5000.mtx ../b_5000.vec
```


### Método de Jacobi

```
$ ./jacobi ../A_5000.mtx ../b_5000.vec
```

### Método de Gauss Seidel


```
$ ./gauss_seidel ../A_5000.mtx ../b_5000.vec
```

### Método de Gradiente

```
$ ./gradient ../A_5000.mtx ../b_5000.vec
```


## Salida

- Un archivo con el nombre x_[method].vec con la solución calculada.

Nota: Ya existe un archivo con la solución general llamado *X_5000.vec*
