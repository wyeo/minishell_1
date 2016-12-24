/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 05:45:39 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/19 16:23:06 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		ft_add_strword(t_data *data)
{
	int		i;

	i = 0;
	ft_get_env("PATH", data);
	while (data->elem_path[i])
	{
		data->elem_path[i] = ft_strjoin(data->elem_path[i], "/");
		i += 1;
	}
}

void		ft_tilde(t_data *data)
{
	if ((len_double_table(data->prompt_table) == 2)
			&& (ft_strncmp(data->prompt_table[1], "~", 1) == 0))
	{
		free(data->prompt_table[1]);
		data->prompt_table[1] = ft_strdup(ft_env_path(data, "HOME="));
	}
}

char		*ft_check_cmd(t_data *data)
{
	int		i;
	int		t;
	char	*tmp;

	i = 0;
	t = 0;
	while (data->elem_path[i])
	{
		tmp = ft_strjoin(data->elem_path[i], data->prompt_table[0]);
		t = access(tmp, F_OK);
		if (t == 0)
			return (tmp);
		else if (t == -1)
			free(tmp);
		i += 1;
	}
	return (NULL);
}

int			ft_check_exec(t_data *data, t_liste *liste)
{
	char	*tmp;

	ft_add_strword(data);
	ft_tilde(data);
	if (ft_cd(data, liste) == -1)
		return (-1);
	if (ft_setenv(data, liste) == -1)
		return (-1);
	if (ft_unsetenv(data, liste) == -1)
		return (-1);
	if (ft_env(data, liste) == -1)
		return (-1);
	if (data->prompt_table[0]
			&& ft_strcmp(data->prompt_table[0], "exit") == 0)
	{
		if (len_double_table(data->prompt_table) > 2)
		{
			ft_putendl("exit: too many arguments");
			data->returned = -1;
			return (-1);
		}
		ft_bye();
		exit(0);
	}
	tmp = ft_check_cmd(data);
	if (tmp)
	{
		data->returned = 0;
		ft_exec(tmp, data);
	}
	if (!tmp)
	{
		if (data->prompt_table[0] && (data->prompt_table[0][0] == '.'
				|| data->prompt_table[0][1] == '.'))
		{
			if (access(data->prompt_table[0], X_OK) == 0)
				ft_exec(data->prompt_table[0], data);
			else
				data->returned = -1;
		}
		else if (data->prompt_table[0] && !data->prompt_table[1]
				&& ft_strcmp(data->prompt_table[0], "unsetenv") == 0)
		{
			ft_putendl_fd("unsetenv: T'es Bete ou QUOOIII ?!!", 2);
			data->returned = -1;
		}
		else if (data->prompt_table[0])
		{
			ft_putstr_fd("ft_minishell: command not found: ", 2);
			ft_putendl_fd(data->prompt_table[0], 2);
			data->returned = -1;
		}
	}
	return (0);
}

void		ft_exec(char *tmp, t_data *data)
{
	data->pid = fork();
	if (data->pid == -1)
		ft_putendl_fd("fork: problem.", 2);
	if (data->pid == 0)
		execve(tmp, data->prompt_table, NULL);
	if (data->pid > 0)
	{
		g_var_global = data->pid;
		wait(&data->returned);
	}
}
