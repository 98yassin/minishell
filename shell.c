/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:40:13 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/20 14:40:16 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int     main()
{
    t_var var;
    int r;
    while (1)
    {
        ft_putstr_fd("\e[1;32mMy_Minishell $>\e[0m", 0);
        r = get_next_line(0, &var.line);
        ft_putstr_fd(var.line, 0);
		write(1, "\n",1);
        if (ft_strcmp((const char*)var.line,"exit") == 0)
        {
            free(var.line);
            break;
        }
    }
    return 0;
}
