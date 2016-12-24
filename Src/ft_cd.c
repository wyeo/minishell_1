/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/22 11:24:55 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/19 14:25:09 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_env_path(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (ft_strncmp(data->my_env[i], str, ft_strlen(str)) != 0)
		i += 1;
	if (ft_strncmp(data->my_env[i], str, ft_strlen(str)) == 0)
		return (data->my_env[i] + before_equal(data->my_env[i]) + 1);
	return (NULL);
}

void	ft_change_oldpwd(t_liste *liste)
{
	char		str[1024];
	t_element	*c;

	c = liste->first;
	while (c != NULL)
	{
		if (ft_strncmp(c->val, "OLDPWD", 6) == 0)
			c->val = ft_strjoin("OLDPWD=", ft_strdup(getcwd(str, sizeof(str))));
		c = c->next;
	}
}

void	ft_change_pwd(t_liste *liste)
{
	char			str[1024];
	t_element		*c;

	c = liste->first;
	while (c != NULL)
	{
		if (ft_strncmp(c->val, "PWD", 3) == 0)
			c->val = ft_strjoin("PWD=", ft_strdup(getcwd(str, sizeof(str))));
		c = c->next;
	}
}

int		ft_cd(t_data *data, t_liste *liste)
{
	if (data->prompt_table[0] && ft_strcmp(data->prompt_table[0], "cd") == 0
			&& len_double_table(data->prompt_table) == 1)
	{
		ft_change_oldpwd(liste);
		chdir(ft_env_path(data, "HOME="));
		ft_change_pwd(liste);
		data->returned = 0;
		return (-1);
	}
	else if (data->prompt_table[0] && data->prompt_table[1]
			&& ft_strcmp(data->prompt_table[0], "cd") == 0
			&& ft_strcmp(data->prompt_table[1], "-") == 0
			&& !data->prompt_table[1][1]
			&& len_double_table(data->prompt_table) == 2)
	{
		chdir(ft_env_path(data, "OLDPWD="));
		ft_change_pwd(liste);
		ft_putendl(ft_env_path(data, "PWD="));
		data->returned = 0;
		return (-1);
	}
	else if (data->prompt_table[0]
			&& data->prompt_table[1]
			&& ft_strcmp(data->prompt_table[0], "cd") == 0
			&& ft_strcmp(data->prompt_table[1], "--") == 0
			&& !data->prompt_table[1][2]
			&& len_double_table(data->prompt_table) == 2)
	{
		ft_change_oldpwd(liste);
		chdir(ft_env_path(data, "HOME="));
		ft_change_pwd(liste);
		data->returned = 0;
		return (-1);
	}
	else if (data->prompt_table[0] && data->prompt_table[1]
			&& ft_strcmp(data->prompt_table[0], "cd") == 0
			&& ft_strcmp(data->prompt_table[1], ".") == 0
			&& !data->prompt_table[1][1]
			&& len_double_table(data->prompt_table) == 2)
		ft_change_oldpwd(liste);
	else if (data->prompt_table[0]
			&& data->prompt_table[1]
			&& ft_strcmp(data->prompt_table[0], "cd") == 0
			&& len_double_table(data->prompt_table) == 2)
	{
		if (chdir(data->prompt_table[1]) == -1)
		{
			ft_putstr_fd("cd: permission denied: ", 2);
			ft_putendl_fd(data->prompt_table[1], 2);
			data->returned = -1;
			return (-1);
		}
		ft_change_pwd(liste);
		return (-1);
	}
	else if (data->prompt_table[0]
			&& ft_strcmp(data->prompt_table[0], "cd") == 0
			&& len_double_table(data->prompt_table) != 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		data->returned = -1;
		return (-1);
	}
	return (0);
}
