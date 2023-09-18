/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/09/18 16:20:55 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	running;

int	main(int argc, char **argv, char** envp)
{
	char	*current_input;

	(void)argc;
	(void)argv;
	(void)envp;
	running = true;

	while (running)
	{
		// hey Alex, what about call out shell as "panzer-shell"?
		current_input = readline("MINI-HELL-> ");
		// do stuff with the command
		if (parse_input(current_input) == ft_false)
		running = ft_false;
		free(current_input);
	}
	return (0);
}