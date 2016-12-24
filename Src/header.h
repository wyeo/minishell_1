/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 05:31:24 by wyeo              #+#    #+#             */
/*   Updated: 2015/06/29 19:58:53 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/types.h>
# include <unistd.h>
# include "./../Libft/libft.h"
# include "get_next_line.h"
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

int							g_var_global;

typedef struct				s_data
{
	char					**my_env;
	char					*courant;
	char					*prompt;
	char					**prompt_table;
	char					**multi_cmd;
	char					**elem_path;
	pid_t					pid;
	int						returned;
}							t_data;

typedef struct				s_element
{
	char					*val;
	struct s_element		*next;
}							t_element;

typedef struct				s_liste
{
	t_element				*first;
	t_element				*end;
	int						len;
}							t_liste;

void						ft_welcome(void);
void						ft_bye(void);
void						handler(int sig);
void						happy_or_not(t_data *data);

int							ft_get_cmd(t_data *data);
int							ft_outc(int c);

int							len_double_table(char **str);
int							ft_cpy_env(char **env, t_data *data);
void						ft_get_env(char *elem, t_data *data);
void						ft_get_courant(t_data *data);
void						ft_list_push_params(t_data *data, t_liste *liste);

void						ft_add_strword(t_data *data);
int							ft_check_exec(t_data *data, t_liste *liste);
char						*ft_check_cmd(t_data *data);
void						ft_print_tab(char **bat);
void						ft_exec(char *tmp, t_data *data);

void						ft_builtins(t_data *data, t_liste *liste);
int							ft_env(t_data *data, t_liste *liste);
int							ft_setenv(t_data *data, t_liste *liste);
int							ft_unsetenv(t_data *data, t_liste *liste);
int							before_equal(char *str);
int							ft_check_position(t_data *data, t_liste *liste);
int							ft_check_exist(t_data *data, t_liste *liste, int l);
int							ft_setenv_junior(t_data *data, t_liste *liste);
int							ft_yes_exist(t_data *data, t_liste *liste);

void						ft_init_liste(t_liste *liste);
int							ft_add_elem(char *str, t_liste *liste);
int							ft_add_end_elem(char *str, t_liste *liste);
void						ft_affiche_liste(t_element *courant);
t_element					*ft_get_end_elem(t_liste *liste);
int							ft_supp_liste(t_liste *liste, int pos);

int							ft_cd(t_data *data, t_liste *liste);
char						*ft_env_path(t_data *data, char *str);
void						ft_change_pwd(t_liste *liste);
void						ft_change_oldpwd(t_liste *liste);

#endif
