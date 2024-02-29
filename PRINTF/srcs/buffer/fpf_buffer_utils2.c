/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_buffer_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:50:12 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/18 14:19:47 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fpf_buffer.h"

/*
 *	Appends c to the buffer
 *	If the buffer is full, flushes it before adding
 *	next_index and total_len are updated
 */
void	buffer_add_char(t_fpf_buffer *buffer, char c)
{
	if (buffer == NULL)
		return ;
	if (buffer->get_available_size(buffer) <= 1)
		buffer->flush(buffer);
	(buffer->content)[buffer->next_index] = c;
	buffer->next_index += 1;
	buffer->total_len += 1;
}

/*
 *	Appends c to the buffer
 *	If the buffer is full:
 *		-	writes the buffer content to given file descriptor
 *		- 	flushes the buffer
 *		-	appends the given char
 */
void	buffer_add_char_secure(t_fpf_buffer *buffer, char c, int fd)
{
	if (buffer == NULL)
		return ;
	if (buffer->get_available_size(buffer) <= 1)
	{
		buffer->put_fd(buffer, fd);
		buffer->flush(buffer);
	}
	buffer->add_char(buffer, c);
}

/*
 *	Adds nb_chars chars to the buffer
 *	Appends each char one by one
 *	As soon as the buffer is full:
 *		-	writes the buffer content to given file descriptor
 *		- 	flushes the buffer
 *		-	appends the remaining chars
 *	WARNING: the string's len is not checked, an invalid nb_chars leads to
 *	undefined behaviours
 */
void	buffer_add_chars_secure(
	t_fpf_buffer *buffer,
	char *str,
	size_t nb_chars,
	int fd
)
{
	size_t	i;

	if (buffer == NULL)
		return ;
	i = 0;
	while (i < nb_chars)
	{
		buffer->add_char_secure(buffer, str[i], fd);
		i++;
	}
}

/*
 *	Appends str to the buffer
 *	Each char is added one by one and, as soon as the buffer is full,
 *	it is flushed
 */
void	buffer_add_str(t_fpf_buffer *buffer, char *str)
{
	size_t	i;
	size_t	str_len;

	if (buffer == NULL || str == NULL)
		return ;
	str_len = ft_strlen(str);
	i = 0;
	while (i < str_len)
	{
		buffer->add_char(buffer, str[i]);
		i++;
	}
}

/*
 *	Appends str to the buffer
 *	Appends each char one by one
 *	As soon as the buffer is full:
 *		-	writes the buffer content to given file descriptor
 *		- 	flushes the buffer
 *		-	appends the remaining chars
 */
void	buffer_add_str_secure(t_fpf_buffer *buffer, char *str, int fd)
{
	size_t	i;
	size_t	str_len;

	if (buffer == NULL || str == NULL)
		return ;
	str_len = ft_strlen(str);
	i = 0;
	while (i < str_len)
	{
		buffer->add_char_secure(buffer, str[i], fd);
		i++;
	}
}
