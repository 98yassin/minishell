/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:06:00 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/03 12:06:03 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void        display_error(char *value)
{
    ft_putstr_fd("\e[1;91mMy_Minishell: syntax error near unexpected token ",1);
    ft_putstr_fd(value ,1);
    ft_putstr_fd("\e[0m\n",1);
}

void        destroy_list(t_token_list *lst)
{
    t_token_list *tmp;
	while (lst != NULL) 
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp);
        tmp = NULL;
    }
}

int         check_quotes(char *value)
{
    int j;
    int backslash;
    int result;

    j = 0;
    backslash = 0;
    result = 0;
    while (value[j] != '\0')
    {
        if (value[j] == '\"')
        {
            j++;
            while (value[j] != '\0' && value[j] != '"')
            {
                if (value[j] == '\\')
                {
                    backslash = check_backslash(value, j);
                    if (backslash % 2 != 0)
                    {
                        j = j + backslash;
                        backslash = 0;
                    }else
                    {
                        j = j + backslash - 1;
                        backslash = 0;
                    }

                }
                j++;
            }
            if (value[j] == '"')
                result = 1;
            else //if (value[j] != '\0')
                result = -1;
        }
        j++;
    }
    return(result);
}

int         check_backslash_end(char *value)
{
    int backslash;
    int i;

    backslash = 0;
    i = 0;
    while (value[i] != '\0')
    {
        while (value[i] == '\\')
        {
            backslash++;
            i++;
        }
        if (value[i] == '\0')
            return(backslash);
        else
            backslash = 0;
        i++;
    }
    return (backslash);
}

void        check_syntax_error(t_token_list *token_lst)
{
    while (token_lst->type != NEWLINE)
    {
        if (token_lst->type == NONE)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                destroy_list(token_lst);
                break;
            }
        }
        else if (token_lst->type == REDIR_GREATER || token_lst->type == REDIR_LESSER || token_lst->type == DOUBLE_GREATER)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }
        }
        else if (token_lst->type == PIPE)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }      
        }
        else if (token_lst->type == WORD)
        {
            if (check_quotes(token_lst->value) == -1)
            {
                write(1,RED,ft_strlen(RED));
                ft_putstr_fd("syntax error multiple line not allowed\n",1);
                write(1,RESET,ft_strlen(RESET));
                destroy_list(token_lst);
                break;
            }
            if (((check_backslash_end(token_lst->value))) % 2 != 0)
            {
                write(1,RED,ft_strlen(RED));
                ft_putstr_fd("syntax error multiple line not allowed\n",1);
                write(1,RESET,ft_strlen(RESET));
                destroy_list(token_lst);
                break;
            }
        }
        else if (token_lst->type == SEMICOLON)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                destroy_list(token_lst);
                break;
            }
        }
        token_lst = token_lst->next;
    }
    
}
