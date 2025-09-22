/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soemin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:05:33 by soemin            #+#    #+#             */
/*   Updated: 2025/05/08 21:59:59 by soemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
void del(void *content)
{
    free(content);
}
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
    t_list *head = NULL;
    
    char *str1 = strdup("Node 1");
    char *str2 = strdup("Node 2");
    char *str3 = strdup("Node 3");
    t_list *node1 = ft_lstnew(str1);
    t_list *node2 = ft_lstnew(str2);
    t_list *node3 = ft_lstnew(str3);
    node1->next = node2;
    node2->next = node3;
    head = node1;
    printf("List before clear:\n");
    print_list(head);
    ft_lstclear(&head, del);
    printf("List after clear:\n");
    print_list(head); // Should print "NULL"
    return (0);
}
*/
