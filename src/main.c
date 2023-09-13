/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/09/13 17:02:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	running;

int	main(int argc, char **argv, char** envp)
{
	char	*current_input;

	(void)argc;
	(void)argv;
	running = true;

	while (running)
	{
		current_input = readline("MINI-HELL->");
		// do stuff with the command
		if (parse_input(current_input) == ft_false)
		running = ft_false;
		free(current_input);
	}
	return (0);
}
