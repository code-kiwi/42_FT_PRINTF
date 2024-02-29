/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_format_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:28:39 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/18 13:29:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Deals with first part of format string
 */
static void	input_format_first_step(t_input_format *format_info, char c)
{
	if (format_info == NULL)
		return ;
	if (c == '+')
		format_info->plus = true;
	if (c == '-')
		format_info->minus = true;
	if (c == '0')
		format_info->zero = true;
	if (c == '#')
		format_info->alternative = true;
	if (c == ' ')
		format_info->space = true;
}

/*
 *	Initializes input_format data
 */
static void	input_format_init(t_input_format *format_info)
{
	if (format_info == NULL)
		return ;
	format_info->precision = false;
	format_info->precision_val = 0;
	format_info->length = 0;
	format_info->length_result = 0;
	format_info->alternative = false;
	format_info->space = false;
	format_info->plus = false;
	format_info->minus = false;
	format_info->zero = false;
}

/*
 *	Parses the format string in order to get format info
 */
void	input_format_get_info(
	t_input_format *format_info,
	const char *format,
	size_t format_end
)
{
	size_t	i;

	if (format_info == NULL)
		return ;
	input_format_init(format_info);
	if (format == NULL)
		return ;
	i = 1;
	while (i <= format_end && ft_strchr("+-0# ", format[i]) != NULL)
		input_format_first_step(format_info, format[i++]);
	format_info->length = ft_atoul(format + i);
	while (i < format_end && ft_isdigit(format[i]))
		i++;
	if (i < format_end && format[i] == '.')
	{
		format_info->precision = true;
		i++;
		format_info->precision_val = ft_atoul(format + i);
	}
	format_info->format = format[format_end];
}
