/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:45:33 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/18 14:56:15 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_empty_args(int ac, char **av)
{
	int	compt;

	compt = 0;
	while (compt < ac)
	{
		if (av[compt] && av[compt][0] == '\0')
		{
			ft_putstr_fd("Empty value detected in arguments\n", 1);
			return (0);
		}
		compt++;
	}
	return (1);
}

static void	close_pipe_fds(t_data *datastruct)
{
	int	i;

	i = 0;
	while (i < (datastruct->nb_cmds - 1) * 2)
	{
		close(datastruct->pipe[i]);
		i++;
	}
}

void	close_fds(t_data *datastruct)
{
	if (datastruct->fd_in != -1)
		close(datastruct->fd_in);
	if (datastruct->fd_out != -1)
		close(datastruct->fd_out);
	close_pipe_fds(datastruct);
}

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	exit_error(int error_status, t_data *datastruct)
{
	if (datastruct)
	{
		close_fds(datastruct);
		if (datastruct->pipe != NULL)
			free(datastruct->pipe);
		if (datastruct->pids != NULL)
			free(datastruct->pids);
		if (datastruct->cmd_options != NULL || datastruct->cmd_path != NULL)
			free_strs(datastruct->cmd_path, datastruct->cmd_options);
	}
	if (datastruct->heredoc == 1)
		unlink(".heredoc.tmp");
	exit(error_status);
}
