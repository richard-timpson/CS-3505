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
            cout << "\t Success!" << endl;
        }
        else
        {
            cout << "\t Failure!" << endl;
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
            if (our_set.contains("Hello") && our_set.contains("World"))
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
            cout << "\t Success!" << endl;
        }
        else
        {
            cout << "\t Failure!" << endl;
        }
    }

    // Add every word from Yankee.txt and make sure it's in the set.
    if (ok)
    {
        cout << "Contains - Test 3: Test all words from Yankee.txt" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");

        // add every word from yankee.txt to set
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }

        // check to make sure every word from yankee.txt is in file
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            if (!our_set.contains(word))
            {
                cout << "\t Failure: Set doesn't contain " << word << endl;
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cout << "\t Success!" << endl;
        }
    }

    /* Remove Test */
    cout << endl
         << "Removal Tests" << endl
         << endl;
    /* Note. Was going to write test for simple removal but it's already in contains. */
    // attempting to get words with the same hash value.
    if (ok)
    {
        cs3505::string_set our_set(1000);
        our_set.add("methods");
        our_set.add("grand");
        our_set.add("winks");
        our_set.remove("methods");
        our_set.remove("grand");
        our_set.remove("winks");
    }

    // Add every word from Yankee.txt and remove every word from Yankee.txt and make sure the set size is 0
    // if (ok)
    // {
    //     ok = false;
    //     cout << "Remove - Test1: Remove all words from yankee.txt" << endl;
    //     ifstream in("Yankee.txt");
    //     cs3505::string_set our_set(1000);
    //     while (true)
    //     {
    //         string word;
    //         in >> word;
    //         if (in.fail())
    //             break;
    //         our_set.add(word);
    //         if (our_set.contains(word))
    //         {
    //             ok = true;
    //         }
    //         else
    //         {
    //             ok = false;
    //             cout << "\t Failure: Didn't succesfully add every word" << endl;
    //             break;
    //         }
    //     }

    //     ok = true;
    //     ifstream in_repeat("Yankee.txt");
    //     int count = 1;
    //     while (true)
    //     {
    //         string word;
    //         in_repeat >> word;
    //         if (in_repeat.fail())
    //             break;
    //         our_set.remove(word);
    //         if (our_set.contains(word))
    //         {
    //             ok = false;
    //             cout << "\t Failure: Set contains word " << word << endl;
    //             break;
    //         }
    //         count++;
    //         cout << count << endl;
    //     }
    //     cout << our_set.get_size() << endl;
    //     if (our_set.get_size() == 0)
    //         ok = true;
    //     else
    //     {
    //         ok = false;
    //     }
    //     if (ok)
    //     {
    //         cout << "\t Success!" << endl;
    //     }
    //     else
    //     {
    //         cout << "\t Failure!" << endl;
    //     }
    // }

    // Add every word from yankee keeping track of the creation count, and upon deletion verify that all objects created have been deleted.
    if (ok)
    {
        {
            cout << "Contains - Test 3: Test all words from Yankee.txt" << endl;
            cs3505::string_set our_set(1000);
            ifstream in("Yankee.txt");

            // add every word from yankee.txt to set
            while (true)
            {
                string word;
                in >> word;
                if (in.fail())
                    break;
                our_set.add(word);
            }
        }
        if (cs3505::node::creation_count != cs3505::node::deletion_count)
            ok = false;
        if (ok)
            cout << "\tSuccess!" << endl;
        else
        {
            cout << "\t Failed!" << endl;
        }
    }

    // /* Operator Equals */
    // cout << endl
    //      << "Operator Equals tests" << endl
    //      << endl;
    // // Test the set size of both to verify that they are the same
    // if (ok)
    // {
    //     cout << "Equals - Test1: Same set size" << endl;
    //     cs3505::string_set our_set(1000);
    //     ifstream in("Yankee.txt");

    //     while (true)
    //     {
    //         string word;
    //         in >> word;
    //         if (in.fail())
    //             break;
    //         our_set.add(word);
    //     }
    //     cs3505::string_set new_set = our_set;
    //     if (new_set.get_size() != our_set.get_size())
    //         ok = false;
    //     else
    //     {
    //         ok = true;
    //     }
    //     if (ok)
    //         cout << "\t Success " << endl;
    //     else
    //     {
    //         cout << "\t Failure" << endl;
    //     }
    // }
    // Make sure that the address of both set's are not the same (The new set is completely new copy)
    // if (ok)
    // {
    //     cout << "Equals - Test2: Verify deep copy" << endl;
    //     cs3505::string_set our_set(1000);
    //     ifstream in("Yankee.txt");

    //     while (true)
    //     {
    //         string word;
    //         in >> word;
    //         if (in.fail())
    //             break;
    //         our_set.add(word);
    //     }
    //     cs3505::string_set new_set = our_set;
    //     cout << &new_set << endl;
    //     cout << &our_set << endl;
    // }


    // Add Yankee.txt to set, set it to the next set, and make sure that every word is contained in the new set.

    /* Get Elements */
    cout << endl << "Get elements Tests" << endl << endl;

    // Verify that the set size is the same as the vector size.
    if (ok)
    {
        cout << "Elements - Test1: Doubly linked list set size" << endl;
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

    // Add every work from Yankee.txt and make sure that as we iterate through the vector every word in the vector is also in the set.
    
    // Make sure that the get_elements works after an object has been deleted.
    // Run small test with 10 words to make sure that the words are iterated in the correct order.
}