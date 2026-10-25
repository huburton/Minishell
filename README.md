# Minishell

A small Unix shell written in C, modelled on bash. School 19 (42 network) project, built in a pair.

```text
$ ./minishell
minishell> echo "hello $HOME" | tr a-z A-Z
HELLO /HOME/USER
minishell> export X=42
minishell> echo $X
42
minishell> ls nope
ls: cannot access 'nope': No such file or directory
minishell> echo $?
2
minishell> cat << EOF | wc -l
> a
> b
> EOF
2
minishell> exit
```

## Features

- Interactive prompt with history (GNU readline).
- Runs programs found through `PATH`, or by absolute or relative path (`fork` + `execve`).
- Pipelines of any length (`|`), wired with `pipe` and `dup2`.
- Redirections: `<`, `>`, `>>` and heredoc `<<`.
- Single quotes (no interpretation) and double quotes (only `$` is expanded).
- Expansion of environment variables and of the last exit status `$?`.
- Signals like bash: `Ctrl-C` gives a new prompt, `Ctrl-D` exits, `Ctrl-\` does nothing at the prompt.
- Built-ins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit [code]`.

## Layout

| Path | Role |
|---|---|
| `src/parsing/` | tokenizer, quote removal, variable expansion, heredoc |
| `src/exec/` | process creation, pipes and redirections, `execve` |
| `src/builtin/` | the built-in commands |
| `src/utils/` | errors, memory cleanup, signal handlers |
| `libft/` | my own C utility library (strings, lists, printf) |

About 2,300 lines of C, compiled with `-Wall -Wextra -Werror`, following the school's coding norm
(functions of 25 lines max, no `for`, no global state except one signal flag).

## Build

Needs a C compiler, `make` and the readline development package (`libreadline-dev` on Debian/Ubuntu).

```bash
make
./minishell
```
