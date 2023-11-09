/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:02:12 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/12 16:08:03 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	triggered(int check, int *trigger, int stdin_fd)
{
	if (check == 0)
	{
		close(stdin_fd);
		*trigger = 0;
	}
	if (*trigger == 1)
		ft_putstr_fd("> ", 1);
}

void	heredoc_file_access(t_data *d)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;
	int		trigger;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd == -1)
		exit_error(msg("here_doc", ": ", strerror(errno), 1), d);
	line = "";
	trigger = 1;
	while (line)
	{
		triggered(1, &trigger, stdin_fd);
		line = get_next_line(stdin_fd);
		if (line == NULL)
			break ;
		if (ft_strlen(d->av[2]) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, d->av[2], ft_strlen(d->av[2] + 1)))
			triggered(0, &trigger, stdin_fd);
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
}

void	in_file_access(t_data *datastruct)
{
	if (datastruct->heredoc == 1)
	{
		heredoc_file_access(datastruct);
		datastruct->fd_in = open(".heredoc.tmp", O_RDONLY);
		if (datastruct->fd_in == -1)
			exit_error(msg("error with the here_doc", ": ",
					strerror(errno), 1), datastruct);
	}
	else
	{
		datastruct->fd_in = open(datastruct->av[1], O_RDONLY, 0644);
		if (datastruct->fd_in == -1)
			msg(strerror(errno), ": ", datastruct->av[1], 1);
	}
}

void	out_file_access(t_data *datastruct)
{
	if (datastruct->heredoc == 1)
		datastruct->fd_out = open(datastruct->av[datastruct->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		datastruct->fd_out = open(datastruct->av[datastruct->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (datastruct->fd_out == -1)
		msg(strerror(errno), ": ", datastruct->av[datastruct->ac - 1], 1);
}
