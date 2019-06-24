#include <stdio.h>
#include <stdlib.h>
int n;
int* array;
struct node{
int data;
struct node* left;
struct node* right;
};
struct node *tree;

struct node* newNode(int a)
{
 struct node* temp = (struct node *)malloc(sizeof(struct node *));
 temp -> data = a;
 temp -> left = NULL;
 temp -> right = NULL;
 return (temp);
}
void CreateTree(){
    struct node*
 for(i = 1; i< n;i++)
    {

    }






}
void InOrder(struct node* root){

if (root != NULL ){
InOrder(root->left);
printf("%d ", root->data);
InOrder(root->right);
}
return;
}


int main()
{
    printf("enter No of values : \n");
    scanf("%d",&n);
    printf("enter values : \n");
    array = (int *)malloc((n+1) * sizeof(int));
    for(int i = 1 ;i <= n ; i++){
        scanf("%d",&array[i]);
    }
    CreateTree();
    //InOrder(&tree[1]);

    return 0;
}
