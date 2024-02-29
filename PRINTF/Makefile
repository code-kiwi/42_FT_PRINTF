# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhotting <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 09:49:51 by mhotting          #+#    #+#              #
#    Updated: 2023/12/18 14:29:58 by mhotting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL
NAME				=	libftprintf.a
CC					=	cc
ifndef NOFLAGS
	CFLAGS			=	-Wall -Werror -Wextra
endif

# LIBFT
LIBFT_DIR			=	libft/
LIBFT_FILE			=	$(LIBFT_DIR)libft.a
LIBFT_HEADER_FILE	=	libft.h
LIBFT_HEADER		=	$(LIBFT_DIR)$(LIBFT_HEADER_FILE)

# HEADERS
HEADERS_DIR			=	includes/
HEADERS_FILES		=	ft_printf.h					\
						fpf_buffer.h
HEADERS				=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# BUFFER
BUFFER_DIR			=	buffer/
BUFFER_FILES		=	fpf_buffer_utils1.c			\
						fpf_buffer_utils2.c
BUFFER				=	$(addprefix $(BUFFER_DIR), $(BUFFER_FILES))

# FORMAT
FORMAT_DIR			=	format_managers/
FORMAT_FILES		=	fpf_string_manager.c		\
						fpf_char_manager.c			\
						fpf_percent_manager.c		\
						fpf_int_manager.c			\
						fpf_uint_manager.c			\
						fpf_hexa_manager.c			\
						fpf_ptr_manager.c			\
						fpf_formatter.c
FORMAT				=	$(addprefix $(FORMAT_DIR), $(FORMAT_FILES))

# FT_PRINTF
FT_PRINTF_DIR		=	ft_printf/
FT_PRINTF_FILES		=	ft_printf.c					\
						ft_printf_utils.c			\
						format_dispatcher_utils.c	\
						input_format_utils.c
FT_PRINTF			=	$(addprefix $(FT_PRINTF_DIR), $(FT_PRINTF_FILES))

# SOURCES
SRCS_MAIN_DIR		=	srcs/
SRCS_FILES			=	$(BUFFER) $(FORMAT) $(FT_PRINTF)
SRCS_DIRS			=	$(BUFFER_DIR) $(FORMAT_DIR) $(FT_PRINTF_DIR)
SRCS				=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS
OBJS_MAIN_DIR		=	objs/
OBJS_DIRS			=	$(addprefix $(OBJS_MAIN_DIR), $(SRCS_DIRS))
OBJS_ALL_DIRS		=	$(OBJS_MAIN_DIR) $(OBJS_DIRS)
OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS				=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

#################################################

# RULES
all: $(NAME)

$(NAME): $(LIBFT_FILE) $(OBJS_ALL_DIRS) $(OBJS)
	cp $(LIBFT_FILE) $@
	ar -rcs $@ $(OBJS)

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.c $(HEADERS) $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(OBJS_ALL_DIRS):
	mkdir -p $@

$(LIBFT_FILE): FORCE
	make -C $(LIBFT_DIR)

FORCE:

clean:
	rm -rf $(OBJS_MAIN_DIR)

clean-libft:
	make -sC $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

ffclean: fclean clean-libft

re: fclean all

rre: ffclean all

bonus: all

.PHONY: all clean clean-libft fclean ffclean re rre FORCE bonus
