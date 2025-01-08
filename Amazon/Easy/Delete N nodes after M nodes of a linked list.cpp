/*
Delete N nodes after M nodes of a linked list

Given a linked list, delete n nodes after skipping m nodes of a linked list until the last of the linked list.
Examples:

Input: Linked List: 9->1->3->5->9->4->10->1, n = 1, m = 2

Output: 9->1->5->9->10->1

Explanation: Deleting 1 node after skipping 2 nodes each time, we have list as 9-> 1-> 5-> 9-> 10-> 1.
*/

/*
delete n nodes after m nodes
  The input list will have at least one element
  Node is defined as

struct Node {
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

*/

// Approach - traverse through the entire list -> when count of nodes == m run the deletion for n nodes and reset count

class Solution
{
public:
    Node *linkdelete(Node *head, int n, int m)
    {
        if (!n)
            return head;
        Node *temp = head;
        int x = n, count = 1;
        while (temp)
        {
            if (count == m)
            {
                count = 0;
                x = n;
                while (temp->next && x--)
                {
                    temp->next = temp->next->next;
                }
            }
            count++;
            temp = temp->next;
        }
        return head;
    }
};