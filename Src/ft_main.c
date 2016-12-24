/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 05:29:28 by wyeo              #+#    #+#             */
/*   Updated: 2015/05/18 11:58:50 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <curses.h>
#include <term.h>

int			ft_termcaps(struct termios *term, char *name_term)
{
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, term) == -1)
		return (-1);
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (-1);
	return (0);
}

void		ft_bye(void)
{
	ft_putchar('\n');
	ft_putendl("|  _ \\| || || |  ___) | |");
	ft_putendl("| |_) ) \\| |/ | |_    | |");
	ft_putendl("|  _ ( \\_   _/|  _)   |_|");
	ft_putendl("| |_) )  | |  | |___   _ ");
	ft_putendl("|____/   |_|  |_____) (_)");
}

void		handler(int sig)
{
	if (g_var_global == 0)
	{
		ft_putchar('\n');
		ft_putstr("\033[31m(>_<)\033[0m $> ");
	}
	else if (g_var_global > 0)
	{
		kill(g_var_global, sig);
		g_var_global = 0;
	}
}

void		happy_or_not(t_data *data)
{
	if (data->returned == 0)
		ft_putstr("\033[32m(^_^)\033[0m $> ");
	else
		ft_putstr("\033[31m(>_<)\033[0m $> ");
}

int			main(int ac, char **av, char **env)
{
	t_data			data;
	t_liste			liste;
	char			*name_term;
	struct termios	term;

	(void)ac;
	(void)av;
	name_term = NULL;
	data.returned = 0;
	if (ft_termcaps(&term, name_term) == -1)
		ft_putendl("No Termcaps");
	ft_init_liste(&liste);
	ft_cpy_env(env, &data);
	ft_list_push_params(&data, &liste);
	signal(SIGINT, handler);
	while (42)
	{
		happy_or_not(&data);
		ft_get_cmd(&data);
		if (ft_check_exec(&data, &liste) == 1)
			exit(0);
	}
	return (0);
}
