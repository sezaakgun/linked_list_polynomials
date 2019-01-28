#include <stdio.h>
#include <stdlib.h> 


typedef struct node *node_ptr;

struct node
{
    int coef;
    int power;
    node_ptr next; 
};

void print_list(node_ptr head);
node_ptr create_polynomial(int n);
node_ptr add_polynomials(node_ptr head1, node_ptr head2);
node_ptr multiply_polynomials(node_ptr head1, node_ptr head2);

int main()
{
    int n = 0;
    printf("First polynomials elements number = ");
    scanf("%d",&n);
    node_ptr head1 = create_polynomial(n);

    printf("Second polynomials elements number = ");
    scanf("%d",&n);
    node_ptr head2 = create_polynomial(n);

    printf("\n\n");

    printf("First polynomial:\n");
    print_list(head1);

    printf("\n\n");

    printf("Second polynomial:\n");
    print_list(head2);

    printf("\n\n");

    node_ptr added = add_polynomials(head1,head2);
    printf("\nAddition:\n");
    print_list(added);

    printf("\n\n");

    node_ptr multiplied = multiply_polynomials(head1,head2);
    printf("\nMultiplication:\n");
    print_list(multiplied);

    return 0;
}

int is_last(node_ptr node)
{
    return(node->next == NULL);
}

void print_list(node_ptr head) {

    if(head == NULL)
    {
        printf("0\n");
        return;
    }

    node_ptr current = head;

    while (current->next != NULL) 
    {
        printf("%d*x^%d + ", current->coef,current->power);
        current = current->next;
    }
    // We didn't want to print + on the last elemenet.
    printf("%d*x^%d\n", current->coef,current->power);
}

void swap(node_ptr node1, node_ptr node2)
{
    int coef = node1->coef;
    int power = node1->power;
    node1->coef = node2->coef;
    node1->power = node2->power;
    node2->coef = coef;
    node2->power = power;
}

node_ptr find_prew(node_ptr head,node_ptr node)
{
    node_ptr current = head;
    while (current->next != NULL && current->next != node)
    {
        current = current->next;
    }
    return current;
}

void delete_node(node_ptr head,node_ptr node)
{
    node_ptr node_prew = find_prew(head, node);
    node_prew->next = node->next;
    free(node);
}


node_ptr create_node(int coef,int power)
{
    node_ptr node;
    node = (node_ptr)malloc(sizeof(struct node));
    node->coef = coef;
    node->power = power;
    node->next = NULL;
    return node;
}

void add_before(node_ptr* head, node_ptr node1, node_ptr node2)
{
    node_ptr new_node = create_node(node2->coef, node2->power);

    if (*head == node1)
    {
        new_node->next = *head;
        *head = new_node;
    } 
    else
    {
        node_ptr node1_prew = find_prew(*head, node1);
        new_node->next = node1;
        node1_prew->next = new_node;
    }
}


void add_after(node_ptr node1, node_ptr node2)
{
    node_ptr new_node = create_node(node2->coef, node2->power);
    new_node->next = node1->next;
    node1->next = new_node;
}


void add_in_decreasing_order(node_ptr* head, node_ptr node)
{
    node_ptr current = *head;
    node_ptr before = NULL;

    while (current != NULL) 
    {
        if (node->power > current->power)
        {
            add_before(head, current, node);
            return;
        }
        else if (node->power == current->power)
        {
            current->coef += node->coef;
            return;
        }
        else
        {
            before = current;
            current = current->next;
        }
        
    }
    add_after(before, node);
}

node_ptr copy_individial(node_ptr node)
{
    return create_node(node->coef,node->power);
}

node_ptr copy_all(node_ptr node)
{   
    if (node == NULL)
    {
        return node;
    }
    if (is_last(node))
    {
        return copy_individial(node);
    }
    node_ptr result = copy_individial(node);
    node_ptr current = node->next;
    while (current != NULL)
    {
        add_in_decreasing_order(&result, current);
        current = current->next;
    }
    
    return result;
}

node_ptr create_polynomial(int n) 
{
    int i = 0;
    node_ptr head = NULL;
    node_ptr temp = NULL;
    node_ptr p = NULL;
    int coef = 0;
    int power = 0;
    for(i = 0; i < n; i++)
    {
        printf("\n%d.element's coefficent and power respectively = ",i+1);
        scanf("%d",&coef);
        scanf("%d",&power);
        printf("\n");
        temp = create_node(coef,power);
        

        if (head == NULL) 
        {
            head = temp;
        }
        else
        {
            add_in_decreasing_order(&head,temp);
        }

    }
    return head;
}


node_ptr order_polynomial(node_ptr head)
{
    node_ptr current = head;
    node_ptr next = NULL;
    int done = 1;

    do 
    {
        if (is_last(current))
        {

            // If polynomial is ordered or head is just one node, return head.
            if (done || is_last(head))
            {
                return head;
            }
            done = 1;
            current = head;
        }
        next = current->next;
        // Bubble sort.
        if (current->power < next->power)
        {
            done = 0;
            swap(current,next);
        }
        // Combine if powers are the same.
        else if (current->power == next->power)
        {
            done = 0;
            current->coef += next->coef;
            current->next = next->next;
            free(next);
        }

        // When we combine the last two elements we need to reset the current to head else current->next cause us t.
        if (current->next == NULL)
        {
            current = head;
        }
        else 
        {
            current = current->next;
        }

    } while (1);
    return head;
}


node_ptr add_polynomials(node_ptr head1, node_ptr head2)
{

    if (head1 != NULL)
    {
        node_ptr result = copy_all(head1);
        node_ptr temp = head2;
        while (temp != NULL)
        {
            add_in_decreasing_order(&result,temp);
            temp = temp->next;
        }
        return result;
    }
    else
    {
        node_ptr result = copy_all(head2);
        node_ptr temp = head1;
        while (temp != NULL)
        {
            add_in_decreasing_order(&result,temp);
            temp = temp->next;
        }
        return result;
    }



    
    
}


node_ptr multiply_polynomials(node_ptr head1, node_ptr head2)
{
    node_ptr temp1 = head1;
    node_ptr temp2 = head2;
    node_ptr temp_mult = NULL;
    node_ptr result = NULL;

    while (temp1 != NULL)
    {
        node_ptr temp2 = head2;
        while (temp2 != NULL)
        {
            temp_mult = create_node(temp1->coef*temp2->coef,temp1->power+temp2->power);
            if (result == NULL)
            {
                result = temp_mult;
            }
            else
            {
                add_in_decreasing_order(&result,temp_mult);
            }
            temp2 = temp2->next;
        } 
        temp1 = temp1->next;
    }
    return result;
}