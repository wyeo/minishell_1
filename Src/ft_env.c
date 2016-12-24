/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 05:45:08 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/16 22:26:01 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		len_double_table(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

int		ft_cpy_env(char **env, t_data *data)
{
	int		i;
	int		len;
	int		len_double;

	i = 0;
	len = 0;
	len_double = len_double_table(env);
	if (!(data->my_env = (char **)malloc(sizeof(char *) * len_double)))
		return (-1);
	while (env[i])
	{
		len = ft_strlen(env[i]);
		data->my_env[i] = (char *)malloc(sizeof(char) * len);
		data->my_env[i] = ft_strcpy(data->my_env[i], env[i]);
		i += 1;
	}
	data->my_env[i] = 0;
	return (0);
}

void	ft_get_env(char *elem, t_data *data)
{
	int		i;

	i = 0;
	while (ft_strncmp(data->my_env[i], elem, ft_strlen(elem)) != 0)
		i += 1;
	if (ft_strncmp(data->my_env[i], elem, ft_strlen(elem)) == 0)
		data->elem_path = ft_strsplit((data->my_env[i] + 5), ':');
}

void	ft_list_push_params(t_data *data, t_liste *liste)
{
	int		i;

	i = 0;
	while (data->my_env[i])
	{
		ft_add_elem(data->my_env[i], liste);
		i += 1;
	}
}
