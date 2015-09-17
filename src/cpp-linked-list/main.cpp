#include <iostream>
#include <stdio.h>

class Node {
public:
     Node() : data(0), next(NULL) {}
     Node(int d) : data(d), next(NULL) {}
     int data;
     Node *next;
protected:
private:
};

class List {
public:
     List() : head_(NULL) { head_ = NULL;}

     int push_front(int d)
          {               
               Node *node = new Node(d);
               
               node->next = head_;
               head_ = node;

               return 0;
          }

     int push_back(int d)
          {
               Node *node = new Node(d);    

               if (head_ == NULL) {
                    head_ = node;
                    return 0;
               }

               Node *n = head_;
               while (n->next != NULL) {
                    n = n->next;
               }
               n->next = node;

               return 0;
          }

     int pop_back()
          {
               if (head_ == NULL) {
                    return -1;
               }

               if (head_->next == NULL) {
                    delete head_;
                    head_ = NULL;
                    return 0;
               }

               Node *n = head_;
               while (n->next->next != NULL) {
                    n = n->next;
               }
               delete n->next;
               n->next = NULL;

               return 0;
          }    

     int pop_front()
          {
               if (head_ == NULL) {
                    return -1;
               }

               if (head_->next == NULL) {
                    delete head_;
                    head_ = NULL;
                    return 0;
               }

               Node * temp = head_;
               head_ = head_->next;
               delete temp;
               return 0;
          }

     void print()
          {
               Node * n;
               n = head_;
               while (n != NULL) {
                    printf("%d ", n->data);
                    n = n->next;
               }
               printf("\n");
          }

protected:
private:
     Node * head_;
};

int main(int argc, char *argv[])
{
     List list;
     list.push_front(1);
     list.print();
     list.push_front(2);
     list.print();
     
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     list.push_back(4);
     list.print();
     
     list.pop_front();
     list.pop_front();     
     list.print();
     
     list.push_back(1);
     list.push_back(2);
     list.push_back(3);
     list.push_back(4);
     list.print();
     
     list.pop_back();
     list.print();
     
     list.push_front(7);
     list.push_front(8);
     list.push_front(9);
     list.print();
     
     return 0;
}
