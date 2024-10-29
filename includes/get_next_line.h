/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:05 by rroussel          #+#    #+#             */
/*   Updated: 2023/07/07 15:26:28 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 9223372036854775806
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
void	ft_read_line(int fd, char **keep, char **tmp);
char	*ft_parse_line(char **keep, char **tmp);
char	*get_before_newline(const char *s);
char	*get_after_newline(const char *s);
int		contains_newline(const char *s);
char	*ft_strdup(const char *s1);
char	*join_strs(const char *s1, const char *s2);
void	*ft_malloc_zero(size_t count, size_t size);
void	ft_free_strs(char **str, char **str2, char **str3);

#endif
