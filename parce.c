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

void            display_commands(t_command *comd)
{
    t_command *new_list;
    new_list = comd;
    //int k = 0;
    while (new_list != NULL)
    {
       // printf("node:{%d} : ",k++);
        ft_putstr_fd("\e[1;33mall commands\e[0m", 0);
        write(1,Cyan,ft_strlen(Cyan));
        ft_putstr_fd("command: {\n",1);
        if (new_list->command != NULL)
        {
            int j = 0;
            while (new_list->command[j] != NULL)
            {
                printf("[%s]\n", new_list->command[j]);
                j++;
            }
        }
        write(1,"}",1);
        write(1,"\n",1);
        while (new_list->redirection != NULL)
        {
            write(1,Cyan,ft_strlen(Cyan));
            ft_putstr_fd("file: {",1);
            ft_putstr_fd(new_list->redirection->file,1);
            write(1,"}",1);
            ft_putstr_fd(" type : {",1);
            ft_putstr_fd(new_list->redirection->type,1);
            write(1,"}",1);
            write(1,"\n",1);
            new_list->redirection = new_list->redirection->next;
        }
        ft_putstr_fd("separatore: {",1);
        ft_putnbr_fd(new_list->seperator,1);
        write(1,"}",1);
        write(1,"\n",1);
        write(1,RESET,ft_strlen(RESET));
        new_list = new_list->next;
    }
}

// t_command       *parce(t_token_list *token_list)
// {
//     t_token_list *lst_token;
//     t_token_list *first_word;
//     t_command *cmd = malloc(sizeof(t_command));
//     t_command *curr_cmd = cmd;
//     int size;

//     lst_token = token_list;
//     size = 0;

//     while (lst_token) 
//     {
//         if (lst_token->type == WORD)
//         {
//             size = 0;
//             first_word = lst_token;
//             while (lst_token->type == WORD)
//             {
//                 size++;
//                 lst_token = lst_token->next;
//             }
//             curr_cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
//             int i = 0;
//             while (i < size)
//             {
//                 curr_cmd->command[i] = ft_strdup(first_word->value);
//                 first_word = first_word->next;
//                 i++;
//             }
//             curr_cmd->command[i] = NULL;
//         }
//         if (lst_token->type == REDIR_GREATER || lst_token->type == REDIR_LESSER || lst_token->type == DOUBLE_GREATER)
//         {
//             if (curr_cmd->redirection != NULL)
//                 curr_cmd->redirection = curr_cmd->redirection->next;
//             curr_cmd->redirection = malloc(sizeof(t_redirection));

//             curr_cmd->redirection->type = lst_token->type;
//             lst_token = lst_token->next;
//             curr_cmd->redirection->file = lst_token->value;
//             //curr_cmd->redirection = curr_cmd->redirection->next;
//             if (curr_cmd->redirection == NULL)
//                 printf("Mr tofa7\n");
//         }
//         if (lst_token->type == PIPE)
//         {
//             //curr_cmd->redirection = NULL;
//             //free(cmd->command);
//             curr_cmd->next = NULL;
//             curr_cmd->next = malloc(sizeof(t_command));
//             curr_cmd = curr_cmd->next;
//         }
//         if (lst_token->type == SEMICOLON || lst_token->type == NEWLINE)
//         {
//             curr_cmd->redirection = NULL;
//             //free(cmd->command);
//             curr_cmd->next = NULL;
//         }
        
//         lst_token = lst_token->next;
//     }
//     return (cmd);
// }

// void                destroy_redirection_list(t_redirection **redirection)
// {
//     t_redirection *current_redirection;
//     while (*redirection != NULL)
//     {
//         current_redirection = *redirection;
//         *redirection = (*redirection)->next;
//         free(current_redirection->file);
//         free(current_redirection->type);
//         free(current_redirection);
//         current_redirection = NULL;
//     }
//     *redirection = NULL;
// }

t_redirection       *initial_redirection(char *type, char *value)
{
    t_redirection *new_redirection;

    //new_redirection = redirection;
    new_redirection = malloc(sizeof(t_redirection));
    new_redirection->type = ft_strdup(type);
    new_redirection->file = ft_strdup(value);
    new_redirection->next = NULL;
    return (new_redirection);
}

