// Filename: stackrecursion.cpp
//
// The file basically contains two functions that generate all subsequences of an input string. One function is the (standard) recursive method,
// while the other is non-recursive and uses a stack. Both these functions have an identical output, and create a (linked) list of strings as their output.
// 
// The code uses the List data structure used in a number of CSE101 assignments and tests.
// 
// USAGE:  (the executable is generated by a Makefile)
//     ./stackrecursion <INPUT FILE> <OUTPUT FILE>
// 
//     Only the first line of <INPUT FILE> is read, as a string. <OUTPUT FILE> contains all subsequences, each in a separate line.
// 
// 
// C. Seshadhri, Jan 2020, Oct 2020

#include <iostream>
#include "list.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
using namespace std;


// This class keeps pairs of string. This is useful for simulating the recursion through as stack.
class Pair
{
    public:
        string in_str;
        string fixed_str;
};

// This function generates all subsequences of the input input_str, and outputs them as a list. This function does not use recursion.
// Input: string input_str
// Output: list of all subsequences of input_str
// 
List allSubSeqStack(string input_str)
{
    List final_output; // generate empty list
    stack<class Pair> recurStack; // empty stack that performs the recursion
    Pair init, stacktop; // create a pair to push, to start the stac
    init.in_str = input_str; // put the initial string
    init.fixed_str = ""; // this is the fixed string, initially empty
    recurStack.push(init); // push this pair onto the top

    while(!recurStack.empty()) // while the stack is non-empty
    {
        stacktop = recurStack.top();// get the top pair in stack 
        recurStack.pop(); // remove the top element of stack
        if (stacktop.in_str.length() == 0) // input string is empty, so this is base case
        {
            final_output.insert(stacktop.fixed_str); // insert the fixed string onto list
            continue; // pop the next element of stack
        }
        char last = stacktop.in_str.back(); // get last element of in_str
        stacktop.in_str.pop_back(); // remove last element of stack
        Pair to_push; // setting up elements to push onto stack
        to_push.in_str = stacktop.in_str;
        to_push.fixed_str = stacktop.fixed_str; 
        recurStack.push(to_push); // this is for one recursive call
        to_push.fixed_str = last + stacktop.fixed_str; // this is for next recursive call
        recurStack.push(to_push);
    }
    return final_output;
}

// This recursive function generates all subsequences of the input in_str *appended* to the fixed_str, and outputs them in the list provided as an argument
// Input: string fixed_str, string in_str, pointer to list list_ptr
// Output: void, but list referenced by list_ptr is modified
// 
void allSubSeqRec(string in_str, string fixed_str, List *list_ptr)
{
    if (in_str.length() == 0) // base case
    {
        list_ptr->insert(fixed_str); // insert the fixed string into list
        return;
    }
    char top = in_str.back(); // get the last element of the string
    in_str.pop_back(); // delete last element of in_str
    allSubSeqRec(in_str, fixed_str, list_ptr); // recursive call for subsequences without top
    allSubSeqRec(in_str, top+fixed_str, list_ptr); //  recursive call for subsequences with top
    return;
}

// This function generates all subsequences of the input in_str, and outputs them as a list. This is the recursive version
// Input: string in_str
// Output: list of all subsequences of in_str
// 
List allSubSeq(string in_str)
{
    List *final_output = new List(); // generate empty list
    allSubSeqRec(in_str,"",final_output); // populate list with output
    return *final_output;
}

List allAnagrams(string input_str)
{
    List final_output; // Empty list final output
    stack<class Pair> recurStack; // Implemented stack
    Pair init, stacktop; // Initialize pairs
    init.in_str = input_str;
    init.fixed_str = "";
    recurStack.push(init); // Push initial pair into stack

    while(!recurStack.empty()) // While stack isn't empty
    {
        stacktop = recurStack.top(); // Get top pair
        recurStack.pop(); // Remove top pair
        
        if (stacktop.in_str.length() == 0) // Base Case - we have processd through the whole input str 
        {
            final_output.insert(stacktop.fixed_str);
            continue;
        }
        // Generate new permutation by removing each character from in_str and appending to fixed_str
        for (unsigned int i = 0; i < stacktop.in_str.length(); ++i)
        {
            Pair to_push; // Setting up element to push into stack

            // Construct the new in_str by removing the character at index i from the current in_str
            to_push.in_str = stacktop.in_str.substr(0, i) + stacktop.in_str.substr(i + 1);
            // Construct the new fixed_str by appending the character at index i from the current in_str to the current fixed_str
            to_push.fixed_str = stacktop.fixed_str + stacktop.in_str[i];

            recurStack.push(to_push); // Push new pair into stack for further permutation
        }
    }
    return final_output; // Return list of all permutations
};


List language(string input_str, int k) {
    List final_output; // Empty list final output
    stack<string> recurStack; // Implemented stack
    string stacktop;
    recurStack.push(""); // Push initial pair into stack

    // Include empty string
    final_output.insert("");

    while(!recurStack.empty()) {
        stacktop = recurStack.top(); // Get top pair
        recurStack.pop(); // Remove top pair

        if (stacktop.length() < unsigned(k)) {
            for (char ch : input_str) {
                string to_push = stacktop + ch;
                final_output.insert(to_push);
                recurStack.push(to_push);
            }
        }
    }
    return final_output; // Return list of characters based on length
};


List stretch(string input, int k) {
    List final_output;
    stack<pair<string, int>> recurStack;
    recurStack.push({"", 0});

    while(!recurStack.empty())
    {
        string stacktop = recurStack.top().first;
        int stacktop_index = recurStack.top().second;

        recurStack.pop();

        for(int j = 0; j < k; ++j)
        {
            stacktop += input[stacktop_index];

            if(stacktop_index < int(input.length() - 1))
            {
                recurStack.push({stacktop, stacktop_index + 1});
            }
            else
            {
                final_output.insert(stacktop);
            }
        }
    }
    return final_output;
}


List bubbling(string input_str) {
    List final_output;
    stack<pair<string, int>> recurStack;
    recurStack.push({input_str, 0});
   
    while(!recurStack.empty())
    {
        string stacktop = recurStack.top().first;
        int stacktop_index = recurStack.top().second;
        recurStack.pop();

        if(stacktop_index < int(input_str.length() - 1))
        {
            string c1 = stacktop;
            string c2 = stacktop;
            recurStack.push({c1, stacktop_index + 1});
            swap(c2[stacktop_index], c2[stacktop_index + 1]);
            recurStack.push({c2, stacktop_index + 1});
        }
        else
        {
            final_output.insert(stacktop);
        }
    }
    return final_output;
}

int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in_str; // to store the input string from the file


    getline(input, in_str); // get the single string from the input file
    
    //cout << in_str << endl;

    List myList = bubbling(in_str); // initializing the linked list

    myList.sort(); // sort the list
    
    output << myList.print("\n") << endl;  // print the list, using a new line as delimiter between items of the list
    cout << myList.print("\n") << endl;
    
    myList.deleteList(); // free all the memory of this list

    input.close();
    output.close();
}
