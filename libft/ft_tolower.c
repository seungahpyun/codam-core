/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_tolower.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 09:20:53 by spyun          #+#    #+#                */
/*   Updated: 2024/10/08 09:20:54 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += ('a' - 'A');
		return (c);
	}
	return (c);
}

// #include <stdio.h>

// int main(void)
// {
// 	char c = 'B';
// 	printf("%c\n", ft_tolower(c));
// 	char d = 'b';
// 	printf("%c\n", ft_tolower(d));
// 	char e = '1';
// 	printf("%c\n", ft_tolower(e));
// 	return 0;
// }
