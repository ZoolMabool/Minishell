/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:24:24 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:24:37 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chevrons(char *arg, int start)
{
	int	i;

	i = 0;
	while (is_chevron(arg[start]))
	{
		i++;
		start++;
	}
	return (i);
}

int	is_chevron(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	else
		return (FALSE);
}

int	is_chevron_alone(char **argv, int arg_index, char chevron_type)
{
	int	arg_len;

	arg_len = ft_strlen(argv[arg_index]);
	if (arg_len == 1 && argv[arg_index][0] == chevron_type
			&& argv[arg_index + 1])
		return (1);
	if (arg_len == 2 && (argv[arg_index][0] == chevron_type
		&& argv[arg_index][1] == chevron_type) && argv[arg_index + 1])
		return (2);
	return (FALSE);
}

int	get_filename_len(char *arg)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (arg[i] && !is_chevron(arg[i]))
		i++;
	while (arg[i] && is_chevron(arg[i]))
		i++;
	while (arg[i] && !is_chevron(arg[i]))
	{	
		i++;
		len++;
	}
	return (len);
}
