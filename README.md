# jsh
A simple shell based on [write a shell in c](https://brennan.io/2015/01/16/write-a-shell-in-c/), but built by modern c++ instead.

Currently jsh implements the similar function in lsh. In the future more features will be added.

Extra features compared to lsh:

+ use arrow keys to manipulate cursor and switch to history command
+ more builtins: `cd`、`help`、`exit`、`history`


## Dependence
+ boost
+ libreadline-dev

## Build
Simply run `make`. Target files are in `target` directory.

## Run
Run `make run` or `./target/jsh`
