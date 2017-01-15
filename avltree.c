#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
* Michal Chorobik
* 0937145
* Assignment 4
* November 28,2016
*/


typedef struct node{
  char key[100];
  int count;
  int height;//( height of the left subtree minus the height of the right subtree. )
  //(if there is an internal node whose balance factor is less than -1 or greater than 1, the tree is said unbalanced.)
  struct node * left;
  struct node * right;
}node;

int size=0;

node* input(node* root, char inputStr[100]);
node* insert(node* n,char key[100]);
node* balance (node* n);
node* newNode(char key[100]);
int height(node* n);
void updateHeight(node* n);
node* R(node * n);
node* L(node * n);
node* searchTree(node* n,char key[100]);
void searchTreeFreq(node* n,int count);

int main(int argc, char const *argv[]) {

  int choice;
  char inputStr[100];
  char serachStr[100];
  char insertStr[100];
  int freq;

  node* root = NULL;

  printf("Michal Chorobik\n0937145\n");

  bool leaveLoop = false;
  while(leaveLoop!=true){

    printf("********************************************************************************************************\n");
    printf("(1) Initialization\n");
    printf("(2) Find\n");
    printf("(3) Insert\n");
    printf("(4) Remove\n");
    printf("(5) Check Height and Size\n");
    printf("(6) Find All (above a given frequency)\n");
    printf("(7) Exit\n");
    printf("********************************************************************************************************\n");
    printf("avl/> ");

    scanf("%d",&choice);

    switch(choice) {
          case 1 :
            printf("filename: ");
            scanf("%s",&inputStr);

            root=input(root,inputStr);
            printf("\n");
            break;
          case 2 :
            printf("find key: " );
            scanf("%s",&serachStr);
            node*s=searchTree(root,serachStr);
            if(s==NULL){
              printf("No_such_key\n");
            }else{
              printf("key: %s, frequency: %d\n",serachStr,s->count);
            }
            break;
          case 3 :
             printf("key: " );
             scanf("%s",&insertStr);
             root=insert(root,insertStr);
             s=searchTree(root,insertStr);
             printf("key: %s, frequency: %d\n",insertStr,s->count);
             break;
          case 4 :
             printf("remove key: " );
             scanf("%s",&insertStr);
             //remember to do size--;
             s=searchTree(root,insertStr);
             if(s==NULL){
               printf("No_such_key\n");
             }else{
               printf("key: %s, frequency: %d\n",serachStr,s->count-1);
             }
             break;
          case 5 :
             printf("height: %d,size: %d \n", root->height,size);
             break;
          case 6 :
             printf("frequency: " );
             scanf("%d",&freq);
             if(freq>-1){
               searchTreeFreq(root,freq);
             }
             break;
          case 7 :
            leaveLoop = true;
            break;
          default :
             printf("Invalid input\n" );
       }

  }//while loop ends

  free(root);
  return 0;
}
node* input(node* root, char inputStr[100]){

  FILE *fp;
  char str[99];

  if ((fp = fopen(inputStr,"r")) == NULL){
      printf("Error! opening file");                  // Program exits if the file pointer returns NULL.
      exit(1);
  }

  while((fscanf(fp,"%s",&str))!=EOF){
      //printf("%s ",str);
      root=insert(root,str);
  }

  return root;

}
node* insert(node* n,char key[100]){

  if(!n){
    return newNode(key);
  }

  if((strcmp(key,n->key))<0){
      n->left=insert(n->left,key);
  }else if((strcmp(key,n->key))>0){
      n->right=insert(n->right,key);
  }else{
    n->count++;
  }

  return balance(n);
}
node* balance (node* n){

  updateHeight(n);

  if ( height(n->left) - height(n->right)==2)
  {
      if ( height(n->left->right) > height(n->left->left))
          n->left = L(n->left);
      return R(n);
  }
  else if ( height(n->right) - height(n->left)==2)
  {
      if ( height(n->right->left) > height(n->right->right))
          n->right = R(n->right);
      return L(n);
  }

  return(n);

}
node* newNode(char key[100]){

  size++;
  node* n = malloc(sizeof(*n));
  strcpy(n->key,key);
  n->height=1;
  n->left=NULL;
  n->right=NULL;
  n->count=1;

  return(n);

}
int height(node* n){

  if(n == NULL){
      return 0;
  }else {
      return n->height;
  }

}
void updateHeight(node* n){

  if(n == NULL){
      n->height = 0;
  }else {
    if(height(n->left)>height(n->right)){
      n-> height = 1 + height(n->left);
    }else{
      n-> height = 1 + height(n->right);
    }
  }

}
node* R(node * n){
  node *new = n->left;
  n->left = new->right;
  new->right=n;
  //update height root and parent
  updateHeight(n);
  updateHeight(new);

  return new;
}
node* L (node * n){
  node *new = n->right;
  n->right = new->left;
  new->left=n;

  updateHeight(n);
  updateHeight(new);

  return new;
}
node* searchTree(node* n,char key[100]){

  if(n==NULL){
    return NULL;
  }

  if (strcmp(key,n->key)<0){
      return searchTree(n->left,key);
  }else if (strcmp(key,n->key)>0){
      return searchTree(n->right,key);
  }else{
    return n;
  }

}
void searchTreeFreq(node* n,int count){

  if(n==NULL){
    return;
  }

  if(n->count>=count){
    printf("key: %s, frequency: %d\n",n->key,n->count );
  }

  searchTreeFreq(n->left,count);
  searchTreeFreq(n->right,count);

}
