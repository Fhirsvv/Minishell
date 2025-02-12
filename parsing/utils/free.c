/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:04:19 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/02 12:20:02 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	free_minishell(t_myshell *tshell)
{
	ft_free(tshell->prompt);
	free_tokens(&tshell->tokens);
	//free_comands(&tshell->comands);
}

int	ft_free(char *s)
{
	if (!s)
		return (1);
	free(s);
	s = NULL;
	return (1);
}

void	ft_free2(char *arr1, char *arr2)
{
	ft_free(arr1);
	ft_free(arr2);
}

void	free_tokens(t_token **tk)
{
	t_token	*next;

	while (*tk)
	{
		next = (*tk)->next;
		ft_free((*tk)->content);
		free((*tk));
		*tk = next;
	}
	*tk = NULL;
}
