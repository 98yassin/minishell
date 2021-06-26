/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 10:57:01 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/13 10:57:08 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./libft/libft.h"
#include <stdio.h>
#include <string.h>


// char    *ft_new_str(char *str, char c)
// {

//     int i = -1;
//     char *result;
//     int len;
//     len = strlen(str);
//     result = strdup("");
//     while (str[++i])
//     {
//         //printf("hna\n");
//         if (str[i] == c)
//         {
//             //printf("hna:%d\n",i);
//                 //str[i] = str[i + 1];  
//                 result =ft_strjoin(result,ft_substr(str,i + 1,len - i + 1));

//         }else
//         {
//             result
//         }
        
//     }
//     return (result);
// }

// void    ft_new_str(char *str, int c)
// {
//     // char *rslt;
//     int i = -1;
//     // int j = 0;
//     // rslt = (char *)malloc(sizeof(char) * 11 + 1);
//     while (str[++i])
//     {
//         // printf("{%d}\n",i);
//         if (str[i] == c)
//             str[i] = str[i + 1];
//         // rslt[j] = str[i];
//     }
// }

// int main()
// {
    
//     char *s1;
//     s1 = (char *)malloc(sizeof(char) * 14 + 1);
//     s1 = "hel'lo 'wor'ld";
//     //char *s2;
//    ft_new_str(s1,'\'');
//     printf("{%s}\n",s1);

//     return 0;
// }

void    ft_new_str(char **str, int index)
{
    while ((*str)[index] != '\0')
    {
            (*str)[index] = (*str)[index + 1];
            index++;
    }
}

int main()
{
    
    char *s1;
    //s1 = (char *)malloc(sizeof(char) * 14 + 1);
    s1 = strdup("hel'lo 'wor'ld");
    int i = -1;
    while (s1[++i])
    {
      if (s1[i] == '\'')
      {
        ft_new_str(&s1, i);
        break;
      }
    }
    //char *s2;
   
    printf("{%s}\n",s1);

    return 0;
}