/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_buffer_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:50:12 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/19 17:11:19 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fpf_buffer.h"

/*
 *	Creates an instance of a buffer and initializes it components
 *	If an invalid FPF_BUFFER_SIZE is given, then the error flag is set to true
 */
t_fpf_buffer	buffer_init(void)
{
	t_fpf_buffer	buffer;

	buffer.max_size = FPF_BUFFER_SIZE;
	buffer.total_len = 0;
	buffer.error = false;
	buffer.flush = buffer_flush;
	buffer.get_available_size = buffer_get_available_size;
	buffer.set_error = buffer_set_error;
	buffer.add_char = buffer_add_char;
	buffer.add_char_secure = buffer_add_char_secure;
	buffer.add_chars_secure = buffer_add_chars_secure;
	buffer.add_str = buffer_add_str;
	buffer.add_str_secure = buffer_add_str_secure;
	buffer.put_fd = buffer_put_fd;
	buffer.flush(&buffer);
	if (FPF_BUFFER_SIZE <= 2 || FPF_BUFFER_SIZE > SIZE_MAX)
		buffer.error = true;
	return (buffer);
}

/*
 *	Flushes the given buffer by setting all its chars to '\0' and setting
 *	next_index to 0
 */
void	buffer_flush(t_fpf_buffer *buffer)
{
	size_t	i;

	if (buffer == NULL)
		return ;
	i = 0;
	while (i < buffer->max_size)
	{
		(buffer->content)[i] = '\0';
		i++;
	}
	buffer->next_index = 0;
}

/*
 *	Returns the buffer remaining size
 */
size_t	buffer_get_available_size(t_fpf_buffer *buffer)
{
	if (buffer == NULL)
		return (0);
	return (buffer->max_size - buffer->next_index);
}

/*
 *	Puts the buffer content to the given file descriptor
 *	In case of error, the buffer's error flag is set to true
 */
void	buffer_put_fd(t_fpf_buffer *buffer, int fd)
{
	ssize_t	returned;

	if (buffer == NULL)
		return ;
	returned = write(fd, buffer->content, buffer->next_index);
	if (returned == -1)
		buffer->error = true;
}

/*
 *	Sets the buffer's error flag to true
 */
void	buffer_set_error(t_fpf_buffer *buffer)
{
	if (buffer == NULL)
		return ;
	buffer->error = true;
}
