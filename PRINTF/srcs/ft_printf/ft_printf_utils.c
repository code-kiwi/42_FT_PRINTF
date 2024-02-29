/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:31:18 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/18 16:14:18 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Returns true is the char c is in the available conversion flags
 */
bool	fpf_is_available_conversion(char c)
{
	return (c != '\0' && ft_strchr(AVAILABLE_CONVS, c) != NULL);
}

/*
 *	Returns true if the char c is in the available format chars
 */
bool	fpf_is_valid_format(char c)
{
	return (c != '\0' && ft_strchr(VALID_FORMAT, c) != NULL);
}

/*
 *	Returns the index of the end of the given format.
 *	Parses fromat:
 *		- if a conversion char is found returns its index
 *		- if an invalid chars is found, returns its index
 *		- if a '%' is found (not at index 0) returns its index
 */
size_t	fpf_get_format_end(const char *format)
{
	size_t	i;

	if (format == NULL)
		return (0);
	if (format[0] == '\0' || format[1] == '\0')
		return (0);
	i = 1;
	while (format[i] != '\0' && !(i != 0 && format[i] == '%')
		&& !fpf_is_available_conversion(format[i])
		&& fpf_is_valid_format(format[i]))
		i++;
	return (i);
}
