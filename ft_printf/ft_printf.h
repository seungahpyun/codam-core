/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 09:46:44 by spyun          #+#    #+#                */
/*   Updated: 2024/10/21 09:46:46 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *str, ...);
int	ft_print_char(char c);
int	ft_print_string(va_list args);
int	ft_print_pointer(va_list args);
int	ft_print_int(va_list args);
int	ft_print_hex_lower(va_list args);
int	ft_print_hex_upper(va_list args);
int	ft_print_unsigned_int(va_list args);
#endif
