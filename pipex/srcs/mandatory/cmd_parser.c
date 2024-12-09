/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:35:21 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/09 10:02:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static void	add_token(char **args, char *token, int *arg_count)
{
	if (!token)
		return ;
	args[*arg_count] = token;
	(*arg_count)++;
}

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

static void	process_cmd(char **args, char *str, int *i, int *arg_count)
{
	char	*token;

	if (is_quote(str[*i]))
		token = parse_quoted_arg(str, i);
	else
		token = parse_non_quoted_arg(str, i);
	if (!token)
	{
		free_array(args);
		return ;
	}
	add_token(args, token, arg_count);
}

char	**parse_cmd(char *str)
{
	char	**args;
	int		i;
	int		arg_count;

	args = init_args(str, &arg_count);
	if (!args)
		return (NULL);
	i = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		process_cmd(args, str, &i, &arg_count);
	}
	args[arg_count] = NULL;
	return (args);
}
