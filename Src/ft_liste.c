/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 20:48:13 by wyeo              #+#    #+#             */
/*   Updated: 2015/04/30 03:21:19 by wyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		ft_init_liste(t_liste *liste)
{
	liste->first = NULL;
	liste->len = 0;
}

t_element	*ft_get_end_elem(t_liste *liste)
{
	t_element		*courant;

	courant = liste->first;
	while (courant->next != NULL)
		courant = courant->next;
	liste->end = courant;
	return (courant);
}

int			ft_add_elem(char *str, t_liste *liste)
{
	t_element		*nouveau;

	if (!(nouveau = (t_element *)malloc(sizeof(t_element))))
		return (-1);
	if (!(nouveau->val = (char *)malloc(sizeof(char) * ft_strlen(str))))
		return (-1);
	nouveau->val = ft_strcpy(nouveau->val, str);
	nouveau->next = liste->first;
	liste->first = nouveau;
	liste->len++;
	return (0);
}

int			ft_add_end_elem(char *str, t_liste *liste)
{
	t_element		*courant;
	t_element		*nouveau;

	courant = ft_get_end_elem(liste);
	if (!(nouveau = (t_element *)malloc(sizeof(t_element))))
		return (-1);
	if (!(nouveau->val = (char *)malloc(sizeof(char) * ft_strlen(str))))
		return (-1);
	nouveau->val = ft_strcpy(nouveau->val, str);
	nouveau->next = NULL;
	courant->next = nouveau;
	liste->len++;
	return (0);
}

void		ft_affiche_liste(t_element *courant)
{
	if (courant->next != NULL)
		ft_affiche_liste(courant->next);
	ft_putendl(courant->val);
}

int			ft_supp_liste(t_liste *liste, int pos)
{
	int			i;
	t_element	*courant;
	t_element	*supp_element;

	i = 1;
	courant = liste->first;
	if (pos == 0)
	{
		liste->first = courant->next;
		liste->len--;
		free(courant->val);
		free(courant);
		return (-1);
	}
	while (i < pos)
	{
		++i;
		courant = courant->next;
	}
	supp_element = courant->next;
	courant->next = courant->next->next;
	if (courant->next == NULL)
		liste->end = courant;
	free (supp_element->val);
	free (supp_element);
	liste->len--;
	return (0);
}
