/*
 * This is a tester that I started to write in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our string_set class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen
 * January 29, 2019
 */

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>
#include "string_set.h"
#include "node.h"

// For convenience only:

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualified the class names
//        below with cs3505::
//        I did this for clarity.

int cs3505::node::creation_count = 0;
int cs3505::node::deletion_count = 0;

int main()
{
      // test contains for every element in the set. 
      // test adding a duplicate to make sure that it doesn't work 
      // test the operator overload to make sure it copies every element exactly. 
      // test delete to make sure that items are removed from both lists. 
      // test the doubly linked list to make sure that words are added in order. 
      // test deletion and addition of the same word. 
      // test delete to make sure the creation count and the deletion count are the same. 

      bool ok = true;
      /* Contains Test */
      cout << "Testing Contains Function" << endl;

      // Make sure simple addition with contains works
      if (ok)
      {
            cout << "Contains - Test1: Simple addition" << endl;
            ok = false;
            cs3505::string_set our_set(1000);
            our_set.add("hello");
            if (our_set.contains("hello"))
                  ok = true;
            if (ok)
            {
                  cout << "\t Success!";
            }
            else
            {
                  cout << "\t Failure!";
            }
            
      }
      // Add word, check, delete word check, and add word again.
      if (ok)
      {
            cout << "Contains - Test2: Adding deleted word" << endl;
            ok = false;
            cs3505::string_set our_set(1000);
            our_set.add("Hello");
            our_set.add("World");
            if (our_set.contains("Hello") && our_set.contains("World"))
                  ok = true;
            else
            {
                  ok = false;
            }
            our_set.remove("Hello");
            if (our_set.contains("Hello"))
            {
                  ok = false;
            }
            else
            {
                  ok = true;
            }
            if (ok)
            {
                  our_set.add("Hello");
                  if (our_set.contains("Hello") && our_set.contains("Wordl"))
                  {
                        ok = true;
                  }
                  else
                  {
                        ok = false;
                  }
            }
            if (ok)
            {
                  cout << "\t Success!";
            }
            else
            {
                  cout << "\t Failure!";
            }
            
            
      }
      // Add every word from Yankee.txt and make sure it's in the set. 
      // Test adding a duplicate word to make it's not in the set. 

      /* Remove Test */
      // Make sure simple deletion with contains works. 
      // Add every word from Yankee.txt and remove every word from Yankee.txt and make sure the set size is 0
      // Add every word from yankee keeping track of the creation count, and upon deletion verify that all objects created have been deleted. 

      /* Operator Equals */
      // Test the set size of both to verify that they are the same
      // Make sure that the address of both set's are not the same (The new set is completely new copy)
      // Add Yankee.txt to set, set it to the next set, and make sure that every word is contained in the new set. 

      /* Get Elements */
      // Verify that the set size is the same as the vector size. 
      // Run small test with 10 words to make sure that the words are iterated in the correct order. 
      // Make sure that the get_elements works after an object has been deleted. 
      // Add every work from Yankee.txt and make sure that as we iterate through the vector every word in the vector is also in the set. 



      // Jensens original tests. 
      ok = true;
      if (ok)
      {
            // Create the two sets.  Declaring the local variables constructs the objects.

            set<string> stl_set; // The built-in set class - no constructor parameters.

            cs3505::string_set our_set(1000); // Our set class, with a hashtable of 1000 slots.

            // Open the file stream for reading.  (We'll be able to use it just like
            //   the keyboard stream 'cin'.)

            ifstream in("Yankee.txt");

            // Loop for reading the file.  Note that it is controlled
            //   from within the loop (see the 'break').

            int count = 0;
            while (true)
            {
                  // Read a word (don't worry about punctuation)
                  string word;
                  in >> word;

                  // If the read failed, we're probably at end of file
                  //   (or else the disk went bad).  Exit the loop.

                  if (in.fail())
                        break;

                  // Word successfully read.  Add it to both sets.

                  stl_set.insert(word);
                  our_set.add(word);

                  count++;
            }

            // Close the file.

            in.close();

            // Print out all the words in the reference solution.

            for (set<string>::iterator it = stl_set.begin(); it != stl_set.end(); it++)
            {
                  string word = *it;
                  cout << word << endl;
            }

            // Print out the number of words found in each set.

            // cout << "STL set contains " << stl_set.size() << " unique words.\n";
            // cout << "Our set contains " << our_set.get_size() << " unique words.\n";

            // Done.  Notice that this code block ends below.  Any local
            // variables declared within this block will be automatically
            // destroyed.  Local objects will have their destructors
            // called.  (Blocks are great for controlling scope/lifetime.)

            cout << "creation count: " << cs3505::node::creation_count << endl;
      }
      cout << "deletion count " << cs3505::node::deletion_count << endl;

      // I really should test here to make sure that memory got cleaned up (that the
      // nodes and tables were deleted appropriately).  There is no such test here.
      // It's simple to construct a test that counts objects:
      //   Add a public static int variable to each class declaration
      //   Add corresponding static int definitions to the .cpp file, set the variable to 0
      //   An each constructor, increment once
      //   An each destructor, decrement once
      //   Check counts here to make sure every created object has been destroyed.

      {
            cout << "hitting second test" << endl;
            bool ok = true;

            if (ok)
            {
                  cout << "Test1: Add/ Contains" << endl;
                  cs3505::string_set set(50);
                  set.add("hello");
                  set.add("world");
                  set.add("!");

                  ok = false;
                  if (set.contains("hello") && set.get_size() == 1)
                        ok = true;
                  if (set.contains("world") && set.get_size() == 2)
                        ok = true;
                  if (set.contains("!") && set.get_size() == 3)
                        ok = true;
                  if (ok)
                        cout << "\t Success! Set contains 'hello world!'" << endl;
                  else
                        cout << "\t Failed" << endl;
            }

            if (ok)
            {
                  cout << "Test2: Contains Empty" << endl;
                  cs3505::string_set set(50);
                  if (set.contains("a"))
                        ok = false;
                  if (ok)
                        cout << "\t Success! Set doesn't contain any elements" << endl;
                  else
                        cout << "\t Failed" << endl;
            }
            if (ok)
            {
                  cout << "Test3: Remove" << endl;
                  cs3505::string_set set(50);
                  set.add("hello");
                  set.add("world");
                  set.remove("hello");
                  set.remove("world");
                  ok = false;
                  if (!set.contains("hello") && set.get_size() == 0)
                        ok = true;
                  if (!set.contains("world") && set.get_size() == 0)
                        ok = true;
                  if (ok)
                        cout << "\t Success! Set doesn't contain'hello world'" << endl;
                  else
                        cout << "\t Failed" << endl;
            }

            if (ok)
            {
                  cout << "Test4: Doubly linked list set size";
                  set<string> stl_set; // The built-in set class - no constructor parameters.

                  cs3505::string_set our_set(1000); // Our set class, with a hashtable of 1000 slots.

                  // Open the file stream for reading.  (We'll be able to use it just like
                  //   the keyboard stream 'cin'.)

                  ifstream in("Yankee.txt");

                  // Loop for reading the file.  Note that it is controlled
                  //   from within the loop (see the 'break').

                  int count = 0;
                  while (true)
                  {
                        // Read a word (don't worry about punctuation)
                        string word;
                        in >> word;

                        // If the read failed, we're probably at end of file
                        //   (or else the disk went bad).  Exit the loop.

                        if (in.fail())
                              break;

                        // Word successfully read.  Add it to both sets.
                        stl_set.insert(word);
                        our_set.add(word);      

                        count++;
                  }
                  vector<string> our_vector = our_set.get_elements();
                  for (vector<string>::iterator it = our_vector.begin(); it != our_vector.end(); it++)
                  {
                        string word = *it;
                        // cout << word << endl;
                  }
                  if (our_set.get_size() != stl_set.size())
                        ok = false;
                  if (ok)
                        cout << "\t Sucess: Set size's are the same" << endl;
                  else
                  {
                        cout << "\t Failed: Set size's aren't the same size" << endl;
                  }
                  
            }
            if (ok)
            {
                  cout << "Test5: Get elements matches stl set elements";
                  set<string> stl_set; // The built-in set class - no constructor parameters.

                  cs3505::string_set our_set(1000); // Our set class, with a hashtable of 1000 slots.

                  // Open the file stream for reading.  (We'll be able to use it just like
                  //   the keyboard stream 'cin'.)

                  ifstream in("Yankee.txt");

                  // Loop for reading the file.  Note that it is controlled
                  //   from within the loop (see the 'break').

                  int count = 0;
                  while (true)
                  {
                        // Read a word (don't worry about punctuation)
                        string word;
                        in >> word;

                        // If the read failed, we're probably at end of file
                        //   (or else the disk went bad).  Exit the loop.

                        if (in.fail())
                              break;

                        // Word successfully read.  Add it to both sets.
                        stl_set.insert(word);
                        our_set.add(word);      

                        count++;
                  }
                  vector<string> our_vector = our_set.get_elements();
                  set<string>::iterator sit = stl_set.begin();
                  vector<string>::iterator vit  = our_vector.begin();
                  while (sit != stl_set.end() && vit != our_vector.end())
                  {
                        string set_word = *sit;
                        string vector_word = *vit;
                        if (set_word != vector_word)
                        {
                              // cout << set_word << " does not match" << vector_word << endl;
                              ok = false;
                        }
                        sit++;
                        vit++;
                  }
                  if (ok)
                  {
                        cout << "Sucess: All words match" << endl;
                  }
                  else
                  {
                        cout << "Failed: All words do not match" << endl;
                  }
                  
            }
      }
      return 0;
}
