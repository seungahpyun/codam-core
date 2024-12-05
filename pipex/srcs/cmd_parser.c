/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 18:39:44 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/05 15:01:33 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int count_args(char *str)
{
	int count;
	int i;
	char quote;
	int in_word;

	count = 0;
    i = 0;
    in_word = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            quote = str[i++];
            if (!in_word)
                count++;
            in_word = 1;
            while (str[i])
            {
                if (str[i] == '\\' && str[i + 1] == quote)
                    i += 2;
                else if (str[i] == quote)
                    break;
                else
                    i++;
            }
            if (str[i])
                i++;
        }
        else if (str[i] != ' ')
        {
            if (!in_word)
                count++;
            in_word = 1;
            i++;
        }
        else
        {
            in_word = 0;
            i++;
        }
    }
    return (count);
}

static char *copy_quoted_content(char *str, int *i, char quote)
{
    int start;
    int j;
    char *result;
    char *temp;

    start = *i;
    j = 0;
    temp = malloc(ft_strlen(str) + 1);
    if (!temp)
        return (NULL);
    while (str[*i])
    {
        if (str[*i] == '\\' && str[*i + 1] == quote)
        {
            temp[j++] = str[*i + 1];
            *i += 2;
        }
        else if (str[*i] == quote)
            break;
        else
            temp[j++] = str[(*i)++];
    }
    temp[j] = '\0';
    result = ft_strdup(temp);
    free(temp);
    if (str[*i])
        (*i)++;
    return (result);
}

static char *extract_quoted(char *str, int *i)
{
    char quote;

    quote = str[*i];
    (*i)++;
    return (copy_quoted_content(str, i, quote));
}

static char *extract_unquoted(char *str, int *i)
{
    int start;
    int len;
    char *result;

    start = *i;
    while (str[*i] && str[*i] != ' ' && str[*i] != '"' && str[*i] != '\'')
        (*i)++;
    len = *i - start;
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    ft_strlcpy(result, &str[start], len + 1);
    return (result);
}

char **parse_cmd(char *str)
{
    char **args;
    char *token;
    int i;
    int arg_count;

    args = malloc(sizeof(char *) * (count_args(str) + 1));
    if (!args)
        return (NULL);
    i = 0;
    arg_count = 0;
    while (str[i])
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (!str[i])
            break;
        if (str[i] == '"' || str[i] == '\'')
            token = extract_quoted(str, &i);
        else
            token = extract_unquoted(str, &i);
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
