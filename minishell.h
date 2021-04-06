/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:18:37 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/20 19:18:39 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_h
# define MINISHELL_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "libft/libft.h"
#include "get_next_line.h"

#define GREEN "\e[1;32m"
#define RESET "\e[0m"
#define RED "\e[1;91m"
#define CYAN "\e[1;36m"
#define YELLOW "\e[1;33m"
#define PURPLE "\e[1;35m"
#define BLUE "\e[1;34m"
#define Purple "\033[0;35m"
#define Cyan "\033[0;36m"

#define NONE "NONE"
#define PIPE "PIPE"
#define SEMICOLON "SEMICOLON"
#define REDIR_GREATER "REDIR_GREATER"
#define REDIR_LESSER "REDIR_LESSER"
#define DOUBLE_GREATER "DOUBLE_GREATER"
#define WORD "WORD"
#define NEWLINE "NEWLINE"


typedef struct s_minishell
{
    //int index;
    char *type;
    char *value;
    struct s_minishell *next;
    
}               t_token_list;


typedef struct s_struct
{
    int i;
}               t_str;


typedef struct s_redirection //list of redirections and types
{
    char *type;
    char *file;
    struct s_redirection *next;
    
}               t_redirection;

typedef struct s_command //list of commands
{
    char **command;
    t_redirection *redirection;
    struct s_command *next;

}               t_command;


t_token_list        *ft_lexer(char *line);
void                display_token(t_token_list *var);
int                 check_backslash(char *line, int i);
void                check_syntax_error(t_token_list *token_lst);


t_command       *parce(t_token_list *token_list);

#endif