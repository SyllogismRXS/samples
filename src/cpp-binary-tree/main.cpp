#include <iostream>
#include <stdio.h>
#include <queue>

using std::cout;
using std::endl;

class Node {
public:

     typedef enum State {
          undiscovered,
          discovered,
          processed
     } State_t;
     
     Node() : data_(0), left_(NULL), right_(NULL), state_(undiscovered) {}
     Node(int data) : data_(data), left_(NULL), right_(NULL), state_(undiscovered) {}

     void set_data(int data) { data_ = data; }
     void set_left(Node *left) { left_ = left; }
     void set_right(Node *right) { right_ = right; }
     void set_state(State_t state) { state_ = state; }
     
     int & data() { return data_; }
     Node* left() { return left_; }
     Node* right() { return right_; }
     State_t state() { return state_; }
     
protected:
     int data_;
     Node *left_;
     Node *right_;
     State_t state_;
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

     void reset_states(Node * n)
          {
               if (n == NULL) { 
                    return;
               }

               reset_states(n->left());
               n->set_state(Node::undiscovered);
               reset_states(n->right());
          }

     Node * breadth_first_search(int value)
          {
               reset_states(root_);

               if (root_ == NULL) {
                    return NULL;
               }

               root_->set_state(Node::discovered);

               std::queue<Node*> q;
               q.push(root_);

               while (q.size() > 0) {
                    Node * n = q.front();
                    q.pop();                                       
                    
                    n->set_state(Node::processed);

                    printf("Node: %d\n", n->data());
                    
                    if (n->data() == value) {
                         printf("\tFound Node: %d\n",  n->data());
                         return n;
                    }
                    
                    if (n->left() != NULL && n->left()->state() == Node::undiscovered) {
                         n->left()->set_state(Node::discovered);
                         q.push(n->left());
                    }

                    if (n->right() != NULL && n->right()->state() == Node::undiscovered) {
                         n->right()->set_state(Node::discovered);
                         q.push(n->right());
                    }                    
               }
               
               return NULL;
          }

     Node * depth_first_search(int value)
          {
               reset_states(root_);
               return dfs(root_, value);               
          }

protected:
     Node *root_;     

     Node * dfs(Node *n, int value)
          {
               if (n == NULL) {
                    return NULL;
               }
               
               n->set_state(Node::discovered);
               n->set_state(Node::processed);
               
               printf("Node: %d\n", n->data());

               if (n->data() == value) {
                    return n;
               }
               
               if (n->left() != NULL && n->left()->state() == Node::undiscovered) {
                    n->left()->set_state(Node::discovered);
                    Node * tmp = dfs(n->left(),value);
                    if (tmp != NULL) {
                         return tmp;
                    }
               }

               if (n->right() != NULL && n->right()->state() == Node::undiscovered) {                    
                    n->right()->set_state(Node::discovered);
                    Node * tmp = dfs(n->right(),value);
                    if (tmp != NULL) {
                         return tmp;
                    }
               }
               return NULL;
          }

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
     bt.add(7);
     bt.add(3);
     bt.add(15);

     bt.print(BinaryTree::preorder);
     bt.print(BinaryTree::inorder);
     bt.print(BinaryTree::postorder);
     
     printf("-------------------\n");
     printf("Breadth First Search\n");

     Node *n = bt.breadth_first_search(10);
     printf("Yeah, Found Node: %d\n", n->data());

     printf("-------------------\n");
     printf("Depth First Search\n");
     
     n = bt.depth_first_search(15);
     printf("Yeah, Found Node: %d\n", n->data());
     
     return 0;
}
