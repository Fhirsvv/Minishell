/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:38:35 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 18:59:47 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	**add_to_matrix(char **arr, char *new)
{
	char	**aux;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (arr)
	{
		while (arr[i])
			i++;
		aux = malloc((i + 2) * sizeof(char *));
		if (!aux)
			return (NULL);
		while (k < i)
		{
			aux[k] = ft_strdup(arr[k]);
			k++;
		}
	}
	else
		aux = malloc((i + 2) * sizeof(char *));
	aux[k] = ft_strdup(new);
	aux[k + 1] = NULL;
	free_arr(arr);
	return (aux);
}

void ft_copy(char *dst, char *src)
{
	int i;

	i = 0;
	if (!dst || !src)
		return ;
	while (dst[i] && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return ;
}

t_com *new_t_com()
{
	t_com *new;

	new = malloc(sizeof(t_com));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->files = NULL;
	new->env_path = NULL;
	new->next = NULL;
	return (new);
}

int is_redir(t_token *t_next)
{
	if (t_next->symbol == REDIR_D || t_next->symbol == REDIR_I
		|| t_next->symbol == DOBLE_REDIR_D)
		return (1);
	return (0);
}

int is_word(t_token *t_next)
{
	if (t_next->symbol == WORD ||t_next->symbol == D_QUOTE
		|| t_next->symbol == S_QUOTE)
		return (1);
	return (0);
}
