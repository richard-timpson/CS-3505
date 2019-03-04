/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen and Richard Timpson
 * February 9, 2019
 */
#include <cstdlib>
#include <iostream>
#include "node.h"
#include "string_set.h"

using namespace std;
// We're not in a namespace.  We are not in any class.  Symbols defined
//   here are globally available.  We need to qualify our function names
//   so that we are definining our cs3505::node class functions.
//
// Note that we could also use the namespace cs3505 { } block.  This would
//   eliminate one level of name qualification.  The 'using' statement will
//   not help in this situation.  
// 
// Keep it as shown here for node.cpp.  I show the other way in string_set.cpp.

/*******************************************************
 * node member function definitions
 ***************************************************** */

/** Constructor:  Creates a node containing
  *   an element.  It is initialized to
  *   not point to any other node.
  */
cs3505::node::node(const std::string & s,  string_set * set)
  : next(NULL),  // This syntax is used to call member variable constructors (or initialize them).
    data(s)
{
  this->set = set;
  // if there are no items in the list, set th head and the tail to the current node
  // and set the back and fore pointers of the current node to NULL
  if (this->set->head == NULL && this->set->tail == NULL)
  {
    this->set->head = this;
    this->set->tail = this;
    this->back = NULL;
    this->fore = NULL;
  }
  // if there are items in the list, set the current tail's next pointer to the current node (Add to the end of the list)
  // set the current node's back to the current tail
  // set the current's next to NULL 
  // set the tail to the current node, making it the new tail.
  else 
  {
    this->set->tail->fore  = this;
    this->back = this->set->tail;
    this->fore = NULL;
    this->set->tail = this;
  }
//   cs3505::node::creation_count++;
}

  
/** Destructor:  release any memory allocated
  *   for this object.
  */
cs3505::node::~node()
{
  
  if (this->back == NULL && this->fore == NULL)
  {
    this->set->head = NULL;
    this->set->tail = NULL;
  }

  //  deletion of the head

  else if (this->back == NULL)
  {
     // if it is, set the back pointer of the fore node to null
    this->set->head = this->fore;
    this->fore->back = NULL;

    // set the fore pointer of the current node to null

    this->fore = NULL;
    this->back = NULL;


  }
 
  // deletion of the tail

  else if (this->fore == NULL)
  {
    // set the tail to the previous node
    this->set->tail = this->back;
    
    // set the fore node of the previous node to Null
    this->back->fore = NULL;
    
    // 0 out the pointers of the current node. 
    this->fore = NULL;
    this->back = NULL;

  }

  // deletion of a random object
  
  else
  {
    // set the back pointer of the fore node to the back of the current
    this->fore->back = this->back;

    // set the fore pointer of the back node to the fore of the current
    this->back->fore = this->fore;

    // set the fore pointer to null
    this->fore = NULL;

    // set the back pointer to null
    this->back = NULL;

  }

  // I'm not convinced that the recursive delete is the
  //   best approach.  I'll keep it (and you'll keep it too).
  if (this->next != NULL)
    delete this->next;

  // Invalidate the entry so that it is not accidentally used.

  this->next = NULL;      


//   cs3505::node::deletion_count++;
}
