/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_itoa.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 12:03:18 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 12:03:19 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_num_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	num = n;
	len = get_num_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (len-- > 0 && num >= 0)
	{
		if (result[len] == '-')
			break ;
		result[len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	num = -12345;
// 	char *str = ft_itoa(num);

// 	printf("Converted string: %s\n", str);
// 	free(str);
// 	return (0);
// }
