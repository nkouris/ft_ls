/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listhandling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:20:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/01/05 12:50:06 by nkouris          ###   ########.fr       */
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
		if (!*top)
			break ;
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
	t_lsnode	*hold;
	char		*store;
	int			i;

	hold = (*top);
	store = (*temp)->fullpath;
	i = 0;
	if ((*top) != (*temp))
	{
		while (hold->next != (*temp))
			hold = hold->next;
		hold->next = 0;
		cleanup(hold);
	}
	(*top) = (*temp)->next;
	(*temp)->next = 0;
	cleanup((*temp));
	(*temp) = create_node(0, 0, 0);
	current_dir(temp, args, store);
}
