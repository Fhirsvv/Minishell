/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:35:49 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 19:41:52 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	addfile(t_com *comand, t_token *tk)
{
	t_files *new;
	t_files *aux;
	
	if (tk->content == NULL || ft_strlen(tk->content) > 255) //añadir manejo de errores
	return (1);
	new = malloc(sizeof(t_files));
	if (!new)
		return (1);
	ft_copy(new->file_name, tk->content);
	new->type_open = tk->symbol;
	new->next = NULL;
	if (!comand->files)
		comand->files = new;
	else
	{
		aux = comand->files;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	aux = comand->files;
	return (0);
}

int	ft_comand(t_myshell *ms)
{
	t_token	*t_next;
	t_com	*start;
	t_com	*caux;

	start = new_t_com();
	if (!start)
	{
		printf("error new_t_com\n");
		return (1);
	}
	ms->t_com = start;
	t_next = ms->tokens;
	caux = start;
	while (t_next)
	{
		if (is_word(t_next))
		{
			caux->args = add_to_matrix(caux->args, t_next->content);
			if (!caux->args)
			{
				printf("error add_to_matrix new_comand\n");
				return (1);
			}	
		}
		else if (is_redir(t_next))
		{
			if (!t_next->next)
			{
				//el error de $? = 2
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
			else if (addfile(caux, t_next->next)) //que hacer cuando acaba en redir el comando
			{
				printf("error addfile\n");
				return (1);
			}
		}
		else if (t_next->symbol == PIPE)
		{
			caux->next = new_t_com();
			if (!caux->next)
			{
				printf("error new_t_com\n");
				return (1);
			}
			caux = caux->next;
		}
		t_next = t_next->next;
	}
	return (0);
}

int	ft_comands(t_myshell *ms)
{
	if (ms->exit_status != EXIT_SUCCESS)
		return (ms->exit_status);
	ms->exit_status = ft_comand(ms);
	return (ms->exit_status);
}
