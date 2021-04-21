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

// char    *ft_new_str(char *str, int c)
// {

//     int i = -1;
//     while (str[++i])
//     {
//         if (str[i] == c)
//             str[i] = str[i + 1];    
//     }
//     return (str);
// }

void    ft_new_str(char *str, int index)
{
    while (str[index] != '\0')
    {
        str[index] = str[index + 1];
        index++;
    }
}

int        expand_double_quotes(char **str, int index, t_env *env_list)
{
    //index++;
    // if (str[index] == '"')
    // {
    //     ft_new_str(str, index);
    //     index--;
    // }
    // else 
    // {
        
        while ((*str)[index] != '\0')
        {
            //index++;
            if ((*str)[index] == '\\')
            {
                if (ft_strchr("\\`$\"",(*str)[index + 1]) != NULL)
                {
                    ft_new_str((*str), index);
                }
                //else if (str[index + 1] == '$')
                   // ft_new_str(str, index--);
            }
            else if ((*str)[index] == '$' && (ft_strchr("\" \t", (*str)[index + 1]) == NULL))
                (*str) = take_dollar_name((*str), &index, env_list);
            else if ((*str)[index] == '"')
            {
                ft_new_str((*str), index);
                index--;
                break;
            }
            index++;
        }
    // }
    return(index);
}

int         expand_single_quote(char *str, int index)
{
    //if (str[index] == '\'')
    //{
    //    ft_new_str(str, index);
     //   index--;
   // }
   // else 
    //{
        while (str[index] != '\0')
        {
            if (str[index] == '\'')
            {
                ft_new_str(str, index);
                index--;
                break;
            }
            index++;
        }
    //}
    return (index);
}

char            *get_dollar_name(char *command,int *j)
{
    char *name;
    int i;

    i = *j;
    name = ft_strdup("");
        
    while (command[i] != '\0' && ft_strchr("\\' `$\":/",command[i]) == NULL)
    {
        name = ft_strjoin(name, ft_substr(command, i, 1));
        i++;
    }
    *j = i;
    return(name);
}

char            *after_dollar_value(char *command1, int i)
{
    char *after_dollar;
    int j;
    int start;

    j = 0;
    start = i;
    while (command1[i++] != '\0')
        j++;
    after_dollar = ft_substr(command1,start, j);
    return (after_dollar);
}

// char *ft_strcpy(char *dest, char *src)
// {
// 	int i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

char            *take_dollar_name(char *comd, int *k, t_env *envl)
{
    char *name;
    char *old_comd;
    char *after_dollar;
    int i;
    size_t len;


    i = *k;
    len = 0;
    old_comd = ft_substr(comd,0,i);
    if (ft_strchr("\\ \0",comd[i + 1]) == NULL)
        ft_new_str(comd,i);
    if (ft_isdigit(comd[i]) == 1)
        name = ft_substr(comd,i++,1);
    else
        name = get_dollar_name(comd, &i);
    *k = i;
    
    after_dollar = after_dollar_value(comd, i);
    if (ft_strcmp(name, "") != 0)
    {
        if (ft_strcmp(name,"0") == 0)
        {
            len = ft_strlen(old_comd) + ft_strlen("bash");
            comd = ft_strjoin(old_comd,"bash");
        }
        else
        {
            while (envl != NULL)
            {
                if (ft_strcmp(name,envl->name) == 0)
                {
                    len = ft_strlen(old_comd) + ft_strlen(envl->value);
                    comd = ft_strjoin(old_comd,envl->value);
                    break;
                }
                else
                {
                    len = 1;
                    comd = ft_strjoin(old_comd,"");
                }
                envl = envl->next;
            }
        }
        *k = len - 1;
    }
    else
    {
        len = ft_strlen(old_comd);
        comd = ft_strjoin(old_comd,"");
    }
    comd = ft_strjoin(comd,after_dollar);
    return(comd);
}

