/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 19:19:42 by yait-kad          #+#    #+#             */
/*   Updated: 2020/01/02 19:19:45 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// char	*ft_strdup(const char *src);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **line);
// char	*ft_strchr(char *c1, int c2);

#endif
