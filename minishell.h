/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:39:37 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/13 18:39:37 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/libft.h"

extern int	g_signal_status;

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	char			**args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmds;
	int		exit_code;
}				t_data;

bool	empty_line(char *line);
bool	check_pipe(t_token *tokens);
bool	open_quote(char *line, t_data *data);
char	**free_env(char **env);
t_token	*free_tokens(t_token *head);
t_cmd	*free_cmds(t_cmd *head);
void	free_all(t_data data, int exit_code);
t_cmd	*append_free(t_cmd *cmd_list, t_cmd *current_cmd);
t_token	*tokenize(const char *input);
t_cmd	*build_cmds(t_token *tokens, t_data data);
bool	expand(t_token *tokens, t_data data);
char	*expand_variables(const char *input, t_data data);
char	*replace_dollar(char *result, const char *input, int *i, t_data data);
char	*ft_strjoin_substr(char *s1, const char *input, int i);
char	*ft_strjoin_free(char *s1, char *s2);
void	remove_str_quotes(char *str);
bool	expand2(t_token *tokens, t_data data);
void	append_token(t_token **head, t_token *new);
void	append_cmd(t_cmd **head, t_cmd *new);
bool	check_file(t_token *tokens, t_cmd *cmd, t_data data);
void	error_close_fd(t_token *tokens, t_cmd *cmd);
int		heredoc(t_data data, char *word);
void	setup_signals(void);
void	setup_signals2(void);
bool	is_valid(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_sort_array(char **env);
char	**make_env(char **env);
char	*get_env_value(char *name, char **env);
bool	is_space(char c);
void	check_reg(char *path, char *cmd, t_data data);
char	*found_cmd(char *paths, char *cmd, char *full, t_data data);
void	print_error(char *str);
void	print_error_cmd(char *str);
void	print_error_tok(t_token_type type);
int		exec_cmd(t_cmd *cmd, t_data *data);
bool	is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_data *data);
int		exec_builtin_redir(t_cmd *cmd, t_data *data);
void	close_fd(t_cmd *cmd);
void	parent_process(t_cmd *cmd, int *pipe_fd, int *prev_fd);
int		pipe_err(int prev_fd);
int		fork_err(t_cmd *cmd, int *pipe_fd, int prev_fd);
char	*resolve_path(char *cmd, t_data data);
int		ft_cd(char ***env, char **args);
int		ft_echo(char **str);
int		ft_env(char **env);
int		ft_exit(char **str, t_data data);
void	ft_exit_pipe(char **str, t_data data);
bool	ft_export_str(char *str, char ***env);
int		ft_export(char **str, char ***env);
int		ft_pwd(void);
int		ft_unset(char **str, char ***env);
bool	has_equal_sign(char *str);
bool	is_append_mode(char *str);
char	*handle_append_mode(char *str, char *existing);

#endif
