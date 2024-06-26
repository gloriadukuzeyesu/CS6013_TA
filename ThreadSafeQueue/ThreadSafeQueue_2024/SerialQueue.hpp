#pragma once

////////////////////////////////////////////////////////////////////////
//
// Author: Gloria Dukuzeyesu
// Date: March 18
// CS 6013
//
// Outline for SerialQueue class.  Fill in the missing data, comments, etc.
//
////////////////////////////////////////////////////////////////////////
#include "iostream"
using namespace std;

template <typename T>

class SerialQueue {

public:
   SerialQueue() :
      head_( new Node{ T{}, nullptr } ), size_( 0 )
   {
      tail_ = head_;
   }

   /**
    * @brief adds a new node at the tail of the linked list.
    * 
    * @param x data to be added to the new node
    */
   void enqueue( const T & x ) {
      // create a new Node
      Node *newNode = new Node {x, nullptr}; // c++11 syntax

      if(head_->next == nullptr) {
         head_->next = newNode; 
         tail_ = newNode; 
         // head_->next = tail_;
      } else {
         tail_->next = newNode; 
         tail_ = newNode; 
      }
      size_++;
   }
   /**
    * @brief 
    * removes a node from the head of the linked list, 
    * and returns the data at the new head in the variable ret. 
    * If the queue is empty, dequeue returns false.
    * If an element was dequeued successfully, dequeue returns true.
    * @param ret 
    * @return true 
    * @return false 
    */

   bool dequeue( T *ret ) {
      // Your code goes here.

      // checking if the queue is empty,
      if(head_->next == nullptr) {
         return false; 
      }

      Node *newHead = head_->next;  
      *ret = newHead->data;  // is this weird or it's me who is weird?? 
      // head_  = newHead ; 
      head_->next = newHead->next;  //should we update the next ptr of head. Assuming head_ is a dummy pointer and will always stays there??

      // delete newHead; 
      size_--;
      return true;  
   }

   ~SerialQueue() {
      while( head_ != nullptr ) {
         Node* temp = head_->next;
         delete head_;
         head_ = temp;
      }
   }

   int size() const { return size_; }

   T getHeadData() const {
      return head_->next->data;
   }

   T getTailData() const {
      return tail_->data;
   }

private:

   struct Node {
      T      data;
      Node * next;
   };

   Node * head_;
   Node * tail_;
   int    size_;
};
