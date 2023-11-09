/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:45:25 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/18 14:55:41 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dupli2(int input, int output, t_data *datastruct)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		exit_error(1, datastruct);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		exit_error(1, datastruct);
	}
}

static void	child_process(t_data *datastruct)
{
	if (datastruct->child == 0)
		dupli2(datastruct->fd_in, datastruct->pipe[1], datastruct);
	else if (datastruct->child == datastruct->nb_cmds - 1)
		dupli2(datastruct->pipe[2 * datastruct->child - 2],
			datastruct->fd_out, datastruct);
	else
		dupli2(datastruct->pipe[2 * datastruct->child - 2],
			datastruct->pipe[2 * datastruct->child + 1], datastruct);
	close_fds(datastruct);
	if (datastruct->cmd_options == NULL || datastruct->cmd_path == NULL)
		exit_error(1, datastruct);
	if (execve(datastruct->cmd_path, datastruct->cmd_options,
			datastruct->env_path) == -1)
		exit_error(msg(datastruct->cmd_options[0], ": ", strerror(errno), 1),
			datastruct);
}

static int	parent_process(t_data *datastruct)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(datastruct);
	datastruct->child--;
	exit_code = 1;
	while (datastruct->child >= 0)
	{
		wpid = waitpid(datastruct->pids[datastruct->child], &status, 0);
		if (wpid == datastruct->pids[datastruct->nb_cmds - 1])
		{
			if ((datastruct->child == (datastruct->nb_cmds - 1))
				&& WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		datastruct->child--;
	}
	free(datastruct->pipe);
	free(datastruct->pids);
	return (exit_code);
}

static int	pipex(t_data *datastruct)
{
	int		exit_code;

	if (pipe(datastruct->pipe) == -1)
		exit_error(msg("Pipe error", ": ", strerror(errno), 1), datastruct);
	datastruct->child = 0;
	while (datastruct->child < datastruct->nb_cmds)
	{
		datastruct->cmd_options = ft_split(datastruct->av[datastruct->child + 2
				+ datastruct->heredoc], ' ');
		if (!datastruct->cmd_options)
			exit_error(msg("unexpected error", "", "", 1), datastruct);
		datastruct->cmd_path = check_command(datastruct->cmd_options[0],
				datastruct);
		datastruct->pids[datastruct->child] = fork();
		if (datastruct->pids[datastruct->child] == -1)
			exit_error(msg("Fork error", ": ", strerror(errno), 1), datastruct);
		else if (datastruct->pids[datastruct->child] == 0)
			child_process(datastruct);
		free_strs(datastruct->cmd_path, datastruct->cmd_options);
		datastruct->child++;
	}
	exit_code = parent_process(datastruct);
	if (datastruct->heredoc == 1)
		unlink(".heredoc.tmp");
	return (exit_code);
}

int	main(int ac, char **av, char **env_path)
{
	t_data	datastruct;
	int		exit_code;

	if (!(check_empty_args(ac, av)))
		return (1);
	if (ac < 5)
	{
		if (ac >= 2 && !ft_strncmp("here_doc", av[1], 9))
			return (msg("How to use the here_doc bonus part: ",
					"./pipex here_doc LIMITER cmd cmd1 file",
					"", 1));
		return (msg("How to use the pipex program: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2", "", 1));
	}
	else if (ac < 6 && !ft_strncmp("here_doc", av[1], 9))
		return (msg("How to use the here_doc bonus part: ",
				"./pipex here_doc LIMITER cmd cmd1 file", "", 1));
	if (!env_path || env_path[0][0] == '\0')
		exit_error(msg("Error: environment variables are not correct.",
				"", "", 1), &datastruct);
	datastruct = starter(ac, av, env_path);
	exit_code = pipex(&datastruct);
	return (exit_code);
}
