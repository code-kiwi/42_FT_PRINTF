/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_char_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:19:25 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/18 14:18:05 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Formats the char string in order to correspond to input_format requirements
 *	If the char '\0' is managed, 0 is replaced by one, the format is applied
 *	and the old 1 is turned back into the 0
 *	The result string true len is add to input_format (because of '\0' char
 *	the result string could be an invalid C-string)
 *	When an error occurs NULL is returned
 */
static char	*fpf_char_formatter(char *str, t_input_format *input, char c)
{
	char	*res;
	size_t	i;

	if (str == NULL || input == NULL)
		return (NULL);
	if (input->length == 0)
		return (str);
	if (c == 0)
		str[0] = 1;
	if (input->minus)
		res = ft_append_chars(str, ' ', input->length);
	else
		res = ft_prepend_chars(str, ' ', input->length);
	if (res == NULL)
		return (NULL);
	input->length_result = ft_strlen(res);
	if (c == 0)
	{
		i = 0;
		while (res[i] && res[i] != 1)
			i++;
		if (res[i] == 1)
			res[i] = 0;
	}
	return (res);
}

/*
 *	Gets a char from the given va_list and converts it into a string
 *	When an error occurs NULL is returned
 */
char	*fpf_char_manager(va_list args, t_input_format *input)
{
	char	c;
	char	*temp;
	char	*res;

	if (args == NULL || input == NULL)
		return (NULL);
	c = va_arg(args, int);
	temp = ft_ctoa(c);
	if (temp == NULL)
		return (NULL);
	input->length_result = 1;
	res = fpf_char_formatter(temp, input, c);
	if (temp != res)
		free(temp);
	return (res);
}
