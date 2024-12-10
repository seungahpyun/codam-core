/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:53:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 08:50:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

static void	process_cmd(t_parse *parse, char *str)
{
	char	*token;

	if (is_quote(str[parse->i]))
		token = parse_quoted_arg(str, &parse->i);
	else
		token = parse_non_quoted_arg(str, &parse->i);
	if (!token)
	{
		free_array(parse->args);
		parse->error = 1;
		return ;
	}
	parse->args[parse->arg_count] = token;
	parse->arg_count++;
}

char	**parse_cmd(char *str)
{
	t_parse	parse;

	parse.error = 0;
	parse.arg_count = 0;
	parse.args = init_args(str, &parse.arg_count);
	if (!parse.args)
		return (NULL);
	parse.i = 0;
	while (str[parse.i] && !parse.error)
	{
		skip_spaces(str, &parse.i);
		if (!str[parse.i])
			break ;
		process_cmd(&parse, str);
	}
	if (parse.error)
		return (NULL);
	parse.args[parse.arg_count] = NULL;
	return (parse.args);
}
