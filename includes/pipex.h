/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:14 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/18 09:51:25 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"

typedef struct s_data
{
	char	**env_path;
	char	**av;
	int		ac;
	int		heredoc;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	int		nb_cmds;
	int		child;
	int		*pids;
	char	**cmd_options;
	char	*cmd_path;
}		t_data;

char			*check_command(char *cmd, t_data *datastruct);
void			triggered(int check, int *trigger, int stdin_fd);
void			heredoc_file_access(t_data *datastruct);
void			in_file_access(t_data *datastruct);
void			out_file_access(t_data *datastruct);
char			**ft_split(char const *s, char c);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_free_strs(char **str, char **str2, char **str3);
void			*ft_malloc_zero(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*join_strs(const char *s1, const char *s2);
int				contains_newline(const char *s);
char			*get_before_newline(const char *s);
char			*get_after_newline(const char *s);
void			ft_read_line(int fd, char **keep, char **tmp);
char			*ft_parse_line(char **keep, char **tmp);
char			*get_next_line(int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				msg(char *str1, char *str2, char *str3, int errornb);
t_data			starter(int ac, char **av, char **env_path);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				check_empty_args(int ac, char **av);
void			close_fds(t_data *datastruct);
void			free_strs(char *str, char **strs);
void			exit_error(int error_status, t_data *datastruct);

#endif
