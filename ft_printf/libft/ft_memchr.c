/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memchr.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 09:15:58 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 09:16:01 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
// 	char arr[] = { 'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd' };
// 	char *result;

// 	result = ft_memchr(arr, 'l', sizeof(arr));

// 	if (result != NULL)
// 		printf("Found 'l' at position: %ld\n", result - arr);
// 	else
// 		printf("'l' not found in the first %ld bytes\n", sizeof(arr));

// 	return 0;
// }
