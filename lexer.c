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

t_list        *initialize_list()
{
    t_list *first_token;
    //first_token->index = 0;
    first_token->type = NONE;
    first_token->value = NONE;
    first_token->next = NULL;
    return (first_token);
}

void        add_token(t_list *var,char *type,char *value)
{
    t_list *new_token;

    new_token = var;
    while (new_token->next != NULL)
        new_token = new_token->next;
    new_token->next->type = type;
    new_token->next->value = value;
    
}
void        get_symbole(t_list *var, char *line, int i)
{
    char *token;
    if (line[i] == '|')
    {
        if (line[i + 1] == '|')
            token = ft_strdup("||");
        else
            token = strdup("|");
        add_token(var,PIPE,token);
    }
    if (line[i] == ';')
    {
        if (line[i + 1] == ';')
            token = ft_strdup(";;");
        else 
            token = ft_strdup(";");
        add_token(var, SEMICOLON, token);
    }
    if (line[i] == '>')
    {
        if (line[i + 1] == '>')
            token = ft_strdup(">>");
        else
            token = ft_strdup(">");
        add_token (var, REDIR_GREATER, token);
    }
    if (line[i] == '<')
    {
        if (line[i + 1] == '<')
            token = ft_strdup("<<");
        else
            token = ft_strdup("<");
        add_token (var, REDIR_LESSER, token);
    }
    
}

int        get_word(t_list *var, s_quote *qot, char *line, int i)
{
    char *token;
    //char *Double_Quote;
    //char *Single_Quote;

    int j;
    int l = 0;
    if (line[i] == '"')
    {
        j = i; 
        j++;
        while (line[j] != '\0' && line[j] != '"')
            j++;
        qot->Double_Quote = ft_substr(line,i,(j - i));
        return (j);
    }
    else if (line[i] == '\'')
    {
        j = i;
        j++;
        while (line[j] != '\0' && line[j] != '\'')
            j++;
        qot->Single_Quote = ft_substr(line,i,(j - i));
        return(j);
    }
    // while ((line[i] != '\0') && (ft_strchr("|;> <",line[i]) == NULL))
    // {
    //     token[l] = line[i];
    //     l++;
    //     i++;
    // }
    return (i);
}

t_list      *ft_lexer(char *line)
{
    t_list *var;
    s_quote *qot;
    char *token;
    int i;
    int j;
    
    i = 0;
    j = 0;
    var = initialize_list();
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == '|' || line[i] == ';' || line[i] == '>' || line[i] == '<')
            get_symbole(var,line,i++);
        while ((line[i] != '\0') && (ft_strchr("|;> <",line[i] == NULL)))
        {
            if (line[i] == '"' || line[i] == '\'')
            {
                i = get_word(var, qot, line, i);
               // token = ft_strjoin(token, )
            }else
                token[j++] = line[i];
            i++;
        }

    }
    return (var);
}