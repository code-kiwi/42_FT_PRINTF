/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 08:50:05 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/19 19:51:16 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "fpf_buffer.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>

# define NB_CONV 7
# define AVAILABLE_CONVS "discuxXp%"
# define VALID_FORMAT "0123456789 +-#."

typedef struct s_intput_format
{
	size_t	precision_val;
	size_t	length;
	size_t	length_result;
	char	format;
	bool	precision;
	bool	alternative;
	bool	space;
	bool	plus;
	bool	minus;
	bool	zero;
}	t_input_format;

typedef struct s_format_dispatch
{
	char	*flags;
	char	*(*f)(va_list args, t_input_format *input);
}	t_format_dispatch;

char	*(*dispatch_get_func(t_format_dispatch dispatch[NB_CONV], char flag))(
			va_list args,
			t_input_format *input
			);
void	input_format_get_info(
			t_input_format *format_info,
			const char *format, size_t format_end
			);

int		ft_printf(const char *format, ...) \
			__attribute__ ((format (printf, 1, 2)));
void	init_format_dispatch(t_format_dispatch dispatch[NB_CONV]);

size_t	fpf_get_format_end(const char *format);
bool	fpf_is_valid_format(char c);
bool	fpf_is_available_conversion(char c);

char	*fpf_int_manager(va_list args, t_input_format *input);
char	*fpf_uint_manager(va_list args, t_input_format *input);
char	*fpf_hexa_manager(va_list args, t_input_format *input);
char	*fpf_ptr_manager(va_list args, t_input_format *input);
char	*fpf_string_manager(va_list args, t_input_format *input);
char	*fpf_char_manager(va_list args, t_input_format *input);
char	*fpf_percent_manager(va_list args, t_input_format *input);
char	*fpf_formatter_precision(char *str, t_input_format *input, int nb);
char	*fpf_formatter_length(char *str, t_input_format *input);
char	*fpf_formatter_plus_space(char *str, t_input_format *input);

#endif
