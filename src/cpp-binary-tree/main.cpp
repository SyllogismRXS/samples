#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

class Node {
public:
     Node() : data_(0), left_(NULL), right_(NULL) {}
     Node(int data) : data_(data), left_(NULL), right_(NULL) {}

     void set_data(int data) { data_ = data; }
     void set_left(Node *left) { left_ = left; }
     void set_right(Node *right) { right_ = right; }
    
     int & data() { return data_; }
     Node* left() { return left_; }
     Node* right() { return right_; }
    
protected:
     int data_;
     Node *left_;
     Node *right_;
private:
};

class BinaryTree {
public:
     BinaryTree() : root_(NULL)
          {
          }

     typedef enum Order {
          preorder = 0,
          inorder,
          postorder
     } Order_t;

     void print(Order_t order)
          {
               switch (order) {
               case preorder:
                    preorder_print(root_);
                    break;
               case inorder:
                    inorder_print(root_);
                    break;
               case postorder:
                    postorder_print(root_);
                    break;
               default:
                    break;
               };
               printf("\n");
          }

     void add(int data)
          {
               if (root_ == NULL) {
                    root_ = new Node(data);
                    return; 
               }
               add_sorted(root_, data);
          }

     void add_sorted(Node *n, int data)
          {
               if (data <= n->data()) {
                    if (n->left() == NULL) {
                         Node *temp = new Node(data);
                         n->set_left(temp);
                         return;
                    }    
                    add_sorted(n->left(),data);
               } else {
                    if (n->right() == NULL) {
                         Node *temp = new Node(data);
                         n->set_right(temp);
                         return;
                    }
                    add_sorted(n->right(),data);
               }
          }

protected:
     Node *root_;

     void preorder_print(Node *n)
          {
               if (n == NULL) {
                    return;    
               }

               printf("%d ", n->data());
               preorder_print(n->left());
               preorder_print(n->right());
          }

     void inorder_print(Node *n)
          {
               if (n == NULL) {
                    return;    
               }

               inorder_print(n->left());
               printf("%d ", n->data());
               inorder_print(n->right());
          }

     void postorder_print(Node *n)
          {
               if (n == NULL) {
                    return;    
               }

               postorder_print(n->right());
               postorder_print(n->left());
               printf("%d ", n->data());
          }

private:
};

int main(int argc, char *argv[])
{
     BinaryTree bt;
     bt.add(5);
     bt.add(8);
     bt.add(2);
     bt.add(1);
     bt.add(9);
     bt.add(10);
     bt.add(20);

     bt.print(BinaryTree::preorder);
     bt.print(BinaryTree::inorder);
     bt.print(BinaryTree::postorder);

     return 0;
}
