/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/27 09:58:35 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
   finds a corresponding whitespace character and returns it
   so the rest part of the input starts with a correct character 
*/
char    find_limiter(char *input, int i)
{
    input++;
    while (ft_isalnum(input[i]) || input[i] == '_')
        i++;
    return (input[i]);    
}

/*
    if a variable key was correct this fucntion gets the parts of the string 
    which are located before and after the variable name, then expands 
    the variable, and then join all the 3 parts, if a key wasn't correct, 
    it joins what was before and after the variable
*/
char    *insert_var_val(char *input, char *var_key, char *var_val, bool found)
{
    char    *first_part;
    char    *rest_part;
    char    *inserted;
    int     first_part_len;
    
    rest_part = ft_strchr(input, '$');
    rest_part = ft_strchr(rest_part, find_limiter(rest_part, 0));
    first_part_len = ft_strlen(input)
		- ft_strlen(rest_part) - (ft_strlen(var_key) + 1); 
    first_part = ft_substr(input, 0, first_part_len);
    if (found == true)
        inserted = ft_strcat_multi(3, first_part, var_val, rest_part);
    else
        inserted = ft_strcat_multi(2, first_part, rest_part);
    free (input);
	free (first_part);
    return (inserted);
}


// TODO: ALex will code this in the env.c file
char *get_var(char *cur_key)
{
    (void)cur_key;
    char *temp_message = ft_calloc(9, sizeof(char));
    temp_message = "|SOON!|";
    return(temp_message);
}

// 1. Loop trough qouted_input
// 2. If we find a $ and are not in qoute_state= single quote
//  TRUE
//      3.1.    Find end of var key (so we have the key)
//      3.2.    Expand var key to value...
//      3.3.    ... and replace in string
//          Subcase
//              only a $
//              $?
//  FALSE
//      4.1.    Remove Quotes but print var key including $
/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
    by their values which are received from environment
*/
void	expand_variables(t_minibox *minibox, int k, int k_end, int quote_state)
{
    char    *cur_key;
    char    *cur_value;
    char    cur_char;
    
    quote_state = OUT_Q;
    minibox->input_expanded = ft_strdup(minibox->input_quoted);
    while(minibox->input_quoted[k])
    {
        cur_char = minibox->input_quoted[k];
        if((cur_char == IN_SQ || cur_char == IN_DQ) && quote_state == OUT_Q)
            quote_state = cur_char;
        else if(quote_state == cur_char)
            quote_state = OUT_Q;
        if(quote_state != IN_SQ && cur_char == '$')
        {
            k++; //skipping the $ sign
            k_end = k;
            while (ft_isalnum(minibox->input_quoted[k_end]) ||  minibox->input_quoted[k_end] == '_')
            {
                k_end++;
            }
	        cur_key = ft_substr(minibox->input_quoted, k, k_end - k); //TODO:FREE IT
            // TODO: cur_key is "$" or "$?" -> treat special cases
            cur_value = get_var(cur_key); //IF key doesnt exist function returns NULL
            if (cur_value)
                minibox->input_expanded = insert_var_val(minibox->input_expanded, cur_key, cur_value, true);
            else
                minibox->input_expanded = insert_var_val(minibox->input_expanded, cur_key, cur_value, false);
        }            
        k++;
    }
}