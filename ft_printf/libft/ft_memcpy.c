/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_memcpy.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 13:48:59 by spyun          #+#    #+#                */
/*   Updated: 2024/10/08 13:49:01 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (dest);
	if (n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main() 
// {
//     char first_str[20] = "Tutorials";
//     char sec_str[] = "Point";

//     puts("first_str before memcpy:");
//     puts(first_str);

//     ft_memcpy(first_str, sec_str, strlen(sec_str) + 1);

//     puts("\nfirst_str after memcpy:");
//     puts(first_str);
//     return 0;
// }