void       expanding(t_command *cmd, t_env *env_lst)
{
    t_redirection *current_redir_list;
    int i,j;
    i = 0;
    j = 0;
    //while (cmd->seperator != 1 && cmd->seperator != 2)
   // {
        //while (cmd->command != NULL)
       // {
    //printf("before expanding[%s]\n",cmd->command[0]);
    //printf("before expanding[%s]\n",cmd->command[1]);
        if (cmd->command != NULL)
        {
            i = 0;
            while (cmd->command[i] != NULL)
            {
                j = 0;
                while (cmd->command[i][j] != '\0')
                {
                    //printf("char[%c]\n",cmd->command[i][j]);
                    if (cmd->command[i][j] == '$')
                        cmd->command[i] = take_dollar_name(cmd->command[i], &j, env_lst);
                    if (cmd->command[i][j] == '\\')
                    {
                        //if (ft_strchr("\\`$\"",cmd->command[i][j + 1]) != NULL)
                        //{
                            ft_new_str(cmd->command[i], j);
                            //j++;
                        //}
                    }
                    else if (cmd->command[i][j] == '"')
                    {
                        ft_new_str(cmd->command[i], j);
                        j = expand_double_quotes(&cmd->command[i], j, env_lst);
                        //j--;
                    }else if (cmd->command[i][j] == '\'')
                    {
                        ft_new_str(cmd->command[i], j);
                        j = expand_single_quote(cmd->command[i], j);
                        //j--;
                    }
                    j++;
                }
                i++;
            }
        }
        if (cmd->redirection)
        {
            current_redir_list = cmd->redirection;
            while (current_redir_list)
            {
                i = 0;
                while (current_redir_list->file[i] != '\0')
                {
                    if (current_redir_list->file[i] == '$')
                       current_redir_list->file = take_dollar_name(current_redir_list->file, &i, env_lst);
                    if (current_redir_list->file[i] == '\\')
                        ft_new_str(current_redir_list->file, i);
                    else if (current_redir_list->file[i] == '"')
                    {
                        ft_new_str(current_redir_list->file, i);
                        i = i + expand_double_quotes(&current_redir_list->file, i, env_lst);
                    }else if (current_redir_list->file[i] == '\'')
                    {
                        ft_new_str(current_redir_list->file, i);
                        i = i + expand_single_quote(current_redir_list->file, i);
                    }
                    i++;
                }
                current_redir_list = current_redir_list->next;
            }
        }
        //printf("after expanding[%s]\n",cmd->command[i - 2]);
       // printf("after expanding[%s]\n",cmd->command[i - 1]);
    //}
}

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

int			quotes_end(char *value, int *k)
{
	int backslash;
    int j;

    j = *k;
    j++;
	backslash = 0;
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
    *k = j;
    if (value[j] == '"')
        return(1);
    else //if (value[j] != '\0')
        return(-1);
	//return (j);
}

int         single_quote_end(char *value, int *k)
{
    int j;

    j = *k;
    j++;
    while (value[j] != '\0' && value[j] != '\'')
        j++;
    *k = j;
    if (value[j] == '\'')
        return(1);
    else 
        return(-1);
}

int         check_quotes(char *value)
{
    int j;
    int backslash;
    int result;
    //char c;

    j = 0;
    backslash = 0;
    result = 0;
    while (value[j])
    {
        if (value[j] == '\"')
        {
            //c = value[j];
            //j++;
            result = quotes_end(value, &j);
        }
        else if (value[j] == '\'')
        {
            result = single_quote_end(value, &j);
            //printf("result:{%d}index:{%d}value:{%c}\n",result, j, value[j]);
        }
        else if (value[j] == '\\')
        {
            if (check_backslash(value, j) % 2 != 0)
                j++;
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

int        check_syntax_error(t_token_list *token_lst)
{
    int result;

    result = 0;
    while (token_lst->type != NEWLINE)
    {
        if (token_lst->type == NONE)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                result = 1;
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                destroy_list(token_lst);
                result = 1;
                break;
            }
        }
        else if (token_lst->type == REDIR_GREATER || token_lst->type == REDIR_LESSER || token_lst->type == DOUBLE_GREATER)
        {
            if (token_lst->next->type != WORD)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                result = 1;
                break;
            }
            // else if (token_lst->next->type == NEWLINE)
            // {
            //     display_error(token_lst->next->value);
            //     destroy_list(token_lst);
            //     break;
            // }
        }
        else if (token_lst->type == PIPE)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                result = 1;
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                result = 1;
                break;
            }      
        }
        else if (token_lst->type == WORD)
        {
            if (((check_backslash_end(token_lst->value))) % 2 != 0)
            {
                write(1,RED,ft_strlen(RED));
                ft_putstr_fd("syntax error multiple line not allowedback\n",1);
                write(1,RESET,ft_strlen(RESET));
                destroy_list(token_lst);
                result = 1;
                break;
            }
            if (check_quotes(token_lst->value) == -1)
            {
                write(1,RED,ft_strlen(RED));
                ft_putstr_fd("syntax error multiple line not allowed\n",1);
                write(1,RESET,ft_strlen(RESET));
                destroy_list(token_lst);
                result = 1;
                break;
            }
        }
        else if (token_lst->type == SEMICOLON)
        {
            if (token_lst->next->type == PIPE || token_lst->next->type == SEMICOLON)
            {
                display_error(token_lst->next->value);
                destroy_list(token_lst);
                result = 1;
                break;
            }
            else if (token_lst->next->type == NEWLINE)
            {
                destroy_list(token_lst);
                result = 1;
                break;
            }
        }
        token_lst = token_lst->next;
    }
    return (result);
}
