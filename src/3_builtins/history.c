/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 14:29:37 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    save_history(t_mbox *mbox, char *inp_hist)
{
    t_history   *cur;
    t_history   *new_inp;
    static int  i;

    new_inp = ft_calloc(1, sizeof(t_history));
    if (!new_inp)
        return ;
    new_inp->inp_hist = ft_strdup(inp_hist);
    new_inp->inp_count = ++i;
    if (!mbox->history)
        mbox->history = new_inp;
    else
    {
        cur = mbox->history;
        while (cur->next)
            cur = cur->next;
        cur->next = new_inp;    
    }    
}

void    builtin_history(t_mbox *mbox, t_ast *arg_node)
{
    t_history   *cur;

    cur = mbox->history;
    while (cur)
    {
        printf ("  %d  %s\n", cur->inp_count, cur->inp_hist); //TODO: write to the CMD FD
        cur = cur->next;
    }
}

void    free_history(t_mbox *mbox)
{
    t_history   *cur;
    t_history   *temp;

    cur = mbox->history;
    while (cur)
    {
        temp = cur;
        cur = cur->next;
        if (temp)
        {
            free(temp->inp_hist);
            free(temp);
        }
    }
    mbox->history = NULL;
}
