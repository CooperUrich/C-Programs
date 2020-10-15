// Cooper Urich
// COP 3502C
// March 30th
// Professor Szumlanski

#include "KindredSpirits.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Struct for the linked list
typedef struct list
{
    node *head;
    int size;
} list;


// helper function to create a new node
node* create_new_node(int data)
{
    node* root = calloc(1, sizeof(node));
    
    // Puts the data in the node
    root->data = data;
    
    return root;
}

// creates the linked list
list *create_list()
{
    list *ptr = calloc(1, sizeof(list));
    
    if (ptr == NULL)
        return NULL;
    // returns the pointer to the list
    return ptr;
}

// head insert at the head
// (taken partly from webcourses)
void head_insert(list *list, int data)
{
        
    node *new_head = create_new_node(data);
    new_head->right = list->head;
    list->head = new_head;
    list->size++;
}

// preorder traversal
void preorder(node *root, list* list)
{
    if (root == NULL)
        return;
    // inserting the node into the linked list
    head_insert(list, root->data);
    preorder(root->left, list);
    preorder(root->right, list);
}

// Post order traversal
void postorder(node *root, list* list)
{
    if (root == NULL)
        return;

    postorder(root->left, list);
    postorder(root->right, list);
    // inserts the data into the list
    head_insert(list, root->data);
}

// frees the whole linked list
// (logic taken from webcourses)
list *destroy(list *list)
{
    node *temp = list->head;
    node *temp2;
    
    
    while (temp != NULL)
    {
        temp2 = temp->right;
        free(temp);
        temp = temp2;
    }
    
    free(list);
    
    return NULL;
}

int isReflection(node *a, node *b)
{
    // if both trees are empty, they are reflections
    if (a == NULL && b == NULL)
        return 1;
    // if only one is null, they are not
    if (a == NULL || b == NULL)
        return 0;
    
    // checks to see if the data is the same between the trees
    if (a->data == b->data)
    {
        if (isReflection(a->left, b->right))
        {
            if (isReflection(a->right, b->left))
                return 1;
        }
    }
    
    return 0;
    
}

node *makeReflection(node *root)
{
    node* reflect;
    reflect = malloc(sizeof(node));
    
    if (root == NULL)
        return NULL;
    // makes the nodes the same
    reflect->data = root->data;
    // reflect the data
    reflect->left = makeReflection(root->right);
    reflect->right = makeReflection(root->left);
    
    return reflect;
}

int kindredSpirits(node *a, node *b)
{
    int flag = 0;
    list *list1 = create_list();
    list *list2 = create_list();
    list *list3 = create_list();
    list *list4 = create_list();
    node *temp1;
    node *temp2;

    // if they are both null, they are kindred
    if (a == NULL && b == NULL)
        return 1;
    // if only one node is empty, cant be a kindred spirit
    if (a == NULL || b == NULL)
        return 0;
    
    // calls the traversal helper functions
    postorder(a, list1);
    preorder(b, list2);
    
    // keeps track of the head of the list
    temp1 = list1->head;
    temp2 = list2->head;
    
    // NULL check
    if (temp1 == NULL || temp2 == NULL)
        return 0;
    
    // if the sizes of the treea arent equal, they cant be kindred
    if (list1->size != list2->size)
        return 0;
   // traverses the list and checks the data
    while (list1 != NULL && list2 != NULL)
    {
        if (temp1 == NULL || temp2 == NULL)
            break;
        
        // flag if they arent equal data
        if (temp1->data != temp2->data)
            flag = 1;

        temp1 = temp1->right;
        temp2 = temp2->right;
    }
    // checks to see if the flag went off
    if (flag == 0)
        return 1;
    
    // free the lists
    destroy(list1);
    destroy(list2);
    
    // traverses the trees but the other way
    postorder(b, list3);
    preorder(a, list4);
    
    // keeps track of head
    temp1 = list4->head;
    temp2 = list3->head;
    
    // traverses trees again
    while (list4 != NULL && list3 != NULL)
    {
        if (temp1 == NULL || temp2 == NULL)
            break;
        
        // if this comparison is wrong, both are wrong
        if (temp1->data != temp2->data)
            return 0;
        
        temp1 = temp1->right;
        temp2 = temp2->right;
    }
    
    // frees the lists
    destroy(list4);
    destroy(list3);

    return 1;
}


double hoursSpent()
{
    return 10.0;
}
double difficultyRating()
{
    return 2.0;
}

//int main()
//{
//
//    kindredSpirits()
//}
