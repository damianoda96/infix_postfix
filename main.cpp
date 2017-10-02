#include <iostream>

using namespace std;

struct List
{
    char list_array[100];
    int s = 0;

    void clearList()
    {
        for(int i = 0; i < 100; i++)
        {
            if(list_array[i] != NULL)
            {
                list_array[i] = NULL;
            }
        }
    }

     void push_to_list_array(char ch)
     {
        for(int i = 0; i < 100; i++)
        {
            if(list_array[i] == NULL)
            {
                list_array[i] = ch;
                s++;
                break;
            }
        }
    }

    int sizeOfListArray()
    {
        return s;
    }
};

struct Stack
{
    List stack_list;
    int topOfStack;

    Stack()
    {
        topOfStack = -1;
    }

    void push(char c)
    {
        stack_list.list_array[++topOfStack] = c;
    }

    void pop()
    {
        topOfStack--;
    }

    int sizeOf()
    {
        return topOfStack;
    }

    char top()
    {
        return stack_list.list_array[topOfStack];
    }

    bool isEmpty()
    {
        if(topOfStack >= 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

int calc_weight(char);
int evaulate(int, int, char);

List convert(List infix_list, int sizeOfList)
{
    cout << "converting..";
    cout << endl;

    Stack postfix_stack;
    List postfix_list;
    int index = 0;

    postfix_list.clearList();

    cout << "sizeoflist = " << sizeOfList;
    cout << endl;

    while (index < sizeOfList)
    {
        if(isalpha(infix_list.list_array[index]))
        {
            cout << infix_list.list_array[index];
            postfix_list.push_to_list_array(infix_list.list_array[index]);
        }
        else if(infix_list.list_array[index] == '+' || infix_list.list_array[index] == '-' || infix_list.list_array[index] == '*' || infix_list.list_array[index] == '/')
        {
            if(postfix_stack.isEmpty())
            {
                postfix_stack.push(infix_list.list_array[index]);
            }
            else
            {
                if(calc_weight(postfix_stack.top()) >= calc_weight(infix_list.list_array[index]))
                {
                    cout << postfix_stack.top();
                    postfix_list.push_to_list_array(postfix_stack.top());
                    postfix_stack.pop();

                }

                postfix_stack.push(infix_list.list_array[index]);
            }

        }

        if(infix_list.list_array[index] == '(')
        {
            postfix_stack.push(infix_list.list_array[index]);

        }
        if(infix_list.list_array[index] == ')')
        {
            while(postfix_stack.top() != '(')
            {
                cout << postfix_stack.top();
                postfix_list.push_to_list_array(postfix_stack.top());
                postfix_stack.pop();
            }
            postfix_stack.pop();
        }

        index++;
    }

    while(postfix_stack.sizeOf() != -1)
    {
        cout << postfix_stack.top();
        postfix_list.push_to_list_array(postfix_stack.top());
        postfix_stack.pop();
    }

    cout << endl << endl;

    return postfix_list;
}

int convertEval(List postfix_list)
{
    Stack postfix_stack;
    Stack operation_stack;
    int index = 0;

    int total;

    while (index < postfix_list.sizeOfListArray())
    {
        if(isdigit(postfix_list.list_array[index]))
        {
            postfix_stack.push(postfix_list.list_array[index]);
        }
        else
        {
            int op1;
            int op2;

            if(isdigit(postfix_stack.top()))
            {
                op1 = postfix_stack.top() - '0';
                postfix_stack.pop();
            }
            else
            {
                op1 = total;
            }

            if(isdigit(postfix_stack.top()))
            {
                op2 = postfix_stack.top() - '0';
                postfix_stack.pop();
            }
            else
            {
                op2 = total;
            }

            total = evaulate(op1,op2,postfix_list.list_array[index]);

            postfix_stack.push(total);

        }

        index++;
    }

    return total;
}

int evaulate(int op1, int op2, char optr)
{
   switch(optr)
   {
      case '*': return op2 * op1;
      case '/': return op2 / op1;
      case '+': return op2 + op1;
      case '-': return op2 - op1;
      default : return 0;
   }
}

int calc_weight(char c)
{
    int weight = 0;

    switch(c)
    {
        case '+':
        case '-':
            weight = 1;
            break;
        case '*':
        case '/':
            weight = 2;
            break;
    }

    return weight;
}

int main()
{
    int choice;
    int index = 0;
    int numberOfVars = 0;
    int infixIndex = 0;
    int sizeOfList = 0;
    string infix;
    List infix_list;
    List variable_list;
    List input_list;
    List postfix_list;

    while(true)
    {

    cout << "Please choose an operation:" << endl;
    cout << "1) Enter an infix expression and convert to postfix" << endl;
    cout << "2) Evaluate expression" << endl;
    cout << "3) Exit" << endl;

    cin >> choice;
    cin.ignore(1000,'\n');


    switch(choice)
    {
        case 1:

            cout << "Please enter your infix expression: " << endl;
            getline(cin, infix);

            cout << "You entered: " ;

            while(infix[index] != '#')
            {
                if(infix[index] != ' ')
                {
                    infix_list.list_array[infixIndex] = infix[index];

                    sizeOfList++;

                    cout << infix[index];

                    infixIndex++;
                }

                if(isalpha(infix[index]))
                {
                    variable_list.list_array[numberOfVars] = infix[index];
                    numberOfVars++;
                }

                index++;
            }

            cout << endl;

            postfix_list = convert(infix_list, sizeOfList);

            break;
        case 2:
            cout << "Your current expression is: ";

            for(int i = 0; i < sizeOfList; i++)
            {
                cout << infix_list.list_array[i];
            }

            cout << endl;

            cout << "Your postfix expression is: ";

            for(int i = 0; i < sizeOfList; i++)
            {
                cout << postfix_list.list_array[i];
            }

            cout << endl;
            cout << "Please input integers for the variables in the expression: " << endl;

            for(int i = 0; i < postfix_list.sizeOfListArray(); i++)
            {
                if(isalpha(postfix_list.list_array[i]))
                {
                    cout << postfix_list.list_array[i] << ":" << endl;
                    cin >> postfix_list.list_array[i];
                }
            }

            for(int i = 0; i < postfix_list.sizeOfListArray(); i++)
            {
                cout << postfix_list.list_array[i];
            }

            cout << " = " << convertEval(postfix_list) << endl << endl;

            break;
        case 3:
            return 0;
            break;

        default:
            cout << "You input an incorrect character...";
            return 0;
    }
    }

    return 0;
}
