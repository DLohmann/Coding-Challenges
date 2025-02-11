#include"Sample.h"

#include<algorithm>
#include<climits>
#include<glog/logging.h>
#include<iostream>
#include<list>
#include<memory>
#include<vector>


namespace sample {
    class Token {
        public:

        enum class TokenType { number, operation };
        enum class TokenOperationType { na, plus, minus, multiply, divide };

        // Operation constructor
        Token(int start_index, int end_index, TokenOperationType operation, std::string str) {
            this->start_index = start_index;
            this->end_index = end_index;
            this->type = TokenType::operation;
            this->operation = operation;
            this->priority = getPriority(operation);
            this->str = str;
        }

        // Number constructor
        Token(int start_index, int end_index, int value, std::string str) {
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
        std::shared_ptr<Token> parent = nullptr;

        // If an operation, set this to the input parameters
        std::vector< std::shared_ptr<Token> > input;

        // Adjacent tokens in the original expression.
        std::shared_ptr<Token> left_neighbor = nullptr;
        std::shared_ptr<Token> right_neighbor = nullptr;

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
                    LOG(INFO) << "Strange type! (priority -1)" << std::endl;
                    return -1;
            }
        }
        
        // string representation of token (for debugging)
        std::string str;
        
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
                //LOG(INFO) << "Can only evaluate operation, not TokenType " << type << std::endl;
                return value;
            }

            if (input.size() < size_t(numRequiredInputs())) {
                LOG(INFO) << "Evaluate() called for \"" << str << "\" with " << input.size() << " inputs, but " << numRequiredInputs() << " are required for this token type!" << std::endl;
                return INT_MIN;
            }
            for (int i = 0; i < numRequiredInputs(); i++) {
                if (input[i] == nullptr) {
                    LOG(INFO) << "evaluate() called on Token \"" << str << "\" before input " << i << " set! Requires " << numRequiredInputs() << " inputs." << std::endl;
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
                    LOG(INFO) << "Unknown operation" << std::endl;
                    value = INT_MIN;
            }
            LOG(INFO) << "evaluate token \"" << str << "\" returns " << value << std::endl;
            return value;
        }
    };

    std::shared_ptr<Token> numberToken(std::string& s, int start_index) {
        LOG(INFO) << "\tnumberToken \"" << s << "\", start_index: " << start_index << std::endl << "\t";
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
            CHECK(i < s.length()) << "Negative number \"" << s.substr(start_index) << "\" reached unexpected end of string." << std::endl;
        }
        for (; '0' <= s[i] && s[i] <= '9'; i++) {
            val = (val * 10) + int(s[i] - '0');
            LOG(INFO) << s[i];
        }
        if (is_negative) {
            val *= -1;
        }
        LOG(INFO) << std::endl;
        LOG(INFO) << "\tval: " << val << ", char length: " << i - start_index << std::endl;
        return std::make_unique<Token>(start_index, i, val, s.substr(start_index, i - start_index));
    }

    std::shared_ptr<Token> operationToken(std::string& s, int start_index) {
        LOG(INFO) << "\toperationToken \"" << s << "\", start_index: " << start_index << std::endl << "\toperation\'" << s[start_index] << "\'" << std::endl ;

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
                LOG(INFO) << "Error! Unknown operation \'" << s[start_index] << "\'" << std::endl;
        }
        return std::make_unique<Token>(start_index, start_index + 1, operation, s.substr(start_index, 1));
    }

    void printTokens(std::list< std::shared_ptr<Token> >& tokens) {
        LOG(INFO) << "Tokens: {";
        for (std::shared_ptr<Token> t : tokens) {
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
        LOG(INFO) << "}, size = " << tokens.size() << std::endl;
        LOG(INFO) << "Priorities: {  ";
        for (std::shared_ptr<Token> t : tokens) {
            LOG(INFO) << t->priority << "  ";
        }
        LOG(INFO) << "}" << std::endl;
    }


    int Solution::calculate(std::string s) {
        LOG(INFO) << "calculate(\"" << s << "\")" <<  std::endl;



        // Tokenizer: Parse string into std::list of tokens
        std::list< std::shared_ptr<Token> > tokens;
        for (long unsigned int i = 0; i < s.size();) {
            if (s[i] == ' ') {
                LOG(INFO) << "skip \' \'" << std::endl;
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
                LOG(INFO) << "number" << std::endl;
                std::shared_ptr<Token> t = numberToken(s, i);
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
                        LOG(INFO) << "operation" << std::endl;
                        std::shared_ptr<Token> t = operationToken(s, i);
                        i = t->end_index;
                        tokens.push_back(t);
                        continue;
                    }
                case '(':
                case ')':
                default:
                    {
                        LOG(INFO) << "unhandled \'" << s[i] << "\'" << std::endl;
                        i++;
                        continue;
                    }
            }

        }
        if (tokens.empty()) {
            LOG(INFO) << "No tokens found!" << std::endl;
            return INT_MIN;
        }

        // Set token neighbors, between tokens
        std::list< std::shared_ptr<Token> >::iterator prev = tokens.begin();
        LOG(INFO) << std::endl << "Neighbors" << std::endl;
        for (std::list< std::shared_ptr<Token> >::iterator it = next(tokens.begin()); it != tokens.end(); it++) {
            (*prev)->right_neighbor = *it;
            (*it)->left_neighbor = *prev;
            // int previous_start  = (*prev)->start_index;
            // int previous_length = (*prev)->end_index - previous_start;
            // int current_start   = (*it)->start_index;
            // int current_length  = (*it)->end_index - current_start;
            LOG(INFO) << "\t\"" << (*prev)->str << "\" and \"" << (*it)->str << "\"" << std::endl;
            prev = it;
        }

        LOG(INFO) << std::endl;
        printTokens(tokens);

        


        // Prioritize tokens by order of operations. Number tokens first (lowest priority),
        // then parse operation tokens from lowest priority to highest priority into operation
        // tree, with lowest priority (numbers) at the leaves. All leaf nodes should be numbers,
        // but all parent nodes should be operations. Build tree using bottom-up approach.
        std::vector< std::shared_ptr<Token> > prioritizer(tokens.begin(), tokens.end());
        sort(prioritizer.begin(), prioritizer.end(),
                [](std::shared_ptr<Token> x, std::shared_ptr<Token> y){
                    return x->priority < y->priority;
                }
            );

        LOG(INFO) << "Prioritized tokens:" << std::endl;
        for (std::shared_ptr<Token> token : prioritizer) {
            LOG(INFO) << token->str << std::endl;
        }

        // Skip over numbers (priority 0)
        long unsigned int i;
        for (i = 0; i < prioritizer.size(); i++) {
            if (prioritizer[i]->type != Token::TokenType::number) {
                break;
            }
        }
        LOG(INFO) << i << " numbers found" << std::endl;

        // Build expression tree. Set operation Token inputs and
        // parents. Parse operation low priority tokens (*/) then high priority
        // tokens (+-) left to right.
        for (; i < prioritizer.size(); i++) {
            std::shared_ptr<Token> token = prioritizer[i];

            std::shared_ptr<Token> right_parameter;
            // Add right neighbor (or ancestor without parent) to input
            if (token->right_neighbor == nullptr) {
                LOG(INFO) << "Error: Token \"" << token->str << "\" does not have right neighbor token." << std::endl;
            }
            right_parameter = token->right_neighbor;
            while(right_parameter->parent != nullptr) {
                right_parameter = right_parameter->parent;
            }
            right_parameter->parent = token;
            token->input.push_back(right_parameter);
            
            std::shared_ptr<Token> left_parameter;
            // Add left neighbor (or ancestor without parent) to input
            if (token->left_neighbor == nullptr) {
                LOG(INFO) << "Error: Token \"" << token->str << "\" does not have left neighbor token." << std::endl;
            }
            left_parameter = token->left_neighbor;
            while(left_parameter->parent != nullptr) {
                left_parameter = left_parameter->parent;
            }
            left_parameter->parent = token;
            token->input.push_back(left_parameter);
        }

        
        std::shared_ptr<Token> root = prioritizer.back();
        while (root->parent != nullptr) {
            LOG(INFO) << "Moving root from \"" << root->str << "\" to \"" << root->parent->str << "\"" <<  std::endl;
            root = root->parent;
        }

        // Recursive post-order traversal of expression tree to evaluate
        LOG(INFO) << std::endl << "root->evaluate: (root == " << root->str << "):" << std::endl;
        int result = root->evaluate();

        return result;
    }

} // namespace sample




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

