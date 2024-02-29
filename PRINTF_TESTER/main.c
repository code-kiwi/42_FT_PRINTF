/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:43:08 by mhotting          #+#    #+#             */
/*   Updated: 2023/12/19 19:25:47 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#define TEST(S, A, B, C, D) \
	str = S;\
	printf("\e[1m");\
	printf("TEST: %s", str);\
	printf("\e[m");\
	v1 = printf(str, A, B, C, D);\
	v2 = ft_printf(str, A, B, C, D);\
	redirect_stdout_to_file(printf_output_filename);\
	printf(str, A, B, C, D);\
	fclose(stdout);\
	redirect_stdout_to_file(ft_printf_output_filename);\
	ft_printf(str, A, B, C, D);\
	fclose(stdout);\
	redirect_stdout_to_file("/dev/tty");\
	compare_res = compare_files(printf_output_filename, ft_printf_output_filename);\
	remove(printf_output_filename);\
	remove(ft_printf_output_filename);\
	if (v1 != v2 || !compare_res)\
	{\
		printf("\033[0;31m");\
		if (v1 != v2 && !compare_res)\
			printf("ERROR - Outputs AND returned values are diferent\n\n");\
		else if (v1 != v2)\
			printf("ERROR - Returned values are diferent\n\n");\
		else\
			printf("ERROR - Outputs are diferent\n\n");\
		printf("\033[0m");\
		nb_err++;\
	}\
	else\
	{\
		printf("\033[0;32m");\
		printf("Returned values OK\n\n");\
		printf("\033[0m");\
	}

#define STR(S) "\"" S "\"\n"

void	redirect_stdout_to_file(const char *filename)
{
    freopen(filename, "w", stdout);
}

int	compare_files(const char *filename1, const char *filename2)
{
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        exit(EXIT_FAILURE);
    }

    int c1, c2;
	do {
        c1 = fgetc(file1);
        c2 = fgetc(file2);

        if (c1 != c2) {
            fclose(file1);
            fclose(file2);
            return 0;  // Les fichiers sont différents
        }
    } while (c1 != EOF && c2 != EOF);

    int result = feof(file1) && feof(file2);  // Vérifie si les deux fichiers sont à la fin

    fclose(file1);
    fclose(file2);

    return result;
}

void	print_intro_test(char *intro)
{
	system("clear");
	printf("\e[1m");
	printf("**********************\n");
	printf("* TESTS: %-11s *\n", intro);
	printf("**********************\n\n");
	printf("\e[m");
}

void	pause_tests(size_t nb_err)
{
	if (nb_err > 0)
	{
		printf("\033[0;31m");
		printf("NB_ERRORS: %zu\n", nb_err);
		printf("\033[0m");
	}
	else
	{
		printf("\033[0;32m");
		printf("NB_ERRORS: %zu\n", nb_err);
		printf("\033[0m");
	}

	printf("Press ENTER to run next tests...");
	while (getchar() != '\n');
}

int	main(int argc, char **argv)
{
	size_t		nb_err;
	char		*str;
	const char	*printf_output_filename = "printf_output.txt";
    const char	*ft_printf_output_filename = "ft_printf_output.txt";
	int			v1;
	int			v2;
	int			compare_res;

	if (argc == 1)
	{
		/*
		 * Mendatory
		 */

		// Tests %c
		nb_err = 0;
		print_intro_test("%c");
		TEST(STR("%c"), 'c', 0, 0, 0)
		TEST(STR("%c %c"), 'c', 'a', 0, 0)
		TEST(STR("%c %c"), 0, 'a', 0, 0)
		TEST(STR("%c %c"), 0, 1, 0, 0)
		TEST(STR("%c %c %c"), '0', 1, '2', 0)
		TEST(STR("%c %c %c"), '0', '1', '2', 0)
		TEST(STR("%c %c %c %c"), 1, 2, 3, 4)
		pause_tests(nb_err);
		
		// Tests %d %i
		nb_err = 0;
		print_intro_test("%d %i");
		TEST(STR("%d"), 0, 0, 0, 0)
		TEST(STR("%i"), 0, 0, 0, 0)
		TEST(STR("%d %d"), INT_MIN, INT_MAX, 0, 0)
		TEST(STR("%i %i"), INT_MIN, INT_MAX, 0, 0)
		TEST(STR("%d %d %d %d"), 1, 10, 100, 1000)
		TEST(STR("%i %i %i %i"), 1, 10, 100, 1000)
		TEST(STR("%d %d %d %d"), -1, -10, -100, -1000)
		TEST(STR("%i %i %i %i"), -1, -10, -100, -1000)
		TEST(STR("%d %d %d %d"), UINT_MAX, LONG_MAX, LONG_MIN, ULONG_MAX)
		TEST(STR("%i %i %i %i"), UINT_MAX, LONG_MAX, LONG_MIN, ULONG_MAX)
		TEST(STR("%d"), -485698, 0, 0, 0)
		TEST(STR("%i"), -485698, 0, 0, 0)
		pause_tests(nb_err);
		
		// Tests %u
		nb_err = 0;
		print_intro_test("%u");
		TEST(STR("%u"), 0, 0, 0, 0)
		TEST(STR("%u"), -1, 0, 0, 0)
		TEST(STR("%u"), 9, 0, 0, 0)
		TEST(STR("%u"), 10, 0, 0, 0)
		TEST(STR("%u"), 100, 0, 0, 0)
		TEST(STR("%u"), 1000, 0, 0, 0)
		TEST(STR("%u"), 9999, 0, 0, 0)
		TEST(STR("%u %u %u %u"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%u %u %u %u"), INT_MIN, 0, LONG_MIN, 0)
		pause_tests(nb_err);
		
		// Tests %x %X
		nb_err = 0;
		print_intro_test("%x %X");
		TEST(STR("%x"), 0, 0, 0, 0)
		TEST(STR("%X"), 0, 0, 0, 0)
		TEST(STR("%x"), 1, 0, 0, 0)
		TEST(STR("%X"), 1, 0, 0, 0)
		TEST(STR("%x"), 42, 0, 0, 0)
		TEST(STR("%X"), 42, 0, 0, 0)
		TEST(STR("%x"), 99, 0, 0, 0)
		TEST(STR("%X"), 99, 0, 0, 0)
		TEST(STR("%x"), 100, 0, 0, 0)
		TEST(STR("%X"), 100, 0, 0, 0)
		TEST(STR("%x"), -42, 0, 0, 0)
		TEST(STR("%X"), -42, 0, 0, 0)
		TEST(STR("%x"), -99, 0, 0, 0)
		TEST(STR("%X"), -99, 0, 0, 0)
		TEST(STR("%x"), -100, 0, 0, 0)
		TEST(STR("%X"), -100, 0, 0, 0)
		TEST(STR("%x %x %x %x"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%X %X %X %X"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%x %x"), INT_MIN, LONG_MIN, 0, 0)
		TEST(STR("%X %X"), INT_MIN, LONG_MIN, 0, 0)
		pause_tests(nb_err);
		
		// Tests %s
		nb_err = 0;
		print_intro_test("%s");
		TEST(STR("%s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%s"), NULL, 0, 0, 0)
		TEST(STR("%s"), "", 0, 0, 0)
		TEST(STR("%s %s %s"), "", NULL, "HELLO", 0)
		TEST(STR("%s %s %s %s"), " - ", "...", "0123456789//\\%", "NULL")
		TEST(STR("%s %s %s %s"), "\t\t", "...", "\\\"lol\"'''", NULL)
		pause_tests(nb_err);
		
		// Tests %p
		nb_err = 0;
		print_intro_test("%p");
		TEST(STR("%p"), 0, 0, 0, 0)
		TEST(STR("%p"), -1, 0, 0, 0)
		TEST(STR("%p"), 1, 0, 0, 0)
		TEST(STR("%p"), 42, 0, 0, 0)
		TEST(STR("%p"), 16, 0, 0, 0)
		TEST(STR("%p"), 255, 0, 0, 0)
		TEST(STR("%p %p %p %p"), INT_MIN, LONG_MIN, NULL, 0)
		TEST(STR("%p %p %p %p"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		pause_tests(nb_err);
		
		// Tests %%
		nb_err = 0;
		print_intro_test("%%");
		TEST(STR("%%%%"), 0, 0, 0, 0)
		TEST(STR("%"), 0, 0, 0, 0)
		TEST(STR("%%"), 0, 0, 0, 0)
		TEST(STR("%%%%%%%%%%"), 0, 0, 0, 0)
		TEST(STR("%%%%%%%%%"), 0, 0, 0, 0)
		TEST(STR("%%%%%%%%%%%%%%%%%"), 0, 0, 0, 0)
		pause_tests(nb_err);
		
		// Mix
		nb_err = 0;
		print_intro_test("Mix");
		TEST(STR("%%%c%%%s%%%d%%%i"), 'A', "42", 42, 0)
		TEST(STR("%%%u%%%x%%%X%%%%"), 42, 42, 42, 0)
		TEST(STR("%%%c%%%s%%%d%%%i"), 0, "HELLO", 123, -123)
		TEST(STR("% % %p % % %s % % % d % % %i"), NULL, NULL, -789, 0)
		TEST(NULL, 0, 0, 0, 0)
		pause_tests(nb_err);
	}
	else if (argc == 2 && argv[1][0] == 'b')
	{
		/*
		 * Bonus
		 */

		// Tests %c
		nb_err = 0;
		print_intro_test("BONUS %c");
		TEST(STR("%10c"), 'c', 0, 0, 0)
		TEST(STR("%100c"), 'c', 0, 0, 0)
		TEST(STR("%1000c"), 'c', 0, 0, 0)
		TEST(STR("%22c"), 'c', 0, 0, 0)
		TEST(STR("%-10c"), 'c', 0, 0, 0)
		TEST(STR("%-100c"), 'c', 0, 0, 0)
		TEST(STR("%-1000c"), 'c', 0, 0, 0)
		TEST(STR("%-22c"), 'c', 0, 0, 0)
		TEST(STR("%10c %24c"), 'c', 'a', 0, 0)
		TEST(STR("%-10c %-24c"), 'c', 'a', 0, 0)
		TEST(STR("%5c %17c"), 0, 'a', 0, 0)
		TEST(STR("%-5c %-17c"), 0, 'a', 0, 0)
		TEST(STR("%12c %33c"), 0, 1, 0, 0)
		TEST(STR("%-12c %-33c"), 0, 1, 0, 0)
		TEST(STR("%45c %21c %0c"), '0', 1, '2', 0)
		TEST(STR("%-45c %-21c %-0c"), '0', 1, '2', 0)
		TEST(STR("%2c %1c %0c"), '0', '1', '2', 0)
		TEST(STR("%-2c %-1c %-0c"), '0', '1', '2', 0)
		TEST(STR("%1c %4c %1c %8c"), 1, 2, 3, 4)
		TEST(STR("%-1c %-4c %-1c %-8c"), 1, 2, 3, 4)
		pause_tests(nb_err);
		
		// Tests %d %i
		nb_err = 0;
		print_intro_test("BONUS %d %i");
		TEST(STR("%10d"), 0, 0, 0, 0)
		TEST(STR("%010d"), 0, 0, 0, 0)
		TEST(STR("%-010d"), 0, 0, 0, 0)
		TEST(STR("%10i"), 0, 0, 0, 0)
		TEST(STR("%010i"), 0, 0, 0, 0)
		TEST(STR("%-010i"), 0, 0, 0, 0)
		TEST(STR("%123d"), 36, 0, 0, 0)
		TEST(STR("%0123d"), 45, 0, 0, 0)
		TEST(STR("%-0123d"), 789, 0, 0, 0)
		TEST(STR("%123i"), 36, 0, 0, 0)
		TEST(STR("%0123i"), 45, 0, 0, 0)
		TEST(STR("%-0123i"), 789, 0, 0, 0)
		TEST(STR("%+d"), 123, 0, 0, 0)
		TEST(STR("% d"), 123, 0, 0, 0)
		TEST(STR("%+10d"), 123, 0, 0, 0)
		TEST(STR("% 10d"), 123, 0, 0, 0)
		TEST(STR("%+010d"), 123, 0, 0, 0)
		TEST(STR("% 010d"), 123, 0, 0, 0)
		TEST(STR("%+i"), 123, 0, 0, 0)
		TEST(STR("% i"), 123, 0, 0, 0)
		TEST(STR("%+10i"), 123, 0, 0, 0)
		TEST(STR("% 10i"), 123, 0, 0, 0)
		TEST(STR("%+010i"), 123, 0, 0, 0)
		TEST(STR("% 010i"), 123, 0, 0, 0)
		TEST(STR("%.8d"), 42, 0, 0, 0)
		TEST(STR("%.50d"), 42, 0, 0, 0)
		TEST(STR("%10.8d"), 42, 0, 0, 0)
		TEST(STR("%-10.8d"), 42, 0, 0, 0)
		TEST(STR("%+-35.30d"), 42, 0, 0, 0)
		TEST(STR("% -35.30d"), 42, 0, 0, 0)
		TEST(STR("%.8d"), -5642, 0, 0, 0)
		TEST(STR("%.50d"), -5642, 0, 0, 0)
		TEST(STR("%10.8d"), -5642, 0, 0, 0)
		TEST(STR("%-10.8d"), -5642, 0, 0, 0)
		TEST(STR("%+-35.30d"), -5642, 0, 0, 0)
		TEST(STR("% -35.30d"), -5642, 0, 0, 0)
		TEST(STR("%.0d"), 0, 0, 0, 0)
		TEST(STR("%.0d"), 27, 0, 0, 0)
		TEST(STR("%.0d"), -369, 0, 0, 0)
		TEST(STR("%.8i"), 42, 0, 0, 0)
		TEST(STR("%.50i"), 42, 0, 0, 0)
		TEST(STR("%10.8i"), 42, 0, 0, 0)
		TEST(STR("%-10.8i"), 42, 0, 0, 0)
		TEST(STR("%+-35.30i"), 42, 0, 0, 0)
		TEST(STR("% -35.30i"), 42, 0, 0, 0)
		TEST(STR("%.8i"), -5642, 0, 0, 0)
		TEST(STR("%.50i"), -5642, 0, 0, 0)
		TEST(STR("%10.8i"), -5642, 0, 0, 0)
		TEST(STR("%-10.8i"), -5642, 0, 0, 0)
		TEST(STR("%+-35.30i"), -5642, 0, 0, 0)
		TEST(STR("% -35.30i"), -5642, 0, 0, 0)
		TEST(STR("%.0i"), 0, 0, 0, 0)
		TEST(STR("%.0i"), 27, 0, 0, 0)
		TEST(STR("%.0i"), -369, 0, 0, 0)
		TEST(STR("%0d"), 77, 0, 0, 0)
		TEST(STR("%0i"), 77, 0, 0, 0)
		TEST(STR("%+7.40d"), INT_MIN, 0, 0, 0);
		TEST(STR("%+7.40i"), INT_MIN, 0, 0, 0);
		pause_tests(nb_err);
		
		// Tests %u
		nb_err = 0;
		print_intro_test("BONUS %u");
		TEST(STR("%10u"), 9999, 0, 0, 0)
		TEST(STR("%010u"), 9999, 0, 0, 0)
		TEST(STR("%+010u"), 9999, 0, 0, 0)
		TEST(STR("%-010u"), 9999, 0, 0, 0)
		TEST(STR("% 010u"), 9999, 0, 0, 0)
		TEST(STR("%#010u"), 9999, 0, 0, 0)
		TEST(STR("%.10u"), 12, 0, 0, 0)
		TEST(STR("%.25u"), -1, 0, 0, 0)
		TEST(STR("%-30.10u"), 12, 0, 0, 0)
		TEST(STR("%-5.25u"), -1, 0, 0, 0)
		TEST(STR("%.0u"), 0, 0, 0, 0)
		TEST(STR("%.0u"), 42, 0, 0, 0)
		TEST(STR("%-12.5u %025.20u %-030.12u %u"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%+2.15u %-20u %-030u %017u"), INT_MIN, 0, LONG_MIN, 0)
		pause_tests(nb_err);
		
		// Tests %x %X
		nb_err = 0;
		print_intro_test("BONUS %x %X");
		TEST(STR("%#x"), 0, 0, 0, 0)
		TEST(STR("%#X"), 0, 0, 0, 0)
		TEST(STR("%#10x"), 42, 0, 0, 0)
		TEST(STR("%#10X"), 42, 0, 0, 0)
		TEST(STR("%25x"), 42, 0, 0, 0)
		TEST(STR("%25X"), 42, 0, 0, 0)
		TEST(STR("%032x"), 42, 0, 0, 0)
		TEST(STR("%032X"), 42, 0, 0, 0)
		TEST(STR("%#032x"), 42, 0, 0, 0)
		TEST(STR("%#032X"), 42, 0, 0, 0)
		TEST(STR("%025x"), -123, 0, 0, 0)
		TEST(STR("%025X"), -123, 0, 0, 0)
		TEST(STR("%-#025x"), -123, 0, 0, 0)
		TEST(STR("%-#025X"), -123, 0, 0, 0)
		TEST(STR("%-25x"), -123, 0, 0, 0)
		TEST(STR("%-25X"), -123, 0, 0, 0)
		TEST(STR("%+25x"), -123, 0, 0, 0)
		TEST(STR("%+25X"), -123, 0, 0, 0)
		TEST(STR("% 25x"), -123, 0, 0, 0)
		TEST(STR("% 25X"), -123, 0, 0, 0)
		TEST(STR("%.10x"), 799, 0, 0, 0)
		TEST(STR("%.10X"), 799, 0, 0, 0)
		TEST(STR("%#.10x"), 799, 0, 0, 0)
		TEST(STR("%#.10X"), 799, 0, 0, 0)
		TEST(STR("%+.10x"), 799, 0, 0, 0)
		TEST(STR("%+.10X"), 799, 0, 0, 0)
		TEST(STR("%-20.10x"), 799, 0, 0, 0)
		TEST(STR("%-20.10X"), 799, 0, 0, 0)
		TEST(STR("%020.10x"), 799, 0, 0, 0)
		TEST(STR("%020.10X"), 799, 0, 0, 0)
		TEST(STR("%-020.10x"), 799, 0, 0, 0)
		TEST(STR("%-020.10X"), 799, 0, 0, 0)
		TEST(STR("%-#020.10x"), 799, 0, 0, 0)
		TEST(STR("%-#020.10X"), 799, 0, 0, 0)
		TEST(STR("%47.30x %-47.30x %#47.30x %#-47.30x"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%47.30X %-47.30X %#47.30X %#-47.30X"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%x %x"), INT_MIN, LONG_MIN, 0, 0)
		TEST(STR("%X %X"), INT_MIN, LONG_MIN, 0, 0)
		pause_tests(nb_err);
		
		// Tests %s
		nb_err = 0;
		print_intro_test("BONUS %s");
		TEST(STR("%.10s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%2.10s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%-2.10s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%20.10s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%-20.10s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%.3s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%12.3s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%-12.3s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%.0s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%-89.0s"), "HELLO WORLD!", 0, 0, 0)
		TEST(STR("%s"), NULL, 0, 0, 0)
		TEST(STR("%.0s"), NULL, 0, 0, 0)
		TEST(STR("%63.0s"), NULL, 0, 0, 0)
		TEST(STR("%-63.0s"), NULL, 0, 0, 0)
		TEST(STR("%.5s"), NULL, 0, 0, 0)
		TEST(STR("%3.5s"), NULL, 0, 0, 0)
		TEST(STR("%-3.5s"), NULL, 0, 0, 0)
		TEST(STR("%.6s"), NULL, 0, 0, 0)
		TEST(STR("%10.6s"), NULL, 0, 0, 0)
		TEST(STR("%-10.6s"), NULL, 0, 0, 0)
		TEST(STR("%.15s"), NULL, 0, 0, 0)
		TEST(STR("%20.15s"), NULL, 0, 0, 0)
		TEST(STR("%-20.15s"), NULL, 0, 0, 0)
		TEST(STR("%s"), "", 0, 0, 0)
		TEST(STR("%s %s %s"), "", NULL, "HELLO", 0)
		TEST(STR("%-20.3s %.5s %10.20s %s"), " - ", "...", "0123456789//\\%", "NULL")
		TEST(STR("%4.20s %-10s %-.1s %.0s"), "\t\t", "...", "\\\"lol\"'''", NULL)
		pause_tests(nb_err);
		
		// Tests %p
		nb_err = 0;
		print_intro_test("BONUS %p");
		TEST(STR("%p"), NULL, 0, 0, 0)
		TEST(STR("%.0p"), NULL, 0, 0, 0)
		TEST(STR("%.4p"), NULL, 0, 0, 0)
		TEST(STR("%.5p"), NULL, 0, 0, 0)
		TEST(STR("%#p"), 0, 0, 0, 0)
		TEST(STR("% p"), 145, 0, 0, 0)
		TEST(STR("%+p"), 145, 0, 0, 0)
		TEST(STR("%#10p"), 42, 0, 0, 0)
		TEST(STR("%25p"), 42, 0, 0, 0)
		TEST(STR("%032p"), 42, 0, 0, 0)
		TEST(STR("%#032p"), 42, 0, 0, 0)
		TEST(STR("%025p"), -123, 0, 0, 0)
		TEST(STR("%+025p"), -123, 0, 0, 0)
		TEST(STR("% 025p"), -123, 0, 0, 0)
		TEST(STR("%-#025p"), -123, 0, 0, 0)
		TEST(STR("%-25p"), -123, 0, 0, 0)
		TEST(STR("%+-25p"), -123, 0, 0, 0)
		TEST(STR("%+25p"), -123, 0, 0, 0)
		TEST(STR("% 25p"), -123, 0, 0, 0)
		TEST(STR("% -25p"), -123, 0, 0, 0)
		TEST(STR("%.10p"), 799, 0, 0, 0)
		TEST(STR("%#.10p"), 799, 0, 0, 0)
		TEST(STR("%+.10p"), 799, 0, 0, 0)
		TEST(STR("%-20.10p"), 799, 0, 0, 0)
		TEST(STR("%020.10p"), 799, 0, 0, 0)
		TEST(STR("%-020.10p"), 799, 0, 0, 0)
		TEST(STR("%-#020.10p"), 799, 0, 0, 0)
		TEST(STR("%47.30p %-47.30p %#47.30p %#-47.30p"), INT_MAX, UINT_MAX, LONG_MAX, ULONG_MAX)
		TEST(STR("%p %p"), INT_MIN, LONG_MIN, 0, 0)
		pause_tests(nb_err);
	}

	return (0);
}
