/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 */

#include "node.h"

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
cs3505::node::node(const std::string & s, const string_set & set)
  : next(NULL),  // This syntax is used to call member variable constructors (or initialize them).
    data(s)      // This calls the copy constructor - we are making a copy of the string.
{
  this->set = set;
  // if there are no items in the list, set the head and the tail to the current node
  // and set the back and fore pointers of the current node to NULL
  if (set.head == NULL && set.tail == NULL)
  {
    set.head = this;
    set.tail = this;
    this->back = NULL;
    this->fore = NULL;
  }
  // if there are items in the list, set the current tail's next pointer to the current node (Add to the end of the list)
  // set the current node's back to the current tail
  // set the current's next to NULL 
  // set the tail to the current node, making it the new tail.
  else 
  {
    set.tail->next  = this;
    this->back = set.tail;
    this->fore = NULL;
    set.tail = this;
  }
}

  
/** Destructor:  release any memory allocated
  *   for this object.
  */
cs3505::node::~node()
{

  // deletion of the head

  if (this->back == NULL)
  {
     // if it is, set the back pointer of the fore node to null
    this->fore->back = NULL;

    // set the fore pointer of the current node to null
    this->fore = NULL;

    // set the head to the fore pointer of the current node
    this->set.head = this;
  }
 
  // deletion of the tail

  if (this->fore == NULL)
  {
    // set the fore pointer of the back node to null
    this->back->fore = NULL;

    // set the back pointer of the current node to null
    this->back = NULL;

    // set the tail to the back pointer of the current node
    this->set.tail = this;
  }

  // deletion of a random object
  
  // Loop through the liist until we find the element to remove
  while (this->fore != NULL)
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

  
}
