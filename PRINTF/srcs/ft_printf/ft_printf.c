/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:41:46 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/18 16:12:10 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Adds formatted content to the buffer
 *	In case of error, the buffer error flag is set to true and the function ends
 *	Steps:	-	gets the right function from dispatch
 *			-	gets all the formatting info from the given format
 *			-	calls the function in order to get the result string
 *			-	stores the string into the buffer
 *	NB:	%c could lead to specific cases with the '\0' char
 *		Then, output strings from %c are treated appart for buffer insertion
 */
static void	print_formatted_content(
	const char *format,
	va_list args,
	t_format_dispatch dispatch[NB_CONV],
	t_fpf_buffer *buffer
)
{
	size_t			format_end;
	char			*(*f)(va_list args, t_input_format *input);
	char			*res;
	t_input_format	format_info;

	if (buffer == NULL)
		return ;
	if (format == NULL || args == NULL || dispatch == NULL)
		return (buffer->set_error(buffer));
	format_end = fpf_get_format_end(format);
	if (format_end == 0)
		return (buffer->set_error(buffer));
	f = dispatch_get_func(dispatch, format[format_end]);
	if (f == NULL)
		return (buffer->set_error(buffer));
	input_format_get_info(&format_info, format, format_end);
	res = f(args, &format_info);
	if (res == NULL)
		return (buffer->set_error(buffer));
	if (format[format_end] == 'c')
		buffer->add_chars_secure(buffer, res, format_info.length_result, 1);
	else
		buffer->add_str_secure(buffer, res, 1);
	free(res);
}

/*
 *	Handles format in order to check if it is a valid ft_printf format or not
 *	When the format is valid, print_formatted_content is called
 *	When it is not, the wrong format substring is added to the buffer
 *	The format_ptr given as input is moved to the end of the heandled part of it
 */
static void	special_format_handler(
	const char **format_ptr,
	va_list args,
	t_format_dispatch dispatch[NB_CONV],
	t_fpf_buffer *buffer
)
{
	const char	*format;
	size_t		i;
	size_t		j;

	format = *format_ptr;
	if (buffer == NULL)
		return ;
	if (args == NULL || dispatch == NULL)
		return (buffer->set_error(buffer));
	i = fpf_get_format_end(format);
	if (i == 0)
		return (buffer->set_error(buffer));
	if (fpf_is_available_conversion(format[i]))
	{
		print_formatted_content(format, args, dispatch, buffer);
		*format_ptr += i + 1;
		return ;
	}
	j = 0;
	while (j < i && !buffer->error)
	{
		buffer->add_char_secure(buffer, format[j], 1);
		j++;
	}
	*format_ptr += i;
}

/*
 *	Parses format input in order to store the characters to display into
 *	a buffer. It can take a variable number of arguments
 *	It returns the number of characters which have been written
 *	In case of error -1 is returned
 */
int	ft_printf(const char *format, ...)
{
	t_fpf_buffer		buffer;
	t_format_dispatch	dispatch[NB_CONV];
	va_list				args;

	if (format == NULL)
		return (-1);
	buffer = buffer_init();
	init_format_dispatch(dispatch);
	va_start(args, format);
	while (*format != '\0' && !buffer.error)
	{
		if (*format == '%')
			special_format_handler(&format, args, dispatch, &buffer);
		else
		{
			buffer.add_char_secure(&buffer, *format, 1);
			format++;
		}
	}
	va_end(args);
	if (!buffer.error)
		buffer.put_fd(&buffer, 1);
	if (buffer.error)
		return (-1);
	return ((int) buffer.total_len);
}
