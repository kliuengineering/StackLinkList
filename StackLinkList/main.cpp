//
//  main.cpp
//  StackLinkList
//
//  Created by Kevin Liu on 2024-02-02.
//
#include <iostream>
#include <vector>
#include <iterator>

template <class T>
class Stack
{
private:
    
    struct Node
    {
        Node *previous;
        Node *next;
        T data;
        
        // parameterized constructor for the Node
        explicit Node(Node *previous = nullptr, Node *next = nullptr, const T &data = T{})
        : previous(previous), next(next), data(data)
        {}
    };
    
    // front and back nodes
    Node *front;
    Node *back;
    
    // remembers the # of elements
    int counter = 0;
    
public:
    
    // default constructor for the stack
    Stack()
    {
        front = nullptr;
        back = nullptr;
    }

    // is the stack empty?
    bool is_empty()
    {
        return !front && !back;
    }
    
    bool is_full()
    {
        return counter == 5;
    }
    
    // stack implementation begins
    bool push(const T &data_input)
    {
        bool flag = false;
        
        // constructing a new node
        Node *node_new = new Node();
        node_new->previous = back;
        node_new->data = data_input;
        
        // if the stack already has at least 1 node, then
        if(back)
        {
            back->next = node_new;
        }
        
        // back points to the new node regardlessly
        back = node_new;
        
        // if the stack is empty, then
        if(!front)
        {
            front = node_new;
        }
        
        // if pushing is successful, then
        if(front && back)
        {
            flag = true;
            counter++;
        }
            
        return flag;
    }
    
    T pop()
    {
        T temp;
        
        // if the stack is empty, then
        if(!back)
        {
            //temp = 0;
        }
        // if the stack has only 1 element, then
        else if(back == front)
        {
            Node *node_del = back;
            temp = node_del->data;
            delete back;
            
            // set both front and back to null because there is no element left afterwards
            front = nullptr;
            back = nullptr;
            
            counter--;
        }
        // if the stack has more than 1 element, then
        else
        {
            Node *node_del = back;
            back = back->previous;
            back->next = nullptr;
            
            temp = node_del->data;
            delete node_del;
            
            counter--;
        }
        
        return temp;
    }
    
    // returns the top data from the stack
    T top()
    {
        if(!is_empty())
        {
            return back->data;
        }
        else
        {
            throw std::underflow_error("\nStack is already empty!\n");
        }
    }
    
    
    
    // free memory upon destruction
    ~Stack()
    {
        Node *temp;
        while(front)
        {
            temp = front->next;
            delete front;
            front = temp;
        }
    }
};


template <typename T>
void Print(Stack<T> &temp_stack, std::vector<T> &temp_vector)
{
    typename std::vector<T>::iterator itr;
    
    while (!temp_stack.is_empty())
    {
        temp_vector.push_back(temp_stack.pop()); // Add elements to the vector
    }
    
    for (itr = temp_vector.begin(); itr != temp_vector.end(); itr++)
    {
        std::cout << *itr << "\t";
    }
}

template <typename T>
void fill_up_the_stack(Stack<T> &temp_stack)
{
    std::string A = "Apples";
    std::string B = "Bananas";
    std::string C = "Grapes";
    std::string D = "Berries";
    std::string E = "Oranges";
    
    std::cout << "Order going in -> " << A << "\t" << B << "\t" << C << "\t" << D << "\t" << E << "\t" ;

    temp_stack.push(A);
    temp_stack.push(B);
    temp_stack.push(C);
    temp_stack.push(D);
    temp_stack.push(E);
}

int main(int argc, const char * argv[]) 
{
    std::cout << "Hello, World, this is a Stack!\n\n";
    
    Stack<std::string> my_stack;
    std::vector<std::string> my_vector;
    

    // testing push() and pop()
    std::cout << "Testing push() and pop()...\n";
    fill_up_the_stack(my_stack);
    std::cout << "\nOrder goin out -> "; Print(my_stack, my_vector);
    
    // testing is_empty()
    std::cout << "\n\nTesting is_empty()...\n";
    if(my_stack.is_empty())
        std::cout << "The stack is now empty!\n\n";
    else
        std::cout << "The stack is not empty!\n\n";
    
    // testing is_full()
    std::cout << "Testing is_full()...\n";
    fill_up_the_stack(my_stack);
    if(my_stack.is_full())
        std::cout << "\nThe stack is now full!\n\n";
    else
        std::cout << "\nThe stack is not full!\n\n";
    
    // testing top()
    std::cout << "Testing top()...\n";
    std::cout << "The top is " << my_stack.top();
    
    puts("");
    puts("");
    return 0;
}
