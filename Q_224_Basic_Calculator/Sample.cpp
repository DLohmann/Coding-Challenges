#include"Sample.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>
#include<climits>

#include <glog/logging.h>

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
                    LOG(INFO) << "Strange type! (priority -1)" << endl;
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
                //LOG(INFO) << "Can only evaluate operation, not TokenType " << type << endl;
                return value;
            }

            if (input.size() < size_t(numRequiredInputs())) {
                LOG(INFO) << "Evaluate() called for \"" << str << "\" with " << input.size() << " inputs, but " << numRequiredInputs() << " are required for this token type!" << endl;
                return INT_MIN;
            }
            for (int i = 0; i < numRequiredInputs(); i++) {
                if (input[i] == nullptr) {
                    LOG(INFO) << "evaluate() called on Token \"" << str << "\" before input " << i << " set! Requires " << numRequiredInputs() << " inputs." << endl;
                    return INT_MIN;
                }
            }

            for (long unsigned int i = 0; i < input.size(); i++) {
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
                    LOG(INFO) << "Unknown operation" << endl;
                    value = INT_MIN;
            }
            LOG(INFO) << "evaluate token \"" << str << "\" returns " << value << endl;
            return value;
        }
    };

    Token* numberToken(string& s, int start_index) {
        LOG(INFO) << "\tnumberToken \"" << s << "\", start_index: " << start_index << endl << "\t";
        int val = 0;
        int i = start_index;
        bool is_negative = false;
        if (s[start_index] == '-') {
            while(i < s.length() && !('0' <= s[i] && s[i] <= '9')) {
                if (s[i] == '-') {
                    is_negative = !is_negative;
                }
                i++;
            }
            CHECK(i < s.length()) << "Negative number \"" << s.substr(start_index) << "\" reached unexpected end of string." << endl;
        }
        for (; '0' <= s[i] && s[i] <= '9'; i++) {
            val = (val * 10) + int(s[i] - '0');
            LOG(INFO) << s[i];
        }
        if (is_negative) {
            val *= -1;
        }
        LOG(INFO) << endl;
        LOG(INFO) << "\tval: " << val << ", char length: " << i - start_index << endl;
        return new Token(start_index, i, val, s.substr(start_index, i - start_index));
    }

    Token* operationToken(string& s, int start_index) {
        LOG(INFO) << "\toperationToken \"" << s << "\", start_index: " << start_index << endl << "\toperation\'" << s[start_index] << "\'" << endl ;

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
                LOG(INFO) << "Error! Unknown operation \'" << s[start_index] << "\'" << endl;
        }
        return new Token(start_index, start_index + 1, operation, s.substr(start_index, 1));
    }

    void printTokens(list<Token*>& tokens) {
        LOG(INFO) << "Tokens: {";
        for (Token* t : tokens) {
            if (t->type == Token::TokenType::number) {
                LOG(INFO) << t->value;
                continue;
            }
            switch(t->operation) {
                case Token::TokenOperationType::plus:
                    LOG(INFO) << "+";
                    break;
                case Token::TokenOperationType::minus:
                    LOG(INFO) << "-";
                    break;
                case Token::TokenOperationType::multiply:
                    LOG(INFO) << "*";
                    break;
                case Token::TokenOperationType::divide:
                    LOG(INFO) << "/";
                    break;
                default:
                    LOG(INFO) << " unknown token ";
            }
        }
        LOG(INFO) << "}, size = " << tokens.size() << endl;
        LOG(INFO) << "Priorities: {  ";
        for (Token* t : tokens) {
            LOG(INFO) << t->priority << "  ";
        }
        LOG(INFO) << "}" << endl;
    }


    int Solution::calculate(string s) {
        LOG(INFO) << "calculate(\"" << s << "\")" <<  endl;



        // Tokenizer: Parse string into list of tokens
        list<Token*> tokens;
        for (long unsigned int i = 0; i < s.size();) {
            if (s[i] == ' ') {
                LOG(INFO) << "skip \' \'" << endl;
                i++;
                continue;
            }

            // If the character is a number, interpret as positive integer.
            // If the character is negative '-', and any of the following is true:
            // - No tokens have been added (tokens is empty, so beginning of expression) OR
            // - The previous token is an opening grouping symbol, such as '(' OR
            // - The previous token is an operation such as +-*/
            // Then interpret as negative.
            //
            if (('0' <= s[i] && s[i] <='9') || 
                    (s[i] == '-' && 
                        (tokens.empty() || tokens.back()->str == "(" || tokens.back()->type == Token::TokenType::operation)
                    )
                ) {
                LOG(INFO) << "number" << endl;
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
                        LOG(INFO) << "operation" << endl;
                        Token* t = operationToken(s, i);
                        i = t->end_index;
                        tokens.push_back(t);
                        continue;
                    }
                case '(':
                case ')':
                default:
                    {
                        LOG(INFO) << "unhandled \'" << s[i] << "\'" << endl;
                        i++;
                        continue;
                    }
            }

        }
        if (tokens.empty()) {
            LOG(INFO) << "No tokens found!" << endl;
            return INT_MIN;
        }

        // Set token neighbors, between tokens
        list<Token*>::iterator prev = tokens.begin();
        LOG(INFO) << endl << "Neighbors" << endl;
        for (list<Token*>::iterator it = next(tokens.begin()); it != tokens.end(); it++) {
            (*prev)->right_neighbor = *it;
            (*it)->left_neighbor = *prev;
            // int previous_start  = (*prev)->start_index;
            // int previous_length = (*prev)->end_index - previous_start;
            // int current_start   = (*it)->start_index;
            // int current_length  = (*it)->end_index - current_start;
            LOG(INFO) << "\t\"" << (*prev)->str << "\" and \"" << (*it)->str << "\"" << endl;
            prev = it;
        }

        LOG(INFO) << endl;
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

        LOG(INFO) << "Prioritized tokens:" << endl;
        for (Token* token : prioritizer) {
            LOG(INFO) << token->str << endl;
        }

        // Skip over numbers (priority 0)
        long unsigned int i;
        for (i = 0; i < prioritizer.size(); i++) {
            if (prioritizer[i]->type != Token::TokenType::number) {
                break;
            }
        }
        LOG(INFO) << i << " numbers found" << endl;

        // Build expression tree. Set operation Token inputs and
        // parents. Parse operation low priority tokens (*/) then high priority
        // tokens (+-) left to right.
        for (; i < prioritizer.size(); i++) {
            Token* token = prioritizer[i];

            Token* right_parameter;
            // Add right neighbor (or ancestor without parent) to input
            if (token->right_neighbor == nullptr) {
                LOG(INFO) << "Error: Token \"" << token->str << "\" does not have right neighbor token." << endl;
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
                LOG(INFO) << "Error: Token \"" << token->str << "\" does not have left neighbor token." << endl;
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
            LOG(INFO) << "Moving root from \"" << root->str << "\" to \"" << root->parent->str << "\"" <<  endl;
            root = root->parent;
        }

        // Recursive post-order traversal of expression tree to evaluate
        LOG(INFO) << endl << "root->evaluate: (root == " << root->str << "):" << endl;
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
// - During tokenization, after reaching the negative sign '-', if either no tokens have
//   been added yet so '-' is the first one, or the previous token was opening grouping
//   '(' or an operation +-*/, then interpret as negative.

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

