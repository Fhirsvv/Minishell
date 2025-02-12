/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:02:21 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/01 19:17:45 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_comand	*ft_command_new(char **args, char *c_path)
{
	t_comand	*new;

	new = malloc(sizeof(t_comand));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	new->args = ft_array_duplicate(args);
	new->comand_path = c_path;
	init_fds(&new->fds);
	new->next = NULL;
	return (new);
}
