#include "Tokenizer.h"


bool Tokenizer::tokenMatch(Token token) {
    if ( currentToken == token ) {
        getNextToken();
        return true;
    }
    return false;
}

void Tokenizer::initialize() {
    this -> getNextToken();
}

bool Tokenizer::tokenizationComplete() {
    return currentToken == tok_eof;
}

//General testing
/*Token Tokenizer::getNextToken() {
    int input = inputStream . get();

    //Get rid of spaces
    while ( isspace( input ) )
        input = inputStream . get();

    //Input symbol is character -> a, b or c
    if ( isalpha( input ) )
    {
        switch ( input ) {
            case 'a':
                return currentToken = tok_a;
            case 'b':
                return currentToken = tok_b;
            case 'c':
                return currentToken = tok_c;
            default:
                throw std::runtime_error("Invalid input.");
        }
    }

    //Semicolon case
    if (input == ';')
        return currentToken = tok_semi_colon;

    //Parentheses cases
    if (input == '(')
        return currentToken = tok_op_par;
    if (input == ')')
        return currentToken = tok_cl_par;

    //Plus, minus, divide and multiply cases
    if (input == '+')
        return currentToken = tok_plus;
    if (input == '-')
        return currentToken = tok_minus;
    if (input == '*')
        return currentToken = tok_mult;
    if (input == '/')
        return currentToken = tok_div;

    //Question mark case
    if (input == '?')
        return currentToken = tok_question_mark;

    //Exclamation mark case
    if (input == '!')
        return currentToken = tok_exclamation_mark;

    //Equality case
    if (input == '=')
        return currentToken = tok_eq;

    //Colon cases -> colon or assignment
    if (input == ':')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_assign;

        inputStream . unget();
        return currentToken = tok_colon;
    }

    //Comparison cases
    if (input == '>')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_gr_eq;

        inputStream . unget();
        return currentToken = tok_gr;
    }

    if (input == '<')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_ls_eq;

        if (next == '>')
            return currentToken = tok_not_eq;

        inputStream . unget();
        return currentToken = tok_ls;
    }

    if ( inputStream . eof() || input == EOF )
        return currentToken = tok_eof;

    throw std::runtime_error("Invalid input.");
}*/

