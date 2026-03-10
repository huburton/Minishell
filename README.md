# 🐚 Minishell

> *As beautiful as a shell.*

**Minishell** est un projet de l'école 42 qui consiste à recréer un petit interpréteur de commandes en C, s'inspirant fortement de bash. Ce projet permet d'approfondir la compréhension des processus, des descripteurs de fichiers, de l'environnement, ainsi que l'utilisation de nombreuses fonctions systèmes.

---

## 🚀 Fonctionnalités

Le shell implémente les fonctionnalités essentielles suivantes :

- **Un prompt** affiché de manière interactive lors de l'attente d'une nouvelle commande.
- **Un historique de commandes fonctionnel**.
- **La recherche et l'exécution** du bon exécutable, que ce soit via la variable d'environnement `PATH`, un chemin absolu ou un chemin relatif.
- **La gestion des quotes** simples (`'`) qui empêchent l'interprétation des métacaractères, et des quotes doubles (`"`) qui interprètent uniquement les variables (`$`).
- **Les redirections** :
  - `<` : redirige l'entrée standard vers un fichier.
  - `>` : redirige la sortie standard vers un fichier.
  - `<<` (heredoc) : lit l'entrée jusqu'à rencontrer un délimiteur (sans être influencé par l'historique).
  - `>>` : redirige la sortie standard vers un fichier en mode "append".
- **Les pipelines (`|`)** : la sortie de chaque commande est connectée à l'entrée de la suivante via un système de pipes.
- **L'expansion de code de retour** (`$?`) et des variables d'environnement (`$VAR`).
- **La gestion des signaux** (`ctrl-C`, `ctrl-D` et `ctrl-\`) pour imiter le comportement de bash.

### 🛠️ Built-ins implémentés

Plusieurs commandes sont intégrées ("built-ins") directement dans le shell :
- `echo` avec la gestion de l'option `-n`
- `cd` avec chemin relatif ou absolu
- `pwd` sans paramètre optionnel
- `export` sans paramètre optionnel
- `unset` sans paramètre optionnel
- `env` sans paramètre optionnel ou argument
- `exit` avec potentiellement un code d'erreur (ex: `exit 42`)

---

## 📂 Architecture du projet

Le code source est organisé selon les étapes clés de vie du shell :

- `src/parsing/` : Gère le *Tokenizer*, le découpage de la commande utilisateur, la suppression des quotes, l'expansion des variables et le heredoc.
- `src/exec/` : Moteur d'exécution qui met en place les forks (processus enfants), gère les tubes (pipes) avec `dup2`, et remplace l'image du processus via `execve`.
- `src/builtin/` : Contient la logique interne de chaque built-in recodé.
- `src/utils/` : Rassemble les fonctions d'impression d'erreurs, de nettoyage de mémoire, et le paramétrage des signaux (`sigaction` / `signal`).
- `libft/` : Bibliothèque utilitaire en C (listes chaînées, fonctions de strings, etc.).

---

## 💻 Installation et Utilisation

### Prérequis
- Un compilateur C (`gcc` / `clang`)
- `GNU Make`
- La librairie système `readline`

### Compilation
Pour compiler l'exécutable, placez-vous à la racine et lancez `make` :
```bash
git clone https://github.com/thaygoo/Minishell.git
cd Minishell
make
```

### Lancement
Démarrez le mini-shell simplement avec l'exécutable :
```bash
./minishell
```

Une fois qu'il tourne, testez vos compétences en bash ! 🚀

---
*Projet réalisé dans le cadre du cursus de l'école 42.*