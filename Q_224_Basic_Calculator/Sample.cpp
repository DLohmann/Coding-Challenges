#include"Sample.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>
#include<climits>

using namespace std;

namespace sample {
    class Token {
        public:

        enum class TokenType { number, operation };
        enum class TokenOperationType { na, plus, minus, multiply, divide };

        // Operation constructor
        Token(int start_index, int end_index, TokenOperationType operation, string str) {
            this->start_index = start_index;
            this->end_index = end_index;
            this->type = TokenType::operation;
            this->operation = operation;
            this->priority = getPriority(operation);
            this->str = str;
        }

        // Number constructor
        Token(int start_index, int end_index, int value, string str) {
            this->start_index = start_index;
            this->end_index = end_index;
            this->value = value;
            this->type = TokenType::number;
            this->priority = 0;
            this->str = str;
        }

        ~Token() {
            input.clear();
        }

        int value = INT_MIN;
        int start_index = -1; // inclusive
        int end_index = -1;   // exclusive
        TokenType type = TokenType::operation;
        TokenOperationType operation = TokenOperationType::na;

        // Token is an input to the parent node (except for root)
        Token* parent = nullptr;

        // If an operation, set this to the input parameters
        vector<Token*> input;

        // Adjacent tokens in the original expression.
        Token* left_neighbor = nullptr;
        Token* right_neighbor = nullptr;

        // TokenOperationType priority for order of operations (GEMDAS)
        // 0: Number. Already evaluated.
        // 1: Grouping symbols ()
        // 2: Exponents
        // 3: Multiply and Divide */
        // 4: Add and Subtract +-
        int priority = -1;

        static int getPriority(TokenOperationType operation) {
            switch(operation) {
                case TokenOperationType::na:
                    return 0;
                case TokenOperationType::multiply:
                case TokenOperationType::divide:
                    return 3;
                case TokenOperationType::plus:
                case TokenOperationType::minus:
                    return 4;
                default:
                    cout << "Strange type! (priority -1)" << endl;
                    return -1;
            }
        }
        
        // string representation of token (for debugging)
        string str;
        
        int numRequiredInputs(){
            if (type == TokenType::number) {
                return 0;
            }
            switch(operation) {
                // Currently all operations (+-*/) require 2 inputs
                default:
                    return 2;
            }
        }

        // Post-order depth-first traversal to calculate expression tree
        int evaluate() {
            if (type == TokenType::number) {
                // Number is already evaluated
                //cout << "Can only evaluate operation, not TokenType " << type << endl;
                return value;
            }

            if (input.size() < numRequiredInputs()) {
                cout << "Evaluate() called for \"" << str << "\" with " << input.size() << " inputs, but " << numRequiredInputs() << " are required for this token type!" << endl;
                return INT_MIN;
            }
            for (int i = 0; i < numRequiredInputs(); i++) {
                if (input[i] == nullptr) {
                    cout << "evaluate() called on Token \"" << str << "\" before input " << i << " set! Requires " << numRequiredInputs() << " inputs." << endl;
                    return INT_MIN;
                }
            }

            for (int i = 0; i < input.size(); i++) {
                input[i]->evaluate();
            }

            // Currently all operations should have 2 parameters; one on right and one on left.
            // Right parameter is added first, to deal with cases like "+1"  or "-1".
            int right_parameter = input[0]->value;
            int left_parameter = input[1]->value;

            switch(operation) {
                case TokenOperationType::plus:
                    value = left_parameter + right_parameter;
                    break;
                case TokenOperationType::minus:
                    value = left_parameter - right_parameter;
                    break;
                case TokenOperationType::multiply:
                    value = left_parameter * right_parameter;
                    break;
                case TokenOperationType::divide:
                    value = left_parameter / right_parameter;
                    break;
                default:
                    cout << "Unknown operation" << endl;
                    value = INT_MIN;
            }
            cout << "evaluate token \"" << str << "\" returns " << value << endl;
            return value;
        }
    };

    Token* numberToken(string& s, int start_index) {
        cout << "\tnumberToken \"" << s << "\", start_index: " << start_index << endl << "\t";
        int val = 0;
        int i;
        for (i = start_index; '0' <= s[i] && s[i] <= '9'; i++) {
            val = (val * 10) + int(s[i] - '0');
            cout << s[i];
        }
        cout << endl;
        cout << "\tval: " << val << ", char length: " << i - start_index << endl;
        return new Token(start_index, i, val, s.substr(start_index, i - start_index));
    }

    Token* operationToken(string& s, int start_index) {
        cout << "\toperationToken \"" << s << "\", start_index: " << start_index << endl << "\toperation\'" << s[start_index] << "\'" << endl ;

        Token::TokenOperationType operation;
        switch(s[start_index]) {
            case '+':
                operation = Token::TokenOperationType::plus;
                break;
            case '-':
                operation = Token::TokenOperationType::minus;
                break;
            case '*':
                operation = Token::TokenOperationType::multiply;
                break;
            case '/':
                operation = Token::TokenOperationType::divide;
                break;
            default:
                operation = Token::TokenOperationType::na;
                cout << "Error! Unknown operation \'" << s[start_index] << "\'" << endl;
        }
        return new Token(start_index, start_index + 1, operation, s.substr(start_index, 1));
    }

    void printTokens(list<Token*>& tokens) {
        cout << "Tokens: {";
        for (Token* t : tokens) {
            if (t->type == Token::TokenType::number) {
                cout << t->value;
                continue;
            }
            switch(t->operation) {
                case Token::TokenOperationType::plus:
                    cout << "+";
                    break;
                case Token::TokenOperationType::minus:
                    cout << "-";
                    break;
                case Token::TokenOperationType::multiply:
                    cout << "*";
                    break;
                case Token::TokenOperationType::divide:
                    cout << "/";
                    break;
                default:
                    cout << " unknown token ";
            }
        }
        cout << "}, size = " << tokens.size() << endl;
        cout << "Priorities: {  ";
        for (Token* t : tokens) {
            cout << t->priority << "  ";
        }
        cout << "}" << endl;
    }


    int Solution::calculate(string s) {
        cout << "calculate(\"" << s << "\")" <<  endl;



        // Tokenizer: Parse string into list of tokens
        list<Token*> tokens;
        for (long unsigned int i = 0; i < s.size();) {
            if (s[i] == ' ') {
                cout << "skip \' \'" << endl;
                i++;
                continue;
            }
            if ('0' <= s[i] && s[i] <='9') {
                cout << "number" << endl;
                Token* t = numberToken(s, i);
                i = t->end_index;
                tokens.push_back(t);
                continue;
            }

            switch (s[i]) {
                case '+':
                case '-':
                case '*':
                case '/':
                    {
                        cout << "operation" << endl;
                        Token* t = operationToken(s, i);
                        i = t->end_index;
                        tokens.push_back(t);
                        continue;
                    }
                default:
                    {
                        cout << "unhandled \'" << s[i] << "\'" << endl;
                        i++;
                        continue;
                    }
            }

        }
        if (tokens.empty()) {
            cout << "No tokens found!" << endl;
            return INT_MIN;
        }

        // Set token neighbors, between tokens
        list<Token*>::iterator prev = tokens.begin();
        cout << endl << "Neighbors" << endl;
        for (list<Token*>::iterator it = next(tokens.begin()); it != tokens.end(); it++) {
            (*prev)->right_neighbor = *it;
            (*it)->left_neighbor = *prev;
            // int previous_start  = (*prev)->start_index;
            // int previous_length = (*prev)->end_index - previous_start;
            // int current_start   = (*it)->start_index;
            // int current_length  = (*it)->end_index - current_start;
            cout << "\t\"" << (*prev)->str << "\" and \"" << (*it)->str << "\"" << endl;
            prev = it;
        }

        cout << endl;
        printTokens(tokens);

        


        // Prioritize tokens by order of operations. Number tokens first (lowest priority),
        // then parse operation tokens from lowest priority to highest priority into operation
        // tree, with lowest priority (numbers) at the leaves. All leaf nodes should be numbers,
        // but all parent nodes should be operations. Build tree using bottom-up approach.
        vector<Token*> prioritizer(tokens.begin(), tokens.end());
        sort(prioritizer.begin(), prioritizer.end(),
                [](Token* x, Token* y){
                    return x->priority < y->priority;
                }
            );

        cout << "Prioritized tokens:" << endl;
        for (Token* token : prioritizer) {
            cout << token->str << endl;
        }

        // Skip over numbers (priority 0)
        int i;
        for (i = 0; i < prioritizer.size(); i++) {
            if (prioritizer[i]->type != Token::TokenType::number) {
                break;
            }
        }
        cout << i << " numbers found" << endl;

        // Build expression tree. Set operation Token inputs and
        // parents. Parse operation low priority tokens (*/) then high priority
        // tokens (+-) left to right.
        for (; i < prioritizer.size(); i++) {
            Token* token = prioritizer[i];

            Token* right_parameter;
            // Add right neighbor (or ancestor without parent) to input
            if (token->right_neighbor == nullptr) {
                cout << "Error: Token \"" << token->str << "\" does not have right neighbor token." << endl;
            }
            right_parameter = token->right_neighbor;
            while(right_parameter->parent != nullptr) {
                right_parameter = right_parameter->parent;
            }
            right_parameter->parent = token;
            token->input.push_back(right_parameter);
            
            Token* left_parameter;
            // Add left neighbor (or ancestor without parent) to input
            if (token->left_neighbor == nullptr) {
                cout << "Error: Token \"" << token->str << "\" does not have left neighbor token." << endl;
            }
            left_parameter = token->left_neighbor;
            while(left_parameter->parent != nullptr) {
                left_parameter = left_parameter->parent;
            }
            left_parameter->parent = token;
            token->input.push_back(left_parameter);
        }

        
        Token* root = prioritizer.back();
        while (root->parent != nullptr) {
            cout << "Moving root from \"" << root->str << "\" to \"" << root->parent->str << "\"" <<  endl;
            root = root->parent;
        }

        // Recursive post-order traversal of expression tree to evaluate
        cout << endl << "root->evaluate: (root == " << root->str << "):" << endl;
        int result = root->evaluate();

        for (Token* token : tokens) {
            delete token;
        }
        return result;
    }

} // namespace sample



// TODO: Add support for negative sign -. Approaches:
// - If an operator token - or + does not have a left neighbor token, then set the result
//   of the left neighbor token to 0.
// - If an operator token - or + does not have a left neighbor token but does have a right
//   neighbor token, then insert a '0' number token as left token.
// - If an operator - or + does not have a left neighbor token but does have a right
//   neighbor token, then delete this operator token and set the right neighbor token
//   to negative for - or leave it alone for +. The problem is that for parenthesis '('
//   it would be difficult to set value to negative if not evaluated yet.

// TODO: Add support for parenthesis (). Several approaches:
// - Maybe make a different TokenType "grouping"
//      * Only 1 input in numRequiredInputs and priority 1.
//      * Evaluate() can return same input value.
//      * When tokenizing '(', move right until # close parenthesis ')' after the
//       '(' equals one (for the '(') plus the number of '(' after the initial
//       '(', so it is balanced. Then try to set left and right neighbors
//       right there.
//      * When tokenizing ')' move left until balanced. Then try to set left and
//        right neighbors.
//      * If '(' or ')' are unbalanced, return error.
//      * If an operation had beginning or end of string, or '(' or ')' next to
//        it, so the operation lacks parameters, then return error.
// - Search for pairs of parenthesis within group s, and get the substring. Then
//   call calculate(string s) recursively on the substring and calculate the
//   value. Then use 1 single number token for the entire substring in parenthesis.
//   For nested parenthesis, this should happen recursively.
// - Every item in parenthesis could have priority adjusted so it could be 
//   evaluated separately. So parenthesis would not be a token, but would adjust
//   the order of tokens within it, and ensure that they must be resolved before
//   interacting with outside tokens.
