/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:13:15 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 19:42:35 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static char	*substr_part_expand(char *auxstr)
{
	int	i;

	i = 1;
	if (!auxstr)
		return (NULL);
	while (auxstr[i] && auxstr[i] != ' ' && auxstr[i] != '\n'
		&& auxstr[i] != '	' && auxstr[i] != '"' && auxstr[i] != '\''
		&& auxstr[i] != '$')
		i++;
	return (ft_substr(auxstr, 1, i - 1));
}

static char	*replace_substr(char *prompt, char *old_str, char *new_str)
{
	int		i;
	char	*aux;
	char	*aux2;

	i = 0;
	aux = NULL;
	aux2 = NULL;
	if (!prompt || !old_str || !new_str)
		return (NULL);
	while (prompt[i] != '$' && prompt[i])
		i++;
	if (i != 0)
	{
		aux = ft_substr(prompt, 0, i);
		aux2 = ft_strjoin(aux, new_str);
		if (!aux || !aux2)
			return (NULL);
		free(aux);
		if (&prompt[i + ft_strlen(old_str)])
			aux = ft_strjoin(aux2, &prompt[i + ft_strlen(old_str)]);
		free(aux2);
	}
	else
		aux = ft_strjoin(new_str, &prompt[ft_strlen(old_str)]);
	return (aux);
}

char	*expand_content(char *str, t_myshell *ms)
{
	char	*dollar;
	char	*aux3;
	char	*aux2;
	int		i = 0;

	dollar = substr_part_expand(ft_strchr(str, '$'));
	aux3 = ft_strjoin(dollar, "=");
	while (ms->environ[i])
	{
		if (ft_strncmp(aux3, ms->environ[i],
				ft_strlen(aux3)) == 0)
		{
			aux2 = ft_semi_strtrim(ms->environ[i], aux3);
			free(aux3);
			free(dollar);
			return (aux2);
		}
		i++;
	}
	free(aux3);
	free(dollar);
	return (NULL);
}

int	expander(t_myshell *tshell)
{
	char	*dollar;
	char	*new_content;
	char	*res;
	t_token	*aux;

	aux = tshell->tokens;
	while (aux)
	{
		if ((aux->symbol == D_QUOTE || aux->symbol == WORD)
			&& ft_strchr(aux->content, '$') && (ft_strcmp(aux->content, "$")
			!= 0 || ft_strcmp(aux->content, "$$") != 0
			|| ft_strcmp(aux->content, "$?") != 0))
		{
			new_content = expand_content(aux->content, tshell);
			res = substr_part_expand(ft_strchr(aux->content, '$'));
			dollar = ft_strjoin("$", res);
			free(res);
			res = replace_substr(aux->content, dollar, new_content);
			ft_free2(new_content, aux->content);
			aux->content = res;
			free(dollar);
			continue ;
		}
		aux = aux->next;
	}
	return (0);
}

int ft_expander(t_myshell *ms)
{
	if (ms->exit_status != EXIT_SUCCESS)
		return (ms->exit_status);
	ms->exit_status = expander(ms);
	return (ms->exit_status);
}
