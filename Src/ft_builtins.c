/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 08:53:40 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/19 16:15:22 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_env(t_data *data, t_liste *liste)
{
	if (data->prompt_table[0] && !data->prompt_table[1])
	{
		if (ft_strcmp(data->prompt_table[0], "env") == 0)
		{
			ft_affiche_liste(liste->first);
			data->returned = 0;
			return (-1);
		}
	}
	return (0);
}

int		ft_setenv(t_data *data, t_liste *liste)
{
	int			i;

	i = 0;
	while (data->prompt_table[i])
		i += 1;
	if (data->prompt_table[0])
	{
		if ((ft_strcmp(data->prompt_table[0], "setenv") == 0) && (i == 4))
		{
			ft_setenv_junior(data, liste);
			data->returned = 0;
			return (-1);
		}
		if ((ft_strcmp(data->prompt_table[0], "setenv") == 0) && (i != 4))
		{
			ft_putendl("setenv: Wrong arguments (Man setenv)");
			data->returned = -1;
			return (-1);
		}
	}
	return (0);
}

int		ft_unsetenv(t_data *data, t_liste *liste)
{
	int			pos;
	int			len;

	pos = 0;
	len = 0;
	if (data->prompt_table[0]
			&& ft_strcmp(data->prompt_table[0], "unsetenv") == 0)
	{
		if (data->prompt_table[1])
		{
			len = ft_strlen(data->prompt_table[1]);
			if (ft_check_exist(data, liste, len) == 0)
			{
				data->returned = -1;
				return (-1);
			}
			else if (ft_check_exist(data, liste, len) == 1)
			{
				pos = ft_check_position(data, liste);
				data->returned = ft_supp_liste(liste, pos);
				return (-1);
			}
		}
	}
	return (0);
}

int		before_equal(char *str)
{
	int		i;

	i = 0;
	if (str[i])
	{
		while (str[i] != '=' && str[i] != '\0')
			i += 1;
	}
	return (i);
}

int		ft_check_position(t_data *data, t_liste *liste)
{
	int				pos;
	int				len;
	t_element		*courant;

	pos = 0;
	courant = liste->first;
	data->prompt_table[1] = ft_strjoin(data->prompt_table[1], "=");
	if (!data->prompt_table[1])
		return (-1);
	len = ft_strlen(data->prompt_table[1]);
	while (courant->next != NULL)
	{
		if (ft_strncmp(data->prompt_table[1], courant->val, len) == 0)
			return (pos);
		pos += 1;
		courant = courant->next;
	}
	return (0);
}

int		ft_check_exist(t_data *data, t_liste *liste, int len)
{
	t_element	*courant;

	courant = liste->first;
	while (courant->next != NULL)
	{
		if (ft_strncmp(data->prompt_table[1], courant->val, len) == 0)
			return (1);
		courant = courant->next;
	}
	return (0);
}

int		ft_setenv_junior(t_data *data, t_liste *liste)
{
	char	*str;
	int		len_before;

	len_before = before_equal(data->prompt_table[1]);
	if (!(str = (char *)malloc(sizeof(char) * len_before)))
		return (-1);
	if (ft_check_exist(data, liste, len_before) == 1 && len_before != 1)
		ft_yes_exist(data, liste);
	else
	{
		str = ft_strcpy(str, data->prompt_table[1]);
		str = ft_strjoin(str, "=");
		str = ft_strjoin(str, data->prompt_table[2]);
		ft_add_elem(str, liste);
	}
	return (0);
}

int		ft_yes_exist(t_data *data, t_liste *liste)
{
	int			val;
	int			len;
	char		*str;
	t_element	*tmp;
	t_element	*courant;

	tmp = NULL;
	courant = liste->first;
	len = before_equal(data->prompt_table[1]);
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (-1);
	str = ft_strcpy(str, data->prompt_table[1]);
	str = ft_strjoin(str, "=");
	str = ft_strjoin(str, data->prompt_table[2]);
	val = ft_atoi(data->prompt_table[3]);
	if (val != 0)
	{
		while (courant->next != NULL)
		{
			if (ft_strncmp(data->prompt_table[1], courant->val, len) == 0)
			{
				tmp = courant->next;
				free(courant->val);
				courant->val = ft_strdup(str);
				courant->next = tmp;
			}
			courant = courant->next;
		}
	}
	return (0);
}
