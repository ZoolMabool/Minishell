/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_new_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:29 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:30 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_new_variables(char **argv, char **envp_l)
{
	int	i;
	int	new_vars;

	i = 1;
	new_vars = 0;
	while (argv[i])
	{
		if (argv[i][0] == '_' && argv[i][1] == '=')
		{
			i++;
			continue ;
		}
		if (check_syntax(argv[i]) == FALSE)
			print_error(argv[i]);
		else if (check_arg(envp_l, argv[i]) == -1)
			new_vars++;
		i++;
	}
	return (new_vars);
}
