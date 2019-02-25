/*
 * CS3505 – Software Pratice
 * Richard Timpson
 * February 9, 2019
 * 
 * 
 * This is a very incomplete tester as I did not have time to finisht the project
 * after running into some bugs. You'll see many tests that I was failing commented out
 * and other test cases that I was going to test but did not get to. :(
 * 
 */

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>
#include "string_set.h"
#include "node.h"

using namespace std;

// static variables for testing destructore
int cs3505::node::creation_count = 0;
int cs3505::node::deletion_count = 0;

int main()
{

    bool ok = true;

    /* Size test */

    cout << endl << "Size Test" << endl;
    if (ok)
    {
        cout << "Size - Test1: Simple size test" << endl;
        cs3505::string_set our_set(10);
        our_set.add("Hello");
        our_set.add("World!");
        our_set.add("!");
        if (our_set.get_size()!= 3) 
        {
            ok = false;
        }
        if (ok) 
        {
            cout << "\tSuccess" << endl;
        }
        else 
        {
            cout << "\tFailure" << endl;
        }
    }


    /* Contains Test */
    cout << endl << "Contains Test" << endl;

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

    // Verify that the set size is the same as the vector size.
    if (ok)
    {
        cout << "Contains - Test3: Verify set size" << endl;
        set<string> stl_set;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");
        int count = 0;
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
            stl_set.insert(word);
        }
        vector<string> our_vector = our_set.get_elements();
        if (stl_set.size() != our_set.get_size())
        {
            ok = false;
        }
        if (ok)
        {
            cout << "\tSuccess!" << endl;
        }
        else
        {
            cout << "\tFailure!" << endl;
        }
    }

    // Add every word from Yankee.txt and make sure it's in the set.
    if (ok)
    {
        cout << "Contains - Test 4: Test all words from Yankee.txt" << endl;
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
         << "Removal Tests" << endl;
    /* Note. Was going to write test for simple removal but it's already in contains. */

    // Add every word from Yankee.txt and remove every word from Yankee.txt and make sure the set size is 0
    if (ok)
    {
        ok = false;
        cout << "Remove - Test1: Remove all words from yankee.txt" << endl;
        ifstream in("Yankee.txt");
        cs3505::string_set our_set(1000);
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
            if (our_set.contains(word))
            {
                ok = true;
            }
            else
            {
                ok = false;
                cout << "\t Failure: Didn't succesfully add every word" << endl;
                break;
            }
        }

        ok = true;
        ifstream in_repeat("Yankee.txt");
        int count = 1;
        while (true)
        {
            string word;
            in_repeat >> word;
            if (in_repeat.fail())
                break;
            if (our_set.contains(word))
            {
                our_set.remove(word);
            }
        }
        if (our_set.get_size() == 0)
            ok = true;
        else
        {
            ok = false;
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

    // Add every word from yankee keeping track of the creation count, and upon deletion verify that all objects created have been deleted.
    if (ok)
    {
        {
            cout << "Remove - Test 2: Test destructor for all words" << endl;
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

    /* Operator Equals */
    cout << endl
         << "Operator Equals tests" << endl;
    // Test the set size of both to verify that they are the same
    if (ok)
    {
        cout << "Equals - Test1: Same set size" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");

        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }
        cs3505::string_set new_set(1000);
        new_set = our_set;
        if (new_set.get_size() != our_set.get_size())
            ok = false;
        else
        {
            ok = true;
        }
        if (ok)
            cout << "\t Success " << endl;
        else
        {
            cout << "\t Failure" << endl;
        }
    }
    // Make sure that the address of both set's are not the same (The new set is completely new copy)
    if (ok)
    {
        cout << "Equals - Test2: Verify new address" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");

        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }
        cs3505::string_set new_set(1000);
        new_set = our_set;
        if (&new_set == &our_set)
        {
            ok = false;
        }
        if (ok)
        {
            cout << "\tSuccess!" << endl;
        }
        else
        {
            cout << "\tFailure!" << endl;
        }
    }

    // Make sure that every word added to the first set is also in the second set.
    if (ok)
    {
        cout << "Equals - Test3: Verify all elements are same" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");

        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }
        cs3505::string_set new_set(1000);
        new_set = our_set;

        ifstream in_new("Yankee.txt");
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            if (!new_set.contains(word))
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cout << "\tSuccess!" << endl;
        }
        else
        {
            cout << "\tFailure!" << endl;
        }
    }

    /* Get Elements */
    cout << endl
         << "Get elements Tests" << endl;

    // verify vector size for small set

    if (ok)
    {
        cout << "Elements - Test1: Verify vector size is same as set size for small set" << endl;
        cs3505::string_set our_set(5);
        our_set.add("Hi");
        our_set.add("my");
        our_set.add("name");
        our_set.add("is");
        our_set.add("richard");
        our_set.add("and");
        our_set.add("this");
        our_set.add("iss");
        our_set.add("a");
        our_set.add("set");

        vector<string> our_vector = our_set.get_elements();
        if (our_vector.size() != our_set.get_size())
        {
            ok = false;
        }
        if (ok)
        {
            cout << "\tSuccess" << endl;
        }
        else 
        {
            cout << "\tFailure" << endl;
        }
    }

    // Verify that the set size is the same as the vector size.
    if (ok)
    {
        cout << "Elements - Test2: Verify vector size is same as set size for large set" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }
        vector<string> our_vector = our_set.get_elements();
        if (our_vector.size() != our_set.get_size())
        {
            ok = false;
        }
        if (ok)
        {
            cout << "\tSuccess!" << endl;
        }
        else
        {
            cout << "\tFailure!" << endl;
        }
    }

    // make sure that the vector prints the words out as they were added

    if (ok)
    {
        cout << "Elements - Test3: Verify vector loops through words in the order they were added" << endl;
        cs3505::string_set our_set(5);
        our_set.add("Hi");
        our_set.add("my");
        our_set.add("name");
        our_set.add("is");
        our_set.add("richard");

        vector<string> our_vector = our_set.get_elements();
        vector<string>::iterator it = our_vector.begin();
        string word = *it;
        if (word !="Hi") ok = false;
        it++;
        word = *it;
        if (word !="my") ok = false;
        it++;
        word = *it;
        if (word !="name") ok = false;
        it++;
        word = *it;
        if (word !="is") ok = false;
        it++;
        word = *it;
        if (word !="richard") ok = false;
        it++;
        word = *it;
        if (ok)
        {
            cout << "\tSuccess" << endl;
        }
        else
        {
            cout << "\tFailure" << endl;
        }

    }

    // Add every work from Yankee.txt and make sure that as we iterate through the vector every word in the vector is also in the set.
    if (ok)
    {
        cout << "Elements - Test4: Verify vector has all words in from yankee.txt" << endl;
        cs3505::string_set our_set(1000);
        ifstream in("Yankee.txt");
        while (true)
        {
            string word;
            in >> word;
            if (in.fail())
                break;
            our_set.add(word);
        }
        vector<string> our_vector = our_set.get_elements();
        for (vector<string>::iterator it = our_vector.begin(); it!= our_vector.end(); it++) 
        {
            string word = *it;
            if (!our_set.contains(word)) 
            {
                ok = false;
                break;
            }
        }
        if (ok) 
        {
            cout << "\tSuccess" << endl;
        }
        else 
        {
            cout << "\tFailure!" << endl;
        }
    }


    // Make sure that the get_elements works after an object has been deleted.


    // make sure that the vector prints the words out as they were added

    if (ok)
    {
        cout << "Elements - Test5: Verify vector is correct after deletion and then insertion" << endl;
        cs3505::string_set our_set(5);
        our_set.add("Hi");
        our_set.add("my");
        our_set.add("name");
        our_set.add("is");
        our_set.add("richard");

        vector<string> our_vector = our_set.get_elements();
        vector<string>::iterator it = our_vector.begin();
        string word = *it;
        if (word !="Hi") ok = false;
        it++;
        word = *it;
        if (word !="my") ok = false;
        it++;
        word = *it;
        if (word !="name") ok = false;
        it++;
        word = *it;
        if (word !="is") ok = false;
        it++;
        word = *it;
        if (word !="richard") ok = false;
        it++;
        word = *it;


        our_set.remove("Hi");
        our_set.remove("name");
        our_set.add("end");
        our_vector = our_set.get_elements();
        it = our_vector.begin();

        word = *it;
        if (word !="my") ok = false;
        it++;
        word = *it;
        if (word !="is") ok = false;
        it++;
        word = *it;
        if (word !="richard") ok = false;
        it++;
        word = *it;
        if (word !="end") ok = false;
        if (ok) 
        {
            cout << "\tSuccess!" << endl;
        }
        else 
        {
            cout << "\tFailure!" << endl;
        }
    }

}