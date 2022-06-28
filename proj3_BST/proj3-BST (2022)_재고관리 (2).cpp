#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *fp1, *fp2;
typedef struct node *node_ptr;
typedef struct node {
	int conponent_number;
	int conponent_inven;
	int reorder;
	char explain[20];
	node_ptr leftchild;
	node_ptr rightchild;
}node;


char getcommand(FILE *fp,int *pnumber,char explain[],int *pinven,int *preorder)
{
    char buffer[100];
    fgets(buffer, 50, fp);
    sscanf(&buffer[2],"%d",pnumber);
 
    for (int i = 9; i < 29; i++) 
    {
        explain[i-9] = buffer[i];
    }
    explain[19]='\0';

    if(buffer[0]=='N')
    {
        sscanf(&buffer[30],"%d",pinven);
        sscanf(&buffer[40],"%d",preorder);       
    }
    else 
    {
         sscanf(&buffer[30],"%d",pinven);
    }
	return buffer[0];
}

void print_conponent(node_ptr root, FILE *fp2) {
	if (root != NULL)
	{

		print_conponent(root->leftchild, fp2);
		fprintf(fp2, "%d  %s  %d  %d ", root->conponent_number, root->explain, root->conponent_inven, root->reorder);
		if (root->conponent_inven < root->reorder)
			fprintf(fp2, "*재주문 필요*");
		fprintf(fp2, "\n");
		print_conponent(root->rightchild, fp2);

	}
}

node_ptr search(node_ptr root, int conponent_number, FILE *fp2)
{

	while (root != NULL) 
	{
		if (conponent_number == root->conponent_number)
			return root; 
		else if (conponent_number < root->conponent_number)
			root = root->leftchild; 
		else if ((conponent_number > root->conponent_number))
			root = root->rightchild; 
	}

	fprintf(fp2, "%d  컨포넌트 번호 에러\n", conponent_number);
	return NULL;
}

void addnode(node_ptr *root, node_ptr newitem, FILE *fp2) {
	node_ptr parent, temp;  
	int t; 
	parent = NULL;
	temp = *root;


	while (temp != NULL) {  

		if (newitem->conponent_number == temp->conponent_number) {
			t = temp->conponent_number;
			fprintf(fp2, "%d  컨포넌트 번호 중복\n", t);
			return;
		}
		parent = temp;
		if (newitem->conponent_number < temp->conponent_number)
			temp = temp->leftchild;
		else if (newitem->conponent_number > temp->conponent_number)
			temp = temp->rightchild;
	}


	if (parent == NULL)
		*root = newitem;
	else if (newitem->conponent_number < parent->conponent_number)
		parent->leftchild = newitem;
	else
		parent->rightchild = newitem;

}
void delete_node(node_ptr *root, int conponent_number, FILE *fp2)
{
	node_ptr parent, child, s, sp, t;


	parent = NULL; 
	t = *root;


	while (t != NULL && t->conponent_number != conponent_number)
	{
		parent = t;

		if (conponent_number < parent->conponent_number)
			t = parent->leftchild;
		else if (conponent_number > parent->conponent_number)
			t = parent->rightchild;
	}


	if (!t)
	{
		fprintf(fp2, "%d  그러한 컨포넌트 없음\n", conponent_number);
		return; 
	}

	if (t->leftchild == NULL && t->rightchild == NULL)
	{
		if (parent) 
		{
			if (parent->leftchild == t)
				parent->leftchild = NULL;
			else
				parent->rightchild = NULL;
		}
		else 
			*root = NULL;
	}
	
	else if ((t->leftchild == NULL) || (t->rightchild == NULL))
	{
		child = (t->leftchild != NULL) ? t->leftchild : t->rightchild;
		if (parent)
		{
			if (parent->leftchild == t)
				parent->leftchild = child;
			else
				parent->rightchild = child;
		}
		else 
			*root = child;
	}

	else
	{
	
		sp = t;
		s = t->rightchild;
		while (s->leftchild != NULL)
		{
			sp = s;
			s = s->leftchild;
		}
		
		if (sp->leftchild == s)
			sp->leftchild = s->rightchild;
		

		else
			sp->rightchild = s->rightchild;

		t->conponent_number = s->conponent_number;
		t = s;
	}
	free(t);
}
void check(node_ptr item, int conponent_inven, FILE *fp2) { 
	if (item) {
		if (item->conponent_inven + conponent_inven < 0) {
			fprintf(fp2, "%d 재고량이 충분하지 않음\n", item->conponent_inven);
			return;
		}
		item->conponent_inven = item->conponent_inven + conponent_inven;

	}
}

int main()
{
	node_ptr item = NULL;
	node_ptr newnode;
	int a, c, d; 
	char data; 
	char b[20] = { 0 };  
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");
	while (!feof(fp1))
	{
        data=getcommand(fp1,&a,b,&c,&d);
        
		switch (data)
		{
		case 'N':  
            newnode = (node_ptr)malloc(sizeof(node)); 
		    newnode->leftchild = NULL; 
		    newnode->rightchild = NULL;
            
			newnode->conponent_number = a;
			strcpy(newnode->explain, b);
			newnode->conponent_inven = c;
			newnode->reorder = d;
			addnode(&item, newnode, fp2);

			break;
		case 'D': 
			delete_node(&item, a, fp2);
			break;
		case 'A': 
			check(search(item, a, fp2), c, fp2);
			break;
		case 'R':
			check(search(item, a, fp2), c*-1, fp2);
			break;
		case 'P': 
			print_conponent(item, fp2);
            print_conponent(item, stdout);
			break;
		case 'X':  
			return 0;
			break;

		}
	}
	return 0;
}


