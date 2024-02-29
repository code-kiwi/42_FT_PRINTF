/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_formatter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:24:38 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/19 20:07:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Common precision formatting function for %d, %i and %p conversions
 *	Adds '+' or ' ' in front of the given string if inputs requires it
 *	When an error occurs NULL is returned
 */
char	*fpf_formatter_plus_space(char *str, t_input_format *input)
{
	char	*res;

	if (str == NULL || input == NULL)
		return (NULL);
	res = str;
	if (input->plus)
	{
		res = ft_strjoin("+", res);
		if (res == NULL)
			return (NULL);
	}
	else if (input->space)
	{
		res = ft_strjoin(" ", res);
		if (res == NULL)
			return (NULL);
	}
	return (res);
}

/*
 *	Common precision formatting function for %d, %i and %u conversions
 *	Adds precision to given string when input requires it.
 *	When an error occurs NULL is returned
 *	NB:	the nb input is here to manage zero precision when nb == 0
 */
char	*fpf_formatter_precision(char *str, t_input_format *input, int nb)
{
	char	*res;

	if (str == NULL || input == NULL)
		return (NULL);
	res = str;
	if (input->precision)
	{
		if (nb == 0 && input->precision_val == 0)
			res = ft_strdup("");
		else
			res = ft_prepend_chars(res, '0', input->precision_val);
	}
	return (res);
}

/*
 *	Common length formatting function for %d, %i and %u conversions
 *	Appends or prepends ' ' or '0'  to given string when input requires it.
 *	When an error occurs NULL is returned
 */
char	*fpf_formatter_length(char *str, t_input_format *input)
{
	char	*res;

	if (str == NULL || input == NULL)
		return (NULL);
	res = str;
	if (input->length > 0)
	{
		if (input->minus)
			res = ft_append_chars(res, ' ', input->length);
		else if (!input->precision && input->zero)
			res = ft_prepend_chars(res, '0', input->length);
		else
			res = ft_prepend_chars(res, ' ', input->length);
	}
	return (res);
}
