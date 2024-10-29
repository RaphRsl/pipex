/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:39 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/07 15:49:52 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **env_path)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env_path[i] != NULL && env_path[i][0] != '\0')
	{
		path = ft_strnstr(env_path[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

static char	**turn_into_path(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free_strs(tmp, NULL);
		i++;
	}
	return (paths);
}

static char	**get_env_paths(char **env_path)
{
	char	*env_path_str;
	char	**paths;

	env_path_str = get_env_path(env_path);
	if (!env_path_str)
		return (NULL);
	paths = ft_split(env_path_str, ':');
	free_strs(env_path_str, NULL);
	if (!paths)
		return (NULL);
	paths = turn_into_path(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_strs(NULL, paths);
			exit_error(msg("unexpected error", "", "", 1), NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_strs(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

char	*check_command(char *cmd, t_data *datastruct)
{
	char	**env_path_tmp;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	env_path_tmp = get_env_paths(datastruct->env_path);
	if (!env_path_tmp)
		return (NULL);
	cmd_path = get_cmd_path(cmd, env_path_tmp);
	if (!cmd_path)
		msg("Impossible to find the command", ": ",
			datastruct->av[datastruct->child + 2], 1);
	free_strs(NULL, env_path_tmp);
	return (cmd_path);
}
