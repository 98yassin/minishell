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
    first_token->type = NONE;
    first_token->value =  ft_strdup("NONE");
    first_token->next = NULL;
    return (first_token);
}

void        add_token(t_token_list *var,char *type,char *value)
{
    t_token_list *new_token;

    new_token = var;
    while (new_token->next != NULL)
        new_token = new_token->next;
    new_token->next = (t_token_list *)malloc(sizeof(t_token_list));
    new_token->next->type = type;
    new_token->next->value = value;
    new_token->next->next = NULL;
    
}

void        display_token(t_token_list *var)
{
    while (var != NULL)
    {
		printf("%s{%s} type : {%s}\n%s", PURPLE, var->value, var->type, RESET);
        var = var->next;
    }
}

int         get_pipe_symbole(t_token_list *var, char *line, int i)
{
    char *token;

    if (line[i + 1] == '|')
        {
            token = ft_strdup("||");
            i++;
        }
        else
        {
            token = strdup("|");
        }
        add_token(var,PIPE,token);
        return(i);
}

int         get_semi_symbole(t_token_list *var, char *line, int i)
{
    char *token;

    int k = i + 1;
        int rslt = 0;
        while (line[k])
        {
            if (ft_strchr(" \t", line[k]) == NULL)
            {
                rslt = 1;
                break;
            }
            k++;
        }
        if (rslt == 1)
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
        return(i);
}

int         get_rg_symbole(t_token_list *var, char *line, int i)
{
    char *token;
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
        return(i);
}

int         get_rl_symbole(t_token_list *var, char *line, int i)
{
    char *token;
    if (line[i + 1] == '<')
        {
            token = ft_strdup("<<");
			add_token (var, DOUBLE_LESSER, token);
            i++;
        }
        else
		{
            token = ft_strdup("<");
        	add_token (var, REDIR_LESSER, token);
		}
        return(i);
}

void        get_symbole(t_token_list *var, char *line, int *index)
{
    int i;

    i = *index;
    if (line[i] == '|')
        i = get_pipe_symbole(var, line, i);
    if (line[i] == ';')
        i = get_semi_symbole(var, line, i);
    if (line[i] == '>')
        i = get_rg_symbole(var, line ,i);
    if (line[i] == '<')
        i = get_rl_symbole(var, line, i);
    *index = i;
}

char        *Treat_Quotes(int *index, char *line, char type)
{
    char *Double_Quote;
    //char *Single_Quote;

    int backslash;
    int j;
    int i;

    i = *index;
    //if (line[i] == type)
    //{
        j = i; 
        j++;
        while (line[j] != '\0' && line[j] != type)
        {
            if (line[j] == '\\')
            {
                backslash = check_backslash(line, j);
                if (backslash % 2 != 0)
                    j = j + backslash;
                else
                    j = j + backslash - 1;
                backslash = 0;
            }
            j++;
        }
        Double_Quote = ft_substr(line,i,(j - i + 1));
        *index = j;
        return (Double_Quote);
    //}
    // else if (line[i] == '\'')
    // {
    //     j = i;
    //     j++;
    //     while (line[j] != '\0' && line[j] != '\'')
    //     {
    //         if (line[j] == '\\')
    //         {
    //             backslash = check_backslash(line, j);
    //             if (backslash % 2 != 0)
    //             {
    //                 j = j + backslash;
    //                 backslash = 0;
    //             }else
    //             {
    //                 j = j + backslash - 1;
    //                 backslash = 0;
    //             }
    //         }
    //         j++;
    //     }
    //     Single_Quote = ft_substr(line,i,(j - i + 1));
    //     *index = j;
    //     return(Single_Quote);
    // }
    //return (NULL);
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

void                backslash_impair(char *line, char **token, int *k, int *backslash)
{
    char *str;
    int i;
    char *tmp;

    i = *k;
    str = ft_substr(line, i, *(backslash) + 1);
    tmp = ft_strjoin((*token), str);
    free((*token));
    free(str);
    (*token) = tmp;
    i = i + *(backslash);
    *(backslash) = 0;
    *k = i;
}

void            backslash_exist(char *line, char **token, int *k, int *backslash)
{
    char *str;
    int i;
    char *tmp;

    i = *k;
    str = ft_substr(line, i, *(backslash));
    tmp = ft_strjoin(*(token), str);
    free(*(token));
    free(str);
    (*token) = tmp;
    i = i + *(backslash) - 1;
    *(backslash) = 0;
    *k = i;
}

void                backslash_not_exist(char *line, char **token, int *k)
{
    char *str;
    int i;
    char *tmp;

    i = *k;
    str = ft_substr(line, i, 1);
    tmp = ft_strjoin(*(token), str);
    free(*(token));
    free(str);
    (*token) = tmp;
    *k = i;
}

void                quotes(char **token, int *k, char *line, char type)
{
    char *trt;
    char *tmp;
    int i;
    
    i = *k;
    trt = Treat_Quotes(&i, line, type);
    tmp = ft_strjoin(*(token), trt);
    free(*(token));
    *(token) = tmp;
    free(trt);
    *k = i;
}

char                *get_word(char *line, int *k)
{
    char *token;
    int backslash;
    int i;
    //char *tmp;
    //char *trt;

    token = ft_strdup("");
    backslash = 0;
    i = *k;
    while ((line[i] != '\0') && (ft_strchr("|;> <\t",line[i]) == NULL))
        {
            backslash = check_backslash(line, i);
            if (backslash % 2 != 0)
                backslash_impair(line, &token, &i, &backslash);
            else if (line[i] == '"' || line[i] == '\'')
            {
                quotes(&token, &i, line, line[i]);
                // trt = Treat_Quotes(&i, line, line[i]);
                // tmp = ft_strjoin(token, trt);
                // free(token);
                // token = tmp;
                // free(trt);
            }
            else
            {
                if (backslash > 0)
                    backslash_exist(line, &token, &i, &backslash);
                else
                    backslash_not_exist(line, &token, &i);
            }
            i++;
        }
        *k = i;
        return(token);
}

t_token_list      *ft_lexer(char *line)
{
    t_token_list *var;
    t_var lexer;

    lexer.i = 0;
    //var = NULL;
    var = initialize_list();
    while (line[lexer.i])
    {
        lexer.token = ft_strdup("");
        lexer.tmp =  lexer.token;
        while ((line[  lexer.i] == ' ' || line[lexer.i] == '\t'))
            lexer.i++;
        if (line[  lexer.i] == '|' || line[lexer.i] == ';'
                                || line[lexer.i] == '>' || line[lexer.i] == '<')
        {
            get_symbole(var,line,&lexer.i);
            lexer.i++;
        }
        free(lexer.tmp);
        if ((line[ lexer.i] != '\0') && (ft_strchr("|;> <\t",line[lexer.i]) == NULL))
            lexer.token = get_word(line,&lexer.i);
        if ( ft_strcmp(lexer.token, "") != 0)
            add_token(var, WORD,   lexer.token);
    }
    add_token(var, NEWLINE, ft_strdup("NEWLINE"));
    return (var);
}

