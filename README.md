# Solutions to advent of code

[advent of code](https://adventofcode.com)

Each day has a folder containing 4 files:

 1. `input.txt` : the input data
 2. `solution.txt` : the true solutions of part1 (line 1) and part2 (line 2)
 3. `part1.*` : the script computing the solution to part1
 4. `part2.*` : the script computing the solution to part2

The scripts return just the solution, no other printout.
They are written in a different language for each year.
Here is how to run them:

## 2022: AWK

```shell
awk -f part1.awk input.txt
```

## 2021: vimscript

```shell
vim --cmd ':source part1.vim | quit'
```

or from within vim:

```
:so %
```

## 2020: vim keystrokes

```shell
vim -c "norm `<part1.vim`" input.txt 2>/dev/null
```

## 2019: C++

```shell
g++ -o x part1.cpp && ./x
```
