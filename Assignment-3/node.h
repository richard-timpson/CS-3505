/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 */

#ifndef NODE_H
#define NODE_H

#include <string>

namespace cs3505
{
  // We're in a namespace - declarations will be within this namespace.
  //   (There are no definitions here.)

  /* Node class for holding elements. */
  
  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data (and constructor) within this class.
 
    private:
    node(const std::string & data, const string_set  & set);  // Constructor, takes in the data for the node, and also a reference to the string_set for getting the head and tail pointers of doubly linked list. 
      ~node();                         // Destructor
      
      
      std::string data;     // Variable to hold the element
      string_set set; // copy of reference to string set. 
      node *next;    // Variable to point to the next node in the list    
      node *back;    // Variable to point to previous node in doubly linked list
      node *fore;    // Variable to point to the next node in the doubly linked list
  };o
}

#endif
