/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memmove.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 14:33:54 by spyun          #+#    #+#                */
/*   Updated: 2024/10/08 14:33:56 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;
	size_t				i;

	d = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	if (d > s && s + n > d)
	{
		i = n;
		while (i--)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main ()
// {
// 	char dest_str[] = "oldstring";
// 	const char src_str[]  = "newstring";
// 	printf("Before memmove dest = %s, src = %s\n", dest_str, src_str);
// 	ft_memmove(dest_str, src_str, 9);
// 	printf("After memmove dest = %s, src = %s\n", dest_str, src_str);
// 	return(0);
// }
