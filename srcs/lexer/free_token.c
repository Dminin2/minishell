/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:18:01 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/03 01:18:02 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_wrapper(void *tok)
{
	free_token((t_token *)tok);
}

void	free_token(t_token *tok)
{
	if (tok)
	{
		if (tok->value)
			free(tok->value);
		free(tok);
	}
}
