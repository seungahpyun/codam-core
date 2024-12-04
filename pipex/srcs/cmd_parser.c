/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 18:39:44 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 18:50:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static char	*parse_quoted_arg(char *str, int *i)
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

char	**parse_cmd(char *str)
{
	char	**args;
	char	*token;
	int		i;
	int		arg_count;
	int		len;

	i = 0;
	arg_count = 0;
	len = ft_strlen(str);
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (is_quote(str[i]))
			token = parse_quoted_arg(str, &i);
		else
		{
			token = ft_strdup(&str[i]);
			while (str[i] && str[i] != ' ')
				i++;
			token[i] = '\0';
		}
		if (!token)
		{
			free_array(args);
			return (NULL);
		}
		args[arg_count++] = token;
	}
	args[arg_count] = NULL;
	return (args);
}
