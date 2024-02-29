# Compiles ft_printf library and our main in order to use it
if [ -n "$1" ];
then
	if [ "$1" = "NF" ];
	then
		make -sC ../ NOFLAGS=1
		cc main.c -I../includes -I../libft -L../ -lftprintf -o prog
	else
		echo "ERROR - \"NF\" is the only accepted parameter if one is provided"
	fi
else
	make -sC ../
	cc -Wall -Werror -Wextra main.c -I../includes -I../libft -L../ -lftprintf -o prog
fi
