/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:42:51 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/05 17:43:08 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command       *parce(t_token_list *token_list)
{
    t_token_list *lst_token;
    t_token_list *first_word;
    t_command *cmd = malloc(sizeof(t_command));
    int size;

    lst_token = token_list;
    size = 0;

    while (lst_token) 
    {
        if (lst_token->type == WORD)
        {
            size = 0;
            first_word = lst_token;
            while (lst_token->type == WORD)
            {
                size++;
                lst_token = lst_token->next;
            }
            cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
            int i = 0;
            while (i < size)
            {
                cmd->command[i] = ft_strdup(first_word->value);
                first_word = first_word->next;
                i++;
            }
            cmd->command[i] = NULL;
        }
        if (lst_token->type == REDIR_GREATER || lst_token->type == REDIR_LESSER || lst_token->type == DOUBLE_GREATER)
        {
            cmd->redirection = malloc(sizeof(t_redirection));
            cmd->redirection->type = lst_token->type;
            lst_token = lst_token->next;
            cmd->redirection->file = lst_token->value;
            cmd->redirection = cmd->redirection->next;
        }
        if (lst_token->type == PIPE)
        {
            cmd->redirection = NULL;
            cmd->next = malloc(sizeof(t_command));
            cmd = cmd->next;
            //cmd->next = NULL;
        }
        if (lst_token->type == SEMICOLON || lst_token->type == NEWLINE)
        {
            cmd->redirection = NULL;
            cmd->next = NULL;
        }
        
        lst_token = lst_token->next;
    }

    while (cmd != NULL)
    {
        int j = 0;
        ft_putstr_fd("\e[1;33mall commands\e[0m", 0);
        write(1,Cyan,ft_strlen(Cyan));
        ft_putstr_fd("command: {",1);
        while (cmd->command[j] != NULL)
        {
            printf("[%s]\n", cmd->command[j]);
            j++;
        }
        write(1,"}",1);
        write(1,"\n",1);
        while (cmd->redirection != NULL)
        {
            write(1,Cyan,ft_strlen(Cyan));
            ft_putstr_fd("file: {",1);
            ft_putstr_fd(cmd->redirection->file,1);
            write(1,"}",1);
            ft_putstr_fd(" type : {",1);
            ft_putstr_fd(cmd->redirection->type,1);
            write(1,"}",1);
            write(1,"\n",1);
            cmd->redirection = cmd->redirection->next;
        }
        write(1,RESET,ft_strlen(RESET));
        cmd = cmd->next;
    }
    return (cmd);
}