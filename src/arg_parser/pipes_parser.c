/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:25:03 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:28:19 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	duplicate_args(char **argv, int i, t_pipes_init *pipes_init,
		char ***pipes_args)
{
	pipes_args[pipes_init->pipe_nb][pipes_init->args_count] = NULL;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
		{
			i++;
			return (i);
		}
		pipes_args[pipes_init->pipe_nb][pipes_init->pipe_arg]
			= ft_strdup(argv[i]);
		pipes_init->pipe_arg++;
		i++;
	}
	return (i);
}

static	int	fill_pipes_args(char ***pipes_args, char **argv)
{
	int				i;
	t_pipes_init	pipes_init;

	i = 0;
	pipes_init.pipe_nb = 0;
	while (argv[i])
	{
		pipes_init.args_count = 0;
		pipes_init.pipe_arg = 0;
		pipes_init.args_count = count_pipe_args(argv, i);
		pipes_args[pipes_init.pipe_nb] = malloc(sizeof(char *)
				* (pipes_init.args_count + 1));
		if (!pipes_args[pipes_init.pipe_nb])
			return (-1);
		i = duplicate_args(argv, i, &pipes_init, pipes_args);
		pipes_init.pipe_nb++;
	}
	return (0);
}

static int	init_pipes_data(t_pipes_data *pipes_data, int pipes_count)
{
	int		i;

	pipes_data->pipes_count = pipes_count;
	pipes_data->fork = malloc(sizeof(t_fork *) * (pipes_count + 1));
	if (!pipes_data->fork)
		return (1);
	i = 0;
	while (i <= pipes_count)
	{
		pipes_data->fork[i] = malloc(sizeof(t_fork));
		if (!pipes_data->fork[i])
			return (1);
		pipes_data->fork[i]->redirections = malloc(sizeof(t_redirections));
		if (!pipes_data->fork[i]->redirections)
			return (1);
		set_default_redirections(pipes_data->fork[i]);
		i++;
	}	
	return (0);
}

static void	parse_argument(char ***pipes_args,
		t_pipes_data *pipes_data, int i)
{
	pipes_data->fork[i]->redirections->fork_index = i;
	pipes_args[i] = handle_infile_redirection(pipes_args[i],
			pipes_data->fork[i]->redirections);
	if (pipes_data->fork[i]->redirections->in_redir_type == 2)
		ft_heredoc(pipes_data->fork[i]);
	pipes_args[i] = handle_outfile_redirection(pipes_args[i],
			pipes_data->fork[i]->redirections);
	remove_quotes(pipes_args[i]);
}

char	***pipes_parser(char **argv, t_pipes_data *pipes_data)
{
	char	***pipes_args;
	int		pipes_count;
	int		i;

	pipes_count = count_pipes(argv);
	if (pipes_count)
		pipes_data->pipes_detected = TRUE;
	pipes_args = malloc (sizeof(char **) * (pipes_count + 2));
	if (!pipes_args)
		return (NULL);
	pipes_args[pipes_count + 1] = NULL;
	fill_pipes_args(pipes_args, argv);
	init_pipes_data(pipes_data, pipes_count);
	i = 0;
	while (pipes_args[i])
	{
		parse_argument(pipes_args, pipes_data, i);
		i++;
	}
	return (pipes_args);
}
