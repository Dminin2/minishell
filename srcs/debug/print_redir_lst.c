/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redir_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:08 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/16 11:48:27 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_lst(t_list *head)
{
	t_redir *redir;
	int i;

	printf("  Rdirections:\n");
	i = 1;
	while (head)
	{
		redir = head->content;
		printf("    [%d]\n", i);
		printf("      value : %s\n", redir->value);
		if (redir->type == R_IN)
			printf("      type  : R_IN\n");
		else if (redir->type == R_OUT)
			printf("      type  : R_OUT\n");
		else if (redir->type == R_HEREDOC)
			printf("      type  : R_HEREDOC\n");
		else if (redir->type == R_APPEND)
			printf("      type  : R_APPEND\n");
		else
			printf("      type  : null\n");
		head = head->next;
		i++;
	}
}
