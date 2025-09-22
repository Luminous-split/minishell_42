/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:07:00 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 22:07:33 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}
int main(void)
{
    t_list *node1 = ft_lstnew(strdup("Node 1"));
    t_list *node2 = ft_lstnew(strdup("Node 2"));
    t_list *node3 = ft_lstnew(strdup("Node 3"));
    node1->next = node2;
    node2->next = node3;
    printf("List content:\n");
    print_list(node1);
    int size = ft_lstsize(node1);
    printf("List size: %d\n", size);
    t_list *tmp;
    while (node1)
    {
        tmp = node1->next;
        free(node1->content);
        free(node1);
        node1 = tmp;
    }
    return (0);
}
*/
