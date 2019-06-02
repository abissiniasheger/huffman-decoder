#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decoder.h"


/*global variables*/
treeNode* root=NULL; /*tree of symbols*/

/**
 * @brief Creates a new node
 *
 * @param[in]     N/A.
 * @return        Pointer to the new node
 *
 ******************************************************************************/
treeNode* talloc()
{
  treeNode* p=(treeNode*)malloc(sizeof(treeNode));
  if(p!=NULL)
  {
    p->left=p->right=NULL;
    p->symbol=0;
    p->isleaf=0;
  }
  return p;
}

/**
 * @brief builds the symbol tree given the list of symbols and code
 *
 *
 * @param[in]     A pointer to the code file.
 * @return        N/A
 *
 ******************************************************************************/
void build_tree(FILE* fp)
{
  codeStorage    characterCode;
  int		items_read;
  int		i,len;
  treeNode* curr=NULL;

  while(!feof(fp))
  {
    items_read=fscanf(fp,"%c %s\n", &(characterCode.symbol),characterCode.strcode);
    if(items_read!=2) break;
    curr=root;
    //treeNode* temp = root;
    len=strlen(characterCode.strcode);
    for(i=0;i<len;i++)
    {
      if (characterCode.strcode[i] == '1')
      {
        if (curr->right == NULL)
        {
          treeNode* newNode = talloc();
          curr->right = newNode;
          curr = newNode;
        }
        else
        {
          curr = curr->right;
        }

      }
      if (characterCode.strcode[i] == '0')
      {
        if (curr->left == NULL)
        {
          treeNode* newNode = talloc();
          curr->left = newNode;
          curr = newNode;
        }
        else
        {
          curr = curr->left;
        }
      }
    }
    /*assign code*/
    curr->isleaf=1;
    curr->symbol=characterCode.symbol;
    printf("inserted symbol:%c\n",characterCode.symbol);
   }
}

/**
 * @brief decodes a give sequence of bits
 *
 * @param[in]     Pointers to the file with the code and the output file.
 * @return        N/A
 *
 ******************************************************************************/
void decode(FILE* fin,FILE* fout)
{
  char c;
  treeNode* curr=root;
  while((c=getc(fin))!=EOF)
  {
    if (c == '1')
    {
      curr = curr->right;
    }
    else
    {
      curr = curr->left;
    }

    if (curr->isleaf)
    {
      putc(curr->symbol, fout);
      curr = root;
    }
  }
}

/**
 * @brief cleans up resources taken by the tree
 *
 * @param[in]     A pointer to the root of the tree.
 * @return        N/A
 *
 ******************************************************************************/

void freetree(treeNode* root)
{
  if(root==NULL)
   return;
  freetree(root->right);
  freetree(root->left);
  free(root);
}

int main()
{
  const char* IN_FILE="encoded.txt";
  const char* CODE_FILE="code.txt";
  const char* OUT_FILE="decoded.txt";
  FILE* fout;
  FILE* fin;
  /*allocate root*/
  root=talloc();
  fin=fopen(CODE_FILE,"r");
  /*build tree*/
  build_tree(fin);
  fclose(fin);

  /*decode*/
  fin=fopen(IN_FILE,"r");
  fout=fopen(OUT_FILE,"w");
  decode(fin,fout);
  fclose(fin);
  fclose(fout);
  /*cleanup*/
  freetree(root);
  getchar();
  return 0;
}
