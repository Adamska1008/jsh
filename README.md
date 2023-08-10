# jsh
A simple shell based on [write a shell in c](https://brennan.io/2015/01/16/write-a-shell-in-c/), but built by modern c++ instead.

Currently jsh implements the similar function in lsh. In the future more features will be added.

Extra features compared to lsh:

+ use arrow keys to manipulate cursor and switch to history command
+ more builtins: `cd`、`help`、`exit`、`history`
+ support autocomplete
+ multiple line input

## Dependence
+ boost
+ libreadline-dev
+ [wildcards](https://github.com/zemasoft/wildcards)(single header)

## Building

```
git clone https://github.com/Adamska1008/jsh
cd jsh & make
```
## Run
Run `make run` or `./target/jsh`
