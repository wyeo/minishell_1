/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 05:36:03 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/17 18:14:53 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	proceed(int const fd, char *buff, char *s[fd])
{
	char	*tmp;
	char	*p;
	int		i;

	i = 0;
	while (!(p = ft_strchr(s[fd], '\n')) &&
		(i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		tmp = s[fd];
		s[fd] = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	if (i == -1)
		return (-1);
	if (i == 0 && !p)
		return (0);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char	*s[256];
	char		*tmp;
	int			res;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);
	if (!s[fd])
		s[fd] = ft_strnew(1);
	if ((res = proceed(fd, buff, &*s)) == -1)
		return (-1);
	if (res == 0)
	{
		*line = s[fd];
		s[fd] = NULL;
		return (0);
	}
	*line = ft_strsub(s[fd], 0, ft_strchr(s[fd], '\n') - s[fd]);
	tmp = s[fd];
	s[fd] = ft_strdup(ft_strchr(s[fd], '\n') + 1);
	ft_strdel(&tmp);
	return (1);
}
