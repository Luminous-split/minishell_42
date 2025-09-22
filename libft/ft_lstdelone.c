/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:05:44 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:00:51 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
void del(void *content)
{
    free(content);
}
int main(void)
{
    char *content = strdup("Hello, list!");
    if (!content)
        return 1;
    t_list *node = ft_lstnew(content);
    if (!node)
    {
        free(content);
        return 1;
    }
    printf("Node content before deletion: %s\n", (char *)node->content);
    ft_lstdelone(node, del);
    printf("Node deleted.\n");
    return (0);
}
*/
