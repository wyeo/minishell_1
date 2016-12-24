/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 08:27:18 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/17 18:13:45 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

int			ft_get_cmd(t_data *data)
{
	int		i;
	int		j;
	char	*res;

	if (get_next_line(0, &data->prompt) == 0)
	{
		ft_bye();
		exit(0);
	}
	if (data->prompt[0] == 12)
	{
		if ((res = tgetstr("cl", NULL)) == NULL)
			return (-1);
		tputs(res, 0, ft_outc);
		data->returned = 0;
	}
	if (ft_strchr(data->prompt, ';'))
	{
		i = 1;
		j = 0;
		data->multi_cmd = ft_strsplit(data->prompt, ';');
		while (data->multi_cmd[i])
			i += 1;
		i -= 1;
		while (j < i)
			data->returned = system(ft_strtrim(data->multi_cmd[j++]));
		data->prompt_table = ft_strsplit(ft_strtrim(data->multi_cmd[i]), ' ');
	}
	else
	{
		data->prompt_table = ft_strsplit(ft_strtrim(data->prompt), ' ');
		if (data->prompt_table[0] && data->prompt_table[1])
			data->prompt_table[1] = ft_strtrim(data->prompt_table[1]);
	}
	return (0);
}

void		ft_print_tab(char **bat)
{
	int		i;

	i = 0;
	while (bat[i])
	{
		ft_putendl(bat[i]);
		i += 1;
	}
}
