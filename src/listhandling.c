/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listhandling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:20:22 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/21 19:08:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	rmhidden(t_lsnode **top)
{
	t_lsnode *front;
	t_lsnode *back;

	front = (*top);
	while ((*top)->name[0] == '.')
	{
		(*top) = (*top)->next;
		ft_memdel((void **)&front);
		front = (*top);
	}	
	while (front)
	{
		while (front->name[0] == '.')
		{
			back->next = front->next;
			ft_memdel((void **)&front);
			if (back->next)
				front = back->next;
			else
				break ;
		}
		back = front;
		front ? front = front->next : front;
	}
}

int			check_args(char ***argv, t_lssort **args)
{
	int found;

	found = 0;
	if ((*++(*argv))[0] == '-')
	{
		(**argv)++;
		while (***argv)
		{
			found = 0;
			if (***argv == 'l' ? (*args)->l = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'R' ? (*args)->R = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'a' ? (*args)->a = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'r' ? (*args)->r = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 't' ? (*args)->t = 1 : 0)
				(**argv)++ ? found++ : found;
			if (!found)
				usage_warning(***argv);
		}
		(*argv)++;
	}
	return (found);
}

void		clean_level(t_lsnode **top, t_lsnode **temp, t_lssort *args)
{
	t_lsnode *halt;

	halt = (*top);
	if ((*top) == (*temp))
	{
		(*top)->next = 0;
		cleanup(*top);
		(*top) = (*temp)->next;
	}
	else
	{
		while (halt != (*temp))
			halt = halt->next;
		halt->next = 0;
		cleanup(halt);
		(*top) = (*temp)->next;
	}
	current_dir(temp, args, (*temp)->fullpath);
}
