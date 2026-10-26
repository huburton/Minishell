# Minishell

*[English version](README.md)*

Un petit shell Unix écrit en C, sur le modèle de bash. Projet de l'école 19 (réseau 42), réalisé en binôme.

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

## Fonctionnalités

- Invite interactive avec historique (GNU readline).
- Lancement des programmes trouvés par `PATH`, ou par chemin absolu ou relatif (`fork` + `execve`).
- Pipelines de longueur quelconque (`|`), câblés avec `pipe` et `dup2`.
- Redirections : `<`, `>`, `>>` et heredoc `<<`.
- Guillemets simples (aucune interprétation) et doubles (seul `$` est développé).
- Développement des variables d'environnement et du dernier code de retour `$?`.
- Signaux comme dans bash : `Ctrl-C` redonne une invite, `Ctrl-D` quitte, `Ctrl-\` ne fait rien à l'invite.
- Commandes internes : `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit [code]`.

## Organisation

| Dossier | Rôle |
|---|---|
| `src/parsing/` | découpage en jetons, retrait des guillemets, développement des variables, heredoc |
| `src/exec/` | création des processus, pipes et redirections, `execve` |
| `src/builtin/` | les commandes internes |
| `src/utils/` | erreurs, libération de la mémoire, gestionnaires de signaux |
| `libft/` | ma propre bibliothèque C (chaînes, listes, printf) |

Environ 2 300 lignes de C, compilées avec `-Wall -Wextra -Werror`, dans le respect de la norme de l'école
(fonctions de 25 lignes au plus, pas de `for`, aucune variable globale à part un indicateur de signal).

## Compilation

Il faut un compilateur C, `make` et le paquet de développement de readline (`libreadline-dev` sous Debian/Ubuntu).

```bash
make
./minishell
```
