/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:13:17 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/23 16:13:35 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list        *initialize_list()
{
    t_token_list *first_token;
    first_token = malloc(sizeof(t_token_list));
    //first_token = NULL;
    //first_token->index = 0;
    first_token->type = NONE;
    first_token->value = ft_strdup("NONE");
    first_token->next = NULL;
    return (first_token);
}

void        add_token(t_token_list *var,char *type,char *value)
{
    t_token_list *new_token;

    new_token = var;
    while (new_token->next != NULL)
        new_token = new_token->next;
    new_token->next = malloc(sizeof(t_token_list));
    new_token->next->type = type;
    new_token->next->value = value;
    new_token->next->next = NULL;
    
}

void        display_token(t_token_list *var)
{
    while (var != NULL)
    {
        write(1,Purple,ft_strlen(Purple));
        write(1,"{",1);
        ft_putstr_fd(var->value,1);
        write(1,"}",1);
        ft_putstr_fd(" type : {",1);
        ft_putstr_fd(var->type,1);
        write(1,"}",1);
        write(1,"\n",1);
        var = var->next;
    }
}

void        get_symbole(t_token_list *var, char *line, t_str *index)
{
    char *token;
    int i;

    i = index->i;
    if (line[i] == '|')
    {
        if (line[i + 1] == '|')
        {
            token = ft_strdup("||");
            i++;
        }
        else
            token = strdup("|");
        add_token(var,PIPE,token);
    }
    if (line[i] == ';')
    {
        if (line[i + 1] == ';')
        {
            token = ft_strdup(";;");
            i++;
        }
        else 
            token = ft_strdup(";");
        add_token(var, SEMICOLON, token);
    }
    if (line[i] == '>')
    {
        if (line[i + 1] == '>')
        {
            token = ft_strdup(">>");
            add_token (var, DOUBLE_GREATER, token);
            i++;
        }
        else
        {
            token = ft_strdup(">");
            add_token (var, REDIR_GREATER, token);
        }
    }
    if (line[i] == '<')
    {
        if (line[i + 1] == '<')
        {
            token = ft_strdup("<<");
            i++;
        }
        else
            token = ft_strdup("<");
        add_token (var, REDIR_LESSER, token);
    }
    index->i = i;
}

char        *Treat_Quotes(t_str *index, char *line)
{
    char *Double_Quote;
    char *Single_Quote;

    int backslash;
    int j;
    if (line[index->i] == '"')
    {
        j = index->i; 
        j++;
        while (line[j] != '\0' && line[j] != '"')
        {
            if (line[j] == '\\')
            {
                backslash = check_backslash(line, j);
                if (backslash % 2 != 0)
                {
                    //Double_Quote = ft_strjoin(Double_Quote, ft_substr(line, j, backslash + 1));
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
        Double_Quote = ft_substr(line,index->i,(j - index->i + 1));
        index->i = j;
        return (Double_Quote);
    }
    else if (line[index->i] == '\'')
    {
        j = index->i;
        j++;
        while (line[j] != '\0' && line[j] != '\'')
        {
            if (line[j] == '\\')
            {
                backslash = check_backslash(line, j);
                if (backslash % 2 != 0)
                {
                    //Double_Quote = ft_strjoin(Double_Quote, ft_substr(line, j, backslash + 1));
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
        Single_Quote = ft_substr(line,index->i,(j - index->i + 1));
        index->i = j;
        return(Single_Quote);
    }
    return (NULL);
}

int         check_backslash(char *line, int i)
{
    int backslash;

    backslash = 0;
    while (line[i++] == '\\')
    {
        backslash++;
    }
    return(backslash);
}

t_token_list      *ft_lexer(char *line)
{
    t_token_list *var;
    t_str index;
    char *token; 
    char *str;
    int backslash = 0;
    // while (line[i] != '\0')
    // {
    //     if (line[i] == '"' && backslash == 0)
    //         treat_double_quotes();
    //     if (line[i] == '\\' && backslash == 0)
    //         backslash = 1;
    //     else
    //         backslash = 0;
    //     i++;
    // }
    token = ft_strdup("");
    index.i = 0;
    var = NULL;
    var = initialize_list();
    while (line[index.i])
    {
        //backslash = check_backslash(line, index.i);
        while ((line[index.i] == ' ' || line[index.i] == '\t'))
            index.i++;
        if (line[index.i] == '|' || line[index.i] == ';' || line[index.i] == '>' || line[index.i] == '<')
        {
            get_symbole(var,line,&index);
            index.i++;
        }
        while ((line[index.i] != '\0') && (ft_strchr("|;> <\t",line[index.i]) == NULL))
        {
            backslash = check_backslash(line, index.i);
            if (backslash % 2 != 0)
            {
                token = ft_strjoin(token, ft_substr(line, index.i, backslash + 1));
                index.i = index.i + backslash;
                backslash = 0;
            }
            else if (line[index.i] == '"' || line[index.i] == '\'')
            {
                //index->i = get_word(var, index, line);
                token = ft_strjoin(token, Treat_Quotes(&index, line));
            }else
            {
                if (backslash > 0)
                {
                    token = ft_strjoin(token, ft_substr(line, index.i, backslash));
                    index.i = index.i + backslash - 1;
                    backslash = 0;
                }else
                {
                    str = ft_strjoin(token, ft_substr(line, index.i, 1));
                    free(token);
                    token = str;
                }
                
            }
            index.i++;
        }
        if ( ft_strcmp(token, "") != 0)
        {
            add_token(var, WORD, token);
            token = ft_strdup("");
        }
    }
    add_token(var, NEWLINE, ft_strdup("NEWLINE"));
    return (var);
}

