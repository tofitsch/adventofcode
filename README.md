# Solutions to advent of code

[advent of code](https://adventofcode.com)

![progress](progress.pdf)

Each day has a folder containing 4 files:

 1. `input.txt` : the input data
 2. `solution.txt` : the true solutions of part1 (line 1) and part2 (line 2)
 3. `part1.*` : the script computing the solution to part1
 4. `part2.*` : the script computing the solution to part2

The scripts return just the solution, no other printout.
They are written in a different language for each year.
Here is how to run them:

## 2019: C++

```shell
g++ -std=c++20 -o x part1.cpp && ./x
```

## 2020: vim keystrokes

```shell
vim input.txt -s part1.vim 2>/dev/null
```

## 2021: vimscript

```shell
vim --cmd ':source part1.vim | quit'
```

or from within vim:

```
:so %
```

## 2022: AWK

```shell
awk -f part1.awk input.txt
```

## 2019: C++, bonus: vim keystrokes

`part1.cpp`: First, each problem is solved in C++ to confirm that my strategy works:

```shell
g++ -std=c++20 -o x part1.cpp && ./x
```

`part1.vim`: Then, as a bonus, I tried so solve some of them entirely in vim. This time I added comments (after TABs) to make them understandable (I'll go back to 2021 at some point to do that there too). To remove the comments and run the vim commands use the following script:

```shell
. ../../run_vim_macro.sh part1.vim input.txt
```

This will make a file `part1.vimc` of the macro without the comments and run it.
