#include<stdio.h>
#include<stdlib.h>


struct bst
{
	int data;
	struct bst *left;
	struct bst *right;
};
typedef struct bst BinTree;


BinTree * insert(BinTree *,int);
void inorder(BinTree *);
void preorder(BinTree *);
void postorder(BinTree *);
 
int main ()
{
	BinTree *r = NULL;

	r = insert(r,30);
	r = insert(r,15);
	r = insert(r,10);
	r = insert(r,20);
	r = insert(r,40);
	r = insert(r,5);
	r = insert(r,45);
	r = insert(r,35);

	printf("\n display element in inorder:-");
	inorder(r);
	printf("\n display element in preorder:-");
	preorder(r);
	printf("\n display element in postorder:-");
	postorder(r);

	return 1;
}

BinTree * insert(BinTree *q, int val)
{
	BinTree *tmp;
	tmp = (BinTree *) malloc(sizeof(BinTree));

	if(q == NULL)
	{
		tmp->data = val;
		tmp->left = tmp->right = NULL;
		return tmp;
	}
	else
	{
		if(val<(tmp->data))
		{
			q->left = insert(q->left,val);
		}
		else
		{
			q->right = insert(q->right,val);
		}
	}

	return q;
}

void inorder(BinTree *q)
{
	if(q == NULL)
	{
		return;
	}

	inorder(q->left);
	printf(" %d ",q->data);
	inorder(q->right);	
}

void preorder(BinTree *q)
{
	if(q!=NULL)
	{
		printf(" %d ",q->data);
		preorder(q->left);
		preorder(q->right);
	}
}

void postorder(BinTree *q)
{
	if(q != NULL)
	{
		postorder(q->left);
		postorder(q->right);
		printf(" %d ",q->data);
	}
}