//Pascal testing
Token Tokenizer::getNextToken() {
    int input = inputStream . get();

    //Get rid of spaces
    while ( isspace( input ) )
        input = inputStream . get();

    //Input symbol is character -> identifier or a keyword
    if ( isalpha( input ) )
    {
        std::string str;
        str = input;

        while ( isalnum( input = inputStream . get() ) || input == '_')
            str . push_back( input );

        inputStream . unget();

        if (str == "program")
            return currentToken = tok_program;
        else if ( str == "label" )
            return currentToken = tok_label;
        else if (str == "var")
            return currentToken = tok_var;
        else if (str == "array") {
            auto streamPosition = inputStream . tellg();
            Token nextToken = this -> getNextToken();
            if ( nextToken == tok_op_br )
                return currentToken = tok_arr_op_br;
            inputStream . seekg( streamPosition );
            throw std::runtime_error("Invalid input.");
        }
        else if (str == "of") {
            auto streamPosition = inputStream . tellg();
            Token nextToken = this -> getNextToken();
            if ( nextToken == tok_end )
                return currentToken = tok_of_end;
            inputStream . seekg( streamPosition );
            return currentToken = tok_of;
        }
        else if (str == "begin")
            return currentToken = tok_begin;
        else if (str == "for")
            return currentToken = tok_for;
        else if (str == "to")
            return currentToken = tok_to;
        else if (str == "do")
            return currentToken = tok_do;
        else if (str == "end")
            return currentToken = tok_end;
        else if (str == "if")
            return currentToken = tok_if;
        else if (str == "then")
            return currentToken = tok_then;
        else if (str == "downto")
            return currentToken = tok_downto;
        else if (str == "div")
            return currentToken = tok_div;
        else if (str == "const")
            return currentToken = tok_const;
        else if (str == "mod")
            return currentToken = tok_mod;
        else if (str == "function")
            return currentToken = tok_func;
        else if (str == "while")
            return currentToken = tok_while;
        else if (str == "else")
            return currentToken = tok_else;
        else if (str == "procedure")
            return currentToken = tok_proc;
        else if (str == "and")
            return currentToken = tok_and;
        else if (str == "or")
            return currentToken = tok_or;
        else if (str == "not")
            return currentToken = tok_not;
        else if ( str == "type" )
            return currentToken = tok_type;
        else if ( str == "with" )
            return currentToken = tok_with;
        else if ( str == "repeat" )
            return currentToken = tok_repeat;
        else if ( str == "until" )
            return currentToken = tok_until;
        else if ( str == "goto" )
            return currentToken = tok_goto;
        else if ( str == "case" )
            return currentToken = tok_case;
        else if ( str == "in" )
            return currentToken = tok_in;
        else if ( str == "packed" )
            return currentToken = tok_packed;
        else if ( str == "record" )
            return currentToken = tok_record;
        else if ( str == "set" ) {
            auto streamPosition = inputStream . tellg();
            Token nextToken = this -> getNextToken();
            if ( nextToken == tok_of )
                return currentToken = tok_set_of;
            inputStream . seekg( streamPosition );
            throw std::runtime_error("Invalid input.");
        }
        else if ( str == "file" ) {
            auto streamPosition = inputStream . tellg();
            Token nextToken = this -> getNextToken();
            if ( nextToken == tok_of )
                return currentToken = tok_file_of;
            inputStream . seekg( streamPosition );
            throw std::runtime_error("Invalid input.");
        }
        else if ( str == "nil" )
            return currentToken = tok_nil;
        else
            return currentToken = tok_id;
    }

    //Input symbol is a number -> we have a numeric value -> either int or real
    if ( isdigit( input ) )
    {
        std::string numStr;
        bool hasDot = false, hasExponent = false;
        while ( isdigit( input ) || ( !hasDot && input == '.' ) || ( !hasExponent && ( input == 'e' || input == 'E' ) ) ) {
            if ( input == '.' ) {
                if ( hasDot ) break;
                hasDot = true;
            }
            if ( input == 'e' || input == 'E' ) {
                if ( hasExponent )
                    throw std::runtime_error("Double exponent sign in the real number.");
                hasExponent = true;
                numStr . push_back( input );
                input = inputStream . get();
                if ( input == '+' || input == '-' ) {
                    numStr . push_back( input );
                    input = inputStream . get();
                }
                continue;
            }
            numStr . push_back( input );
            input = inputStream . get();
        }

        inputStream . unget();

        return currentToken = ( hasDot || hasExponent ) ? tok_real_num : tok_int_num;
    }

    //String case
    if ( input == '\'' ) {
        std::string str;
        while ( ( input = inputStream . get() ) != '\'' && input != EOF )
            str . push_back( input );

        if ( input != '\'' )
            throw std::runtime_error("Unterminated string literal");

        return currentToken = tok_string;
    }

    //Comma case
    if (input == ',')
        return currentToken = tok_comma;

    //Brackets cases
    if (input == '[') {
        auto streamPosition = inputStream . tellg();
        Token nextToken = this -> getNextToken();
        if ( nextToken == tok_cl_br )
            return currentToken = tok_op_cl_br;
        inputStream . seekg( streamPosition );
        return currentToken = tok_op_br;
    }
    if (input == ']') {
        auto streamPosition = inputStream . tellg();
        Token nextToken = this -> getNextToken();
        if ( nextToken == tok_of )
            return currentToken = tok_cl_br_of;
        inputStream . seekg( streamPosition );
        return currentToken = tok_cl_br;
    }

    //Semicolon case
    if (input == ';')
        return currentToken = tok_semi_colon;

    //Pointer case
    if ( input == '^' )
        return currentToken = tok_ptr;

    //Parentheses cases
    if (input == '(')
        return currentToken = tok_op_par;
    if (input == ')')
        return currentToken = tok_cl_par;

    //Plus, minus and multiply cases
    if (input == '+')
        return currentToken = tok_plus;
    if (input == '-')
        return currentToken = tok_minus;
    if (input == '*')
        return currentToken = tok_mult;
    if ( input == '/' )
        return currentToken = tok_div;

    //Equality case
    if (input == '=')
        return currentToken = tok_eq;

    //Colon cases -> colon or assignment
    if (input == ':')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_assign;

        inputStream . unget();
        return currentToken = tok_colon;
    }

    //Dot cases -> dot or double dot (interval)
    if (input == '.')
    {
        int next = inputStream . get();

        if (next == '.')
            return currentToken = tok_double_dot;

        inputStream . unget();
        return currentToken = tok_dot;
    }

    //Comparison cases
    if (input == '>')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_gr_eq;

        inputStream . unget();
        return currentToken = tok_gr;
    }

    if (input == '<')
    {
        int next = inputStream . get();

        if (next == '=')
            return currentToken = tok_ls_eq;

        if (next == '>')
            return currentToken = tok_not_eq;

        inputStream . unget();
        return currentToken = tok_ls;
    }

    if ( inputStream . eof() || input == EOF )
        return currentToken = tok_eof;

    throw std::runtime_error("Invalid input.");
}