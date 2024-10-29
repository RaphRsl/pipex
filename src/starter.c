/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:00:48 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/07 15:49:52 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_data	reset_struct(void)
{
	t_data	datastruct;

	datastruct.env_path = NULL;
	datastruct.ac = -1;
	datastruct.av = NULL;
	datastruct.heredoc = 0;
	datastruct.fd_in = -1;
	datastruct.fd_out = -1;
	datastruct.pipe = NULL;
	datastruct.nb_cmds = -1;
	datastruct.child = -1;
	datastruct.pids = NULL;
	datastruct.cmd_options = NULL;
	datastruct.cmd_path = NULL;
	return (datastruct);
}

static void	generate_pipes(t_data *datastruct)
{
	int	i;

	i = 0;
	while (i < datastruct->nb_cmds - 1)
	{
		if (pipe(datastruct->pipe + 2 * i) == -1)
			exit_error(msg("Pipe creation failed", "", "", 1), datastruct);
		i++;
	}
}

t_data	starter(int ac, char **av, char **env_path)
{
	t_data	datastruct;

	datastruct = reset_struct();
	datastruct.env_path = env_path;
	datastruct.ac = ac;
	datastruct.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		datastruct.heredoc = 1;
	in_file_access(&datastruct);
	out_file_access(&datastruct);
	datastruct.nb_cmds = ac - 3 - datastruct.heredoc;
	datastruct.pids = malloc(sizeof * datastruct.pids * datastruct.nb_cmds);
	if (!datastruct.pids)
		exit_error(msg("Error whith PIDS malloc: ", strerror(errno), "", 1),
			&datastruct);
	datastruct.pipe = malloc(sizeof * datastruct.pipe * 2
			* (datastruct.nb_cmds - 1));
	if (!datastruct.pipe)
		exit_error(msg("Error with PIPE malloc: ", strerror(errno), "", 1),
			&datastruct);
	generate_pipes(&datastruct);
	return (datastruct);
}
