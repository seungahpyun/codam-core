/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:53:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 08:35:58 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// static void	add_token(char **args, char *token, int *arg_count)
// {
// 	if (!token)
// 		return ;
// 	args[*arg_count] = token;
// 	(*arg_count)++;
// }

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

// static void	process_cmd(char **args, char *str, int *i, int *arg_count)
// {
// 	char	*token;

// 	if (is_quote(str[*i]))
// 		token = parse_quoted_arg(str, i);
// 	else
// 		token = parse_non_quoted_arg(str, i);
// 	if (!token)
// 	{
// 		free_array(args);
// 		return ;
// 	}
// 	add_token(args, token, arg_count);
// }

// char	**parse_cmd(char *str)
// {
// 	char	**args;
// 	int		i;
// 	int		arg_count;

// 	args = init_args(str, &arg_count);
// 	if (!args)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		skip_spaces(str, &i);
// 		if (!str[i])
// 			break ;
// 		process_cmd(args, str, &i, &arg_count);
// 	}
// 	args[arg_count] = NULL;
// 	return (args);
// }

typedef struct s_parse
{
    char    **args;
    int     i;
    int     arg_count;
    int     error;
}   t_parse;

static void    process_cmd(t_parse *parse, char *str)
{
    char    *token;

    if (is_quote(str[parse->i]))
        token = parse_quoted_arg(str, &parse->i);
    else
        token = parse_non_quoted_arg(str, &parse->i);
    if (!token)
    {
        free_array(parse->args);
        parse->error = 1;
        return;
    }
    parse->args[parse->arg_count] = token;
    parse->arg_count++;
}

char    **parse_cmd(char *str)
{
    t_parse parse;

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
            break;
        process_cmd(&parse, str);
    }
    if (parse.error)
        return (NULL);
    parse.args[parse.arg_count] = NULL;
    return (parse.args);
}
