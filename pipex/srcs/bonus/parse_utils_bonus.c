/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 10:03:03 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/09 10:07:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*parse_quoted_arg(char *str, int *i)
{
	char	quote;
	int		start;

	quote = str[*i];
	start = ++(*i);
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
		return (NULL);
	str[*i] = '\0';
	return (ft_strdup(&str[start]));
}

char	*parse_non_quoted_arg(char *str, int *i)
{
	char	*token;
	int		start;
	int		len;

	start = *i;
	while (str[*i] && str[*i] != ' ')
		(*i)++;
	len = *i - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], len + 1);
	return (token);
}

char	**init_args(char *str, int *arg_count)
{
	char	**args;

	*arg_count = 0;
	args = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!args)
		return (NULL);
	return (args);
}
