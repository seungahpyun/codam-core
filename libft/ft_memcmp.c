/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memcmp.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 10:06:06 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 10:06:08 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	int arr1[] = {1, 2, 3, 4, 5};
// 	int arr2[] = {1, 2, 3, 4, 6};

// 	int result = ft_memcmp(arr1, arr2, sizeof(arr1));
// 	if (result == 0)
// 		printf("Arrays are equal\n");
// 	else
// 		printf("Arrays are not equal\n");
// 	return (0);
// }
