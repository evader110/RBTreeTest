#ifndef RBTASKTREE_H
#define RBTASKTREE_H

#include <iostream>
#include "vm_task.h"
using namespace std;

struct Node
{
    int key;
    VM_Task* m_task;
    Node* parent;
    Node* left;
    Node* right;
    bool color;//Red = 0 | Black = 1
};

class RB_Task_Tree
{
  private:
    //root refers to root of the tree
    Node* root;
    Node* q;
  public:
    RB_Task_Tree()
    {
      q = NULL;
      root = NULL;
    }
    
    void insert(VM_Task* task);
    void insertFix(Node* n);
    void leftRotate(Node* n);
    void rightRotate(Node* n);
    void remove(Node* n);
    void removeFix(Node* n);
    Node* successor(Node* n);
    void display(Node* n);//Displays whole tree in-order
    void clear();
    Node* getRoot(){return root;}
    int getKey(Node n){return n.key;}
    //void search();
};

void RB_Task_Tree::insert(VM_Task* task)
{
  //t is the node we are inserting 
  Node* t = new Node;
  Node* p = root;
  Node* q = NULL;
  t->key = task->getPriority();
  t->m_task = task;
  t->left = NULL;
  t->right = NULL;
  t->color = 0;
  if(root == NULL)
  {
    root = t;
    t->parent = NULL;
  }
  else
  {
    while(p != NULL)
    {
      q = p;
      if(p->key <= t->key)
        p = p->right;
      else
        p = p->left;
    }
    t->parent = q;
    if(q->key <= t->key)
      q->right = t;
    else
      q->left = t;
  }
  insertFix(t);
}

void RB_Task_Tree::insertFix(Node* n)
{
  Node* temp;
  if(root == n)
  {
    n->color = 1;
    return;
  }
  while(n->parent != NULL && n->parent->color == 0)
  {
    Node* grandparent = n->parent->parent;
    if(grandparent->left == n->parent)
    {
      if(grandparent->right != NULL)
      {
        temp=grandparent->right;
        if(temp->color == 0)
        {
          n->parent->color = 1;
          temp->color = 1;
          grandparent->color = 0;
          n = grandparent;
        }
      }
      else
      {
        if(n->parent->right == n)
        {
          n = n->parent;
          leftRotate(n);
        }
        n->parent->color = 1;
        grandparent->color = 0;
        rightRotate(grandparent);
      }
    }
    else
    {
      if(grandparent->left != NULL)
      {
        temp = grandparent->left;
        if(temp->color == 0)
        {
          n->parent->color = 1;
          temp->color = 1;
          grandparent->color = 0;
          n = grandparent;
        }
      }
      else
      {
        if(n->parent->left == n)
        {
          n = n->parent;
          rightRotate(n);
        }
        n->parent->color = 1;
        grandparent->color = 0;
        leftRotate(grandparent);
      }
    }
    root->color = 1;
  }
}

void RB_Task_Tree::leftRotate(Node* n)
{
  if(n->right == NULL)
    return;
  else
  {
    Node* y = n->right;
    if(y->left != NULL)
    {
      n->right = y->left;
      y->left->parent = n;
    }
    else
      n->right = NULL;

    if(n->parent != NULL)
      y->parent = n->parent;
    
    if(n->parent == NULL)
      root=y;
    else
    {
      if(n == n->parent->left)
        n->parent->left = y;
      else
        n->parent->right = y;
    }
    y->left = n;
    n->parent = y;
  }
}

void RB_Task_Tree::rightRotate(Node* n)
{
  if(n->left == NULL)
      return;
  else
  {
    Node* y = n->left;
    if(y->right != NULL)
    {
      n->left = y->right;
      y->right->parent = n;
    }
    else
      n->left = NULL;
    
    if(n->parent != NULL)
      y->parent = n->parent;
    
    if(n->parent == NULL)
      root=y;
    else
    {
      if(n == n->parent->left)
        n->parent->left = y;
      else
        n->parent->right = y;
    }
    y->right = n;
    n->parent = y;
  }
}

void RB_Task_Tree::remove(Node* n)
{
  if(root == NULL)
    return;
  int x = n->key;
  Node* p = root;
  Node* y = NULL;
  Node* q = NULL;
  bool found = 0;
  if(n->left == NULL && n->right == NULL)
  {
    if(n->parent->key <= n->key)
      n->parent->right = NULL;
    else
      n->parent->left = NULL;
    delete n;
  }
  else if(n->left == NULL || n->right == NULL)
  {
    if()
  }
}

void RB_Task_Tree::removeFix(Node* n)
{
  Node* s;
  while(n != root && n->color)
  {
    if(n->parent->left == n)
    {
      s = n->parent->right;
      if(!s->color)
      {
        s->color = 1;
        n->parent->color = 0;
        leftRotate(n->parent);
        s = n->parent->right;
      }
      if(s->right->color == 1 && s->left->color == 1)
      {
        s->color = 0;
        n = n->parent;
      }
      else
      {
        if(s->right->color)
        {
           s->left->color = 1;
           s->color = 0;
           rightRotate(s);
           s = n->parent->right;
        }
        s->color = n->parent->color;
        n->parent->color = 1;
        s->right->color = 1;
        leftRotate(n->parent);
        n = root;
      }
    }
    else
    {
      s = n->parent->left;
      if(!s->color)
      {
        s->color = 1;
        n->parent->color = 0;
        rightRotate(n->parent);
        s = n->parent->left;
      }
      if(s->left->color && s->right->color)
      {
        s->color = 0;
        n = n->parent;
      }
      else
      {
        if(s->left->color)
        {
          s->right->color = 1;
          s->color = 0;
          leftRotate(s);
          s = n->parent->left;
        }
        s->color = n->parent->color;
        n->parent->color = 1;
        s->left->color = 1;
        rightRotate(n->parent);
        n=root;
      }
    }
    n->color = 1;
    root->color = 1;
  }
}

void RB_Task_Tree::clear()
{
  while(root != NULL)
    remove(root);
}

Node* RB_Task_Tree::successor(Node* n)
{
  Node* y = NULL;
  if(n->left != NULL)
  {
    y = n->left;
    while(y->right != NULL)
      y = y->right;
  }
  else
  {
    y = n->right;
    while(y->left != NULL)
      y = y->left;
  }
  return y;
}

void RB_Task_Tree::display(Node* n)
{
  if(n != NULL)
  {
    display(n->left);
    cout << "Task: " << n->m_task->getTaskName() << " Priority: " << n->key << ": Color: " << (n->color ? "Black ":"Red ") << endl;;
    display(n->right);
  }
}

#endif //RBTASKTREE_H