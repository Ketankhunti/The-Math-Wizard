#include<bits/stdc++.h>

using namespace std;

void insertIntoMap(map<string,char>& map){
    map["zero"] = 0;
    map["one"] = '1';
    map["two"] = '2';
    map["three"] = '3';
    map["four"] = '4';
    map["five"] = '5';
    map["six"] = '6';
    map["seven"] = '7'; 
    map["eight"] = '8';
    map["nine"] = '9';
    map["plus"]='+';
    map["substract"]='-';
    map["multiple"]='*';
    map["division"]='/';
    map["equals"]='=';
 }

string convertIntoMathExpression(map<string,char>& map,string str) {
     string ans="";
     for(int i=0;i<str.length();i++){
        if(str[i]==' ') continue;
        else if(str[i]>='0' && str[i]<='9'){
            ans+=str[i];
        }
        else if(str[i]=='+' || str[i]=='-' || str[i]=='/' || str[i]=='*' || str[i]=='='||str[i]=='.'){
            ans+=str[i];
        }
        else{
            string temp="";
            int j=i;
            while(j<str.length() && (str[j]>='a' && str[j]<='z')){
              temp+=str[j];
              j++;
            }
            ans += map[temp];
            i=j-1;
        }
     }
    // cout<<ans<<endl;
     return ans;
  
}

// Function to find precedence of
// operators.
int precedence(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
 
// Function to perform arithmetic operations.
int applyOp(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return -1;
}
 
// Function that returns value of
// expression after evaluation.
int evaluate(string tokens){
    int i;
     
    // stack to store integer values.
    stack <int> values;
     
    // stack to store operators.
    stack <char> ops;
     
    for(i = 0; i < tokens.length(); i++){
         
        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;
         
        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
         
        // Current token is a number, push
        // it to stack for numbers.
        else if(isdigit(tokens[i])){
            int val = 0;
             
            // There may be more than one
            // digits in number.
            while(i < tokens.length() &&
                        isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
             
            values.push(val);
             
            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            //  token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
              i--;
        }
         
        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
             
            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }
         
        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // precedence to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in values stack.
            while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
             
            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }
     
    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // values.
    while(!ops.empty()){
        int val2 = values.top();
        values.pop();
                 
        int val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOp(val1, val2, op));
    }
     
   // cout << values.top() << endl; 
    // Top of 'values' contains result, return it.
    return values.top();
}

int main(int argc, char **argv) {

//    freopen("input.txt", "r", stdin);
   freopen("output_large.txt", "w", stdout);

    map<string,char> map;
 int count=1;
    insertIntoMap(map);

      string str;
       
      ifstream infile("input.txt"); 
      int cnt=1;
      while(getline(infile,str)){
        if(cnt == 1) 
        { 
            cnt++;
             continue;
        }
       // cout<<str<<endl;

        string expr = convertIntoMathExpression(map, str);

      //  cout<<expr<<endl;
          
         string s1="",s2="";

         int i=0;

         while(expr[i]!='='){
             s1+=expr[i];
             i++;
         }
        i++;
         
      
         double leftSide = evaluate(s1);

        cout<<s1<<endl;
  
         while(i<expr.length()){
            s2 += expr[i];
            i++;
         } 

         cout<<s2<<endl;
        
         double rightSide = stod(s2);

         cout << "Case #"<<count<<": ";
         if(leftSide==rightSide) cout << "true" <<endl;
         else cout << "false" <<endl;
         
         count++;
       
      } 

}