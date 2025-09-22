/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:06:51 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:04:21 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>
void print_node(t_list *node)
{
    if (node)
        printf("Node content: %s\n", (char *)node->content);
    else
        printf("Node is NULL\n");
}

int main(void)
{
    char *content = strdup("Hello, ft_lstnew!");
    t_list *node = ft_lstnew(content);
    print_node(node);
    if (node)
    {
        free(node->content);
        free(node);          
    }
    return (0);
}
*/
