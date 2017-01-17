#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int precedence(const string & op)
{
    switch(op[0])
    {
    case '*':
    case '/':
    case '%':
        return 2;

    case '+':
    case '-':
        return 1;

    default:
        return 0;
    }
}

string infix_to_postfix(const string & infix)
{
    string token;
    stack<string> s;
    string ans;

    for(int i=0;i<infix.size();++i)
    {
        token=infix[i];

        if (token == "(")
            s.push(token);

        if (token == ")")
        {
            while (s.top() != "(")
            {
                //ans += " ";
                ans += s.top();
                s.pop();
            }
            s.pop();

        }
        if (token == "+" || token == "-" || token == "*" ||
                token == "/" || token == "%")
        {
            while (!s.empty() &&
                   (precedence(s.top()) >= precedence(token)))
                {
                    //ans += " ";
                    ans += s.top();
                    s.pop();
                }
             s.push(token);
        }
        else // operand
        {
            //ans += " ";
            ans += token;

        }
    }
    while (!s.empty())
    {
        //ans += " ";
        ans += s.top();
        s.pop();
    }
    return ans;
}

bool and_them(bool a, bool b)
{
    return a&&b;
}

bool invert(bool a)
{
    if (a==1)
        return 0;
    return 1;
}

bool or_them(bool a, bool b)
{
    return a||b;
}

vector<char> get_variables(vector<char> list_variables)
{
   char variable;
    while (variable!='X')
    {
        cout<<"Enter a variable. A variable is represented by an individual letter. Enter 'X' when done."<<endl;
        cin>>variable;
        variable = toupper(variable);
        if(variable != 'X')
            list_variables.push_back(variable);
    }

    sort(list_variables.begin(), list_variables.end());
    return list_variables;
}

vector<string> get_expressions(vector<string> list_expressions, vector<char> list_variables)
{
    string muahaha="'lalala";
    char invert_symbol= muahaha[0];
    string expression;
    while (expression!="X")
    {
        cout<<"Enter a string with no spaces of a boolean expression. Enter 'X' when done."<<endl;
        cin>>expression;
        for (int i=0; i<expression.size();++i)
            if (expression[i]-0>=97 && expression[i]-0<=122)
                expression[i] = toupper(expression[i]);

        bool valid_expression = true;
        for (auto char_expression: expression)
        {
            if(char_expression == '+' || char_expression == '*' || char_expression == '(' || char_expression == ')' || char_expression == invert_symbol)
                continue;
            else if(find(list_variables.begin(),list_variables.end(),char_expression) == list_variables.end())
            {
                cout<<"You entered an incorrect letter:"<<char_expression<<endl;
                valid_expression=false;
            }
        }
        if(valid_expression)
            list_expressions.push_back(expression);
    }

    return list_expressions;
}

vector<vector<bool>> create_input_combos(vector<char> list, int list_size)
{
    vector<vector<bool>> input_combos;
    vector<bool> combo;

    for (int i=0; i<list.size(); ++i)
    {
        combo.push_back(0);
    }

    input_combos.push_back(combo);
    vector<bool> temp_combo=combo;
    for (int i = 1; i < pow(2,list_size); ++i)
    {
        for(int j=temp_combo.size()-1;j>=0;--j)
        {
            if (temp_combo[j] == 0)
            {
                temp_combo[j] = 1;
                j = -1;
            }
            else
            {
                temp_combo[j] = 0;
            }
        }
        combo=temp_combo;
        input_combos.push_back(combo);
    }
    return input_combos;
}

void translate_logic(vector<string> list_expressions, vector<vector<bool>> input_combos, vector<char> list_variables)
{
    pair<char,bool> cbpair;

    string muahaha="'lalala";
    char invert_symbol=muahaha[0];

    for (auto expression: list_expressions)
    {

        cout << "-----------------------------------" << endl;
        cout << expression << endl;

        expression = infix_to_postfix(expression);
        sort(list_variables.begin(), list_variables.end());

        for (auto combo: input_combos)
        {
            stack<bool> s;
            for (auto character:expression)
            {
                if(character-0>=65 && character-0<=90)
                {
                    for(int i=0;i<list_variables.size();++i)
                    {
                        if(character==list_variables[i])
                        {
                             cbpair=make_pair(character,combo[i]);
//                             cout<<"!"<<character<<", i="<<i<< " ---- ";
                             s.push(cbpair.second);
//                             cout<<"<"<<cbpair.first<<","<<cbpair.second<<">"<<endl;
                        }
                    }
                }
                else
                {
                    if (character=='+')
                    {
                        bool value1=s.top();
                        s.pop();
                        bool value2=s.top();
                        s.pop();
                        bool new_value=or_them(value1,value2);
                        s.push(new_value);
//                        cout<<value1<<character<<value2<<"="<<new_value<<endl;
//                        cout<<s.size()<<endl;
                    }

                    else if (character=='*')
                    {
                        bool value1=s.top();
                        s.pop();
                        bool value2=s.top();
                        s.pop();
                        bool new_value=and_them(value1,value2);
                        s.push(new_value);
//                        cout<<value1<<character<<value2<<"="<<new_value<<endl;
                    }

                    else if (character == invert_symbol)
                    {
                        bool value=s.top();
                        s.pop();
                        value=invert(value);
                        s.push(value);
                    }
                }
            }

            for (int i=0;i<combo.size();++i)
                cout<<combo[i];
            cout<<": "<<s.top()<<endl;
        }
         cout<<"-----------------------------------"<<endl;
    }
}

void print_input_combos(vector<vector<bool>> input_combos)
{
    for(auto e:input_combos)
    {
        for(auto f:e)
            cout<<f<<" ";
        cout<<endl;
    }
}

void print_all_variables (vector<string> list,int list_size)
{
    for (auto e:list)
        cout<<e<<" ";
    cout<<endl;

    cout<<"Amount of variables: "<<list_size<<endl;
}

int main(int argc, char *argv[])
{

    vector<char> list_variables;
    vector<string> list_expressions;
    vector<vector<bool>> input_combos;

    list_variables = get_variables(list_variables);
    list_expressions = get_expressions(list_expressions, list_variables);

    int list_variables_size = list_variables.size();
    input_combos = create_input_combos(list_variables, list_variables_size);

    translate_logic(list_expressions, input_combos, list_variables);

    return 0;
}
