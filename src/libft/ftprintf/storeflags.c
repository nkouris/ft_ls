/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storeflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:25:09 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/10 12:38:14 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void	store_padp(const char **format, t_flags *flags, int *found,
		va_list *args)
{
	int i;
	int num;

	i = 0;
	num = 0;
	if (**format == '.')
	{
		(*found)++;
		flags->preper = 1;
		(*format)++;
		if (**format == '*')
		{
			flags->precision = va_arg(*args, int);
			(*format)++;
		}
		else
		{
			while (ft_isdigit(**format))
			{
				num = *(*format)++ - '0';
				i = (i * 10) + num;
				flags->precision = i;
			}
		}
	}
}

static void	store_padw(const char **format, t_flags *flags, int *found,
		va_list *args)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if ((ft_isdigit(**format) && flags->fieldwidth < 0 && **format != '0'))
	{
		(*found)++;
		while (ft_isdigit(**format))
		{
			num = *(*format)++ - '0';
			i = (i * 10) + num;
			flags->fieldwidth = i;
		}
	}
	else if (**format == '*')
	{
		flags->fieldwidth = va_arg(*args, int);
		(*format)++;
	}
	store_padp(format, flags, found, args);
}

static void	store_pre1(const char **format, t_flags *flags, int *found)
{
	if (**format == ' ' ? flags->spacepad = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '+' ? flags->sign = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '#' ? flags->altform = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '0' ? flags->zpad = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '-' ? flags->negwidth = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '$' ? flags->dolla = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == 'L' ? flags->capl = 1 : 0)
		(*format)++ ? (*found)++ : *found;
	if (**format == '\'' ? flags->apos = 1 : 0)
		(*format)++ ? (*found)++ : *found;
}

void		store_pre(const char **format, t_flags *flags, va_list *args)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	while (**format && !(ft_isalpha(**format)) && j < 2)
	{
		found = 0;
		if (**format == '%' && j < 2)
		{
			!(j++) ? (*format)++ : *format;
			found++;
		}
		store_pre1(format, flags, &found);
		store_padw(format, flags, &found, args);
		while (((**format == 'l' || **format == 'j'
				|| **format == 'z' || **format == 'h') && i < 2))
			flags->lenmod[i++] = *(*format)++;
		if (!found && !(ft_isalpha(**format)) && **format)
			(*format)++;
	}
}
