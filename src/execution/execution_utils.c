/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:11 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:26:11 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_fork_stdout(t_fork *cur_fork)
{
	if (cur_fork->redirections->outfile)
	{
		if (cur_fork->redirections->out_redir_type == 1)
			cur_fork->redirections->fd_out
				= open(cur_fork->redirections->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cur_fork->redirections->out_redir_type == 2)
			cur_fork->redirections->fd_out
				= open(cur_fork->redirections->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cur_fork->redirections->fd_out < 0)
		{
			perror(" ");
			exit (EXIT_FAILURE);
		}
		dup2(cur_fork->redirections->fd_out, STDOUT_FILENO);
	}
}

int	count_cur_fork_args(char **pipe_args)
{
	int	i;

	i = 0;
	while (pipe_args[i])
		i++;
	return (i);
}

char	**exec_builtin(char **argv, char **envp_l,
		int argc, t_pipes_data *pipes)
{
	if (pipes->fork[0]->redirections->in_redir_type)
		if (redirect_stdin(pipes) == ERROR)
			return (envp_l);
	if (pipes->fork[0]->redirections->outfile)
		if (redirect_stdout(pipes) == ERROR)
			return (envp_l);
	envp_l = builtins(argv, envp_l, argc, pipes);
	if (pipes->fork[0]->redirections->out_redirection)
		restore_stdout(pipes);
	if (pipes->fork[0]->redirections->in_redirection)
		restore_stdin(pipes);
	return (envp_l);
}

char	**builtins(char **argv, char **envp_l,
			int argc, t_pipes_data *pipes_data)
{
	if ((ft_strcmp(argv[0], "echo")) == 0)
		builtin_echo(argv);
	else if ((ft_strcmp(argv[0], "pwd")) == 0)
		builtin_pwd();
	else if ((ft_strcmp(argv[0], "cd")) == 0)
		g_return = builtin_cd(argv, envp_l, argc);
	else if ((ft_strcmp(argv[0], "export")) == 0)
		envp_l = builtin_export(envp_l, argv, argc);
	else if ((ft_strcmp(argv[0], "exit")) == 0)
		builtin_exit(argv, envp_l, pipes_data);
	else if ((ft_strcmp(argv[0], "env")) == 0)
		builtin_env(envp_l);
	else if ((ft_strcmp(argv[0], "unset")) == 0)
		envp_l = builtin_unset(envp_l, argv);
	return (envp_l);
}

int	cmd_is_builtin(char *cmd)
{
	if ((ft_strcmp(cmd, "echo")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "pwd")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "cd")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "export")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "exit")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "env")) == 0)
		return (1);
	else if ((ft_strcmp(cmd, "unset")) == 0)
		return (1);
	else
		return (0);
}
