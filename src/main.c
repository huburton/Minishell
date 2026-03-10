/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiascha <phiascha@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:39:48 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/16 23:48:03 by phiascha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_minishell(t_data *data, int i)
{
	char	*str;
	int		level;
	char	*joined;

	if (data->cmds->args[0] && !ft_strcmp(data->cmds->args[0], "./minishell"))
	{
		signal(SIGINT, SIG_IGN);
		str = get_env_value("SHLVL", data->env);
		if (!str)
			return ;
		level = ft_atoi(str) + i;
		str = ft_itoa(level);
		if (!str)
			return (print_error("Malloc error\n"));
		joined = ft_strjoin("SHLVL=", str);
		free(str);
		if (!joined)
			return (print_error("Malloc error\n"));
		ft_export_str(joined, &data->env);
		free(joined);
		data->cmds->next = free_cmds(data->cmds->next);
	}
	else
		setup_signals2();
}

static bool	process_tokens(t_token *tokens, t_data *data)
{
	if (!check_pipe(tokens))
	{
		data->exit_code = 2;
		free_tokens(tokens);
		return (false);
	}
	if (!expand(tokens, *data))
	{
		free_tokens(tokens);
		return (false);
	}
	data->cmds = build_cmds(tokens, *data);
	free_tokens(tokens);
	if (!data->cmds)
	{
		data->exit_code = 1;
		return (false);
	}
	new_minishell(data, 1);
	return (true);
}

static bool	ft_parsing(char *line, t_data *data)
{
	t_token	*tokens;

	if (open_quote(line, data))
		return (false);
	tokens = tokenize(line);
	free(line);
	if (!tokens)
	{
		data->exit_code = 1;
		print_error("Malloc error\n");
		return (false);
	}
	return (process_tokens(tokens, data));
}

static void	main_loop(t_data data)
{
	char	*line;

	while (1)
	{
		setup_signals();
		line = readline("minishell> ");
		if (!line)
			break ;
		if (g_signal_status != 0)
		{
			data.exit_code = g_signal_status;
			g_signal_status = 0;
		}
		if (empty_line(line))
			continue ;
		if (*line)
			add_history(line);
		if (!ft_parsing(line, &data))
			continue ;
		data.exit_code = exec_cmd(data.cmds, &data);
		new_minishell(&data, -1);
		free_cmds(data.cmds);
	}
	rl_clear_history();
	free_env(data.env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = make_env(env);
	if (!data.env)
	{
		print_error("Malloc error\n");
		return (1);
	}
	data.exit_code = 0;
	main_loop(data);
	printf("exit\n");
	return (0);
}
