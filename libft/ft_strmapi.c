/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strmapi.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 14:15:35 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 14:15:36 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// char example_func(unsigned int i, char c)
// {
// 	if (i % 2 == 0)
// 		return (c - 32);
// 	else
// 		return (c);
// }

// int main(void)
// {
// 	char str[] = "hello";
// 	char *result = ft_strmapi(str, example_func);

// 	if (result)
// 	{
// 		printf("Original: %s\n", str);
// 		printf("Modified: %s\n", result);
// 		free(result);
// 	}
// 	return 0;
// }