void                add_redirection(t_redirection *redirection, char *type, char *value)
{
    t_redirection *new_redirection;

    new_redirection = redirection;
    while (new_redirection->next != NULL)
    {
        new_redirection = new_redirection->next;
    }
    new_redirection->next = malloc(sizeof(t_redirection));
    new_redirection->next->type = ft_strdup(type);
    new_redirection->next->file = ft_strdup(value);
    new_redirection->next->next = NULL;
}
int                 tab_size(char **cmd_args)
{
    int i;

    i = 0;
    while (cmd_args[i] != NULL)
        i++;
    return (i);
}
void                add_separator(t_command *cmd, char *sep)
{
    if (sep == PIPE)
        cmd->seperator = e_pipe;
    else if (sep == SEMICOLON)
        cmd->seperator = e_semicolon;
    else
        cmd->seperator = e_newline;
}
t_command           *initial_cmd(char **cmd_arg, t_redirection *redirection, char *sep)
{
    t_command *first_cmd;
    int size;
    int i;

    first_cmd = malloc(sizeof(t_command));
    i = 0;
    first_cmd->command = NULL;
    size = tab_size(cmd_arg);
    if (cmd_arg != NULL)
    {
        first_cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
        while (cmd_arg[i] != NULL)
        {
            first_cmd->command[i] = ft_strdup(cmd_arg[i]);
            i++;
        }
        first_cmd->command[i] = NULL;
    }
    first_cmd->redirection = redirection;

    add_separator(first_cmd, sep);
    first_cmd->next = NULL;
    return(first_cmd);
}

void                add_cmd(t_command *cmd, char **cmd_arg, t_redirection *redirection, char *sep)
{
    t_command *new_cmd;
    int size;
    int i;

    new_cmd = cmd;
    i = 0;
    while (new_cmd->next != NULL)
        new_cmd = new_cmd->next;
    new_cmd->next = malloc(sizeof(t_command));
    new_cmd->next->command = NULL;
    size = tab_size(cmd_arg);
    if (cmd_arg != NULL)
    {
        new_cmd->next->command = (char **)malloc(sizeof(char *) * (size + 1));
        while (cmd_arg[i] != NULL)
        {
            new_cmd->next->command[i] = cmd_arg[i];
            i++;
        }
        new_cmd->next->command[i] = NULL;
    }
    new_cmd->next->redirection = redirection;
    add_separator(new_cmd->next, sep);
    new_cmd->next->next = NULL;
}

t_command           *ft_parce(t_token_list *token_list)
{
    t_command       *cmd;
    t_redirection   *redirection;
    t_token_list    *current_token;
    t_token_list    *first_word;
    char **cmd_arg;
    int size;

    size = 0;
    current_token = token_list;
    redirection = NULL;
    cmd_arg = NULL;
    cmd = NULL;
    while (current_token)
    {
        if (current_token->type == WORD)
        {
            size = 0;
            first_word = current_token;
            while (current_token->type == WORD)
            {
                size++;
                current_token = current_token->next;
            }
            cmd_arg = (char **)malloc(sizeof(char *) * (size + 1));
            int i = 0;
            while (i < size)
            {
                cmd_arg[i] = ft_strdup(first_word->value);
                first_word = first_word->next;
                i++;
            }
            cmd_arg[i] = NULL;
        }
        if (current_token->type == REDIR_GREATER || current_token->type == REDIR_LESSER || current_token->type == DOUBLE_GREATER)
        {
            if (!redirection)
                redirection = initial_redirection(current_token->type,current_token->next->value);
            else
                add_redirection(redirection,current_token->type,current_token->next->value);
            current_token = current_token->next;
        }
        if (current_token->type == PIPE || current_token->type == SEMICOLON || current_token->type == NEWLINE)
        {
            if (cmd != NULL)
            {
                add_cmd(cmd, cmd_arg, redirection, current_token->type);
                //for (int i = 0; i < size; i++)
                    //free(cmd_arg[i]);
                free(cmd_arg);
                redirection = NULL;
            }
            else
            {
                cmd = initial_cmd(cmd_arg, redirection, current_token->type);
                for (int i = 0; i < size; i++)
                    free(cmd_arg[i]);
                free(cmd_arg);
                //destroy_redirection_list(&redirection);
                redirection = NULL;
            }
            //display_commands(cmd);
            //add_cmd(cmd,cmd_arg,redirection);
            //curr_cmd->redirection = NULL;
            //free(cmd->command);
            //curr_cmd->next = NULL;
            //curr_cmd->next = malloc(sizeof(t_command));
            //curr_cmd = curr_cmd->next;
        }
        //if (current_token->type == SEMICOLON || current_token->type == NEWLINE)
       // {
        //    free(cmd_arg);
            //break;
       // }
        current_token = current_token->next;
    }
    return(cmd);
}