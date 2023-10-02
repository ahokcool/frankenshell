/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/02 18:43:23 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *token_list_case1(t_minibox *minibox);
static t_tree *token_list_case2(t_minibox *minibox);
static t_tree *token_list_case3(t_minibox *minibox);

t_tree *token_list_main(t_minibox *minibox)
{
    t_tree  *tl_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return (NULL);
    tl_node = token_list_case1(minibox);
    if (tl_node)
        return (tl_node);
    minibox->tmp_token = backup;
    tl_node = token_list_case2(minibox);
    if (tl_node)
        return (tl_node);
    minibox->tmp_token = backup;
    //TODO: add a third case
    return (NULL);
}
/* [name]  <token list> */
static t_tree *token_list_case1(t_minibox *minibox)
{
    // char    *name;

    if (minibox->tmp_node->content)
        return (NULL);
    if (minibox->tmp_token->type == WORD_TOKEN) {
        minibox->tmp_node->content = ft_strdup(minibox->tmp_token->value);
        if (minibox->tmp_token)
            minibox->tmp_token = minibox->tmp_token->next;
        token_list(minibox);
        return (minibox->tmp_node);
    }
    return (NULL);
}
/* [token] <token list> */
static t_tree *token_list_case2(t_minibox *minibox)
{
    // char    *arg;
    t_tree  *arg_node;

    if (minibox->tmp_token->type != WORD_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);
    arg_node = ast_create_node(ARG_NODE);
    arg_node->content = ft_strdup(minibox->tmp_token->value);
    if (minibox->tmp_token)
        minibox->tmp_token = minibox->tmp_token->next;
    token_list(minibox);
    connect_subtree(&minibox->tmp_node, arg_node, 1);
    return (arg_node);
}

/* <redir> <token list> */ 
static t_tree *token_list_case3(t_minibox *minibox)
{
    t_tree  *redir_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return (NULL);

    if ((minibox->tmp_token->type != RED_IN_TOKEN)
        || (minibox->tmp_token->type != RED_IN_TOKEN))
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);
    redir_node = redir_main(minibox);
    redir_node->content = ft_strdup(minibox->tmp_token->value);
    if (minibox->tmp_token)
        minibox->tmp_token = minibox->tmp_token->next;
    token_list(minibox);
    connect_subtree(&minibox->tmp_node, redir_node, 1);
    return (redir_node);
}