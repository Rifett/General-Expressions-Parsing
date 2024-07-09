#ifndef BACHELOR_THESIS_TOKENIZER_H
#define BACHELOR_THESIS_TOKENIZER_H

#include <string>
#include <utility>
#include <sstream>

//General testing
/*enum Token {
    tok_eof,                            //   'EOF'
    tok_a,                              //   'a'
    tok_b,                              //   'b'
    tok_c,                              //   'c'
    tok_question_mark,                  //   '?'
    tok_exclamation_mark,               //   '!'
    tok_colon,                          //   ':'
    tok_semi_colon,                     //   ';'
    tok_assign,                         //   ':='
    tok_op_par,                         //   '('
    tok_cl_par,                         //   ')'
    tok_minus,                          //   '-'
    tok_plus,                           //   '+'
    tok_mult,                           //   '*'
    tok_div,                            //   '/'
    tok_eq,                             //   '='
    tok_gr,                             //   '>'
    tok_ls,                             //   '<'
    tok_gr_eq,                          //   '>='
    tok_ls_eq,                          //   '<='
    tok_not_eq,                         //   '<>'
};*/

//Pascal testing
enum Token {
    tok_eof,                    //   'EOF'
    tok_program,                //   'program'
    tok_label,                  //   'label'
    tok_const,                  //   'const'
    tok_type,                   //   'type'
    tok_var,                    //   'var'
    tok_proc,                   //   'procedure'
    tok_func,                   //   'function'
    tok_semi_colon,             //   ';'
    tok_colon,                  //   ':'
    tok_comma,                  //   ','
    tok_with,                   //   'with'
    tok_do,                     //   'do'
    tok_for,                    //   'for'
    tok_repeat,                 //   'repeat'
    tok_until,                  //   'until'
    tok_while,                  //   'while'
    tok_if,                     //   'if'
    tok_then,                   //   'then'
    tok_else,                   //   'else'
    tok_begin,                  //   'begin'
    tok_end,                    //   'end'
    tok_goto,                   //   'goto'
    tok_case,                   //   'case'
    tok_of_end,                 //   'of end'
    tok_of,                     //   'of'
    tok_assign,                 //   ':='
    tok_not_eq,                 //   '<>'
    tok_eq,                     //   '='
    tok_in,                     //   'in'
    tok_gr,                     //   '>'
    tok_ls,                     //   '<'
    tok_gr_eq,                  //   '>='
    tok_ls_eq,                  //   '<='
    tok_to,                     //   'to'
    tok_downto,                 //   'downto'
    tok_minus,                  //   '-'
    tok_plus,                   //   '+'
    tok_or,                     //   'or'
    tok_mult,                   //   '*'
    tok_div,                    //   'div' or '/'
    tok_mod,                    //   'mod'
    tok_and,                    //   'and'
    tok_packed,                 //   'packed'
    tok_arr_op_br,              //   'array ['
    tok_cl_br_of,               //   '] of'
    tok_record,                 //   'record'
    tok_set_of,                 //   'set of'
    tok_file_of,                //   'file of'
    tok_double_dot,             //   '..'
    tok_not,                    //   'not'
    tok_ptr,                    //   '^'
    tok_dot,                    //   '.'
    tok_op_par,                 //   '('
    tok_cl_par,                 //   ')'
    tok_op_br,                  //   '['
    tok_cl_br,                  //   ']'
    tok_int_num,                //   integer value
    tok_real_num,               //   real value
    tok_string,                 //   string value
    tok_id,                     //   identifier
    tok_nil,                    //   'nil'
    tok_op_cl_br                //   '[ ]'
};


class Tokenizer
{
public:
    Tokenizer() = default;

    Tokenizer( const std::string& inputString ) : inputStream( inputString ) {};

    bool tokenMatch( Token token );

    void initialize();

    bool tokenizationComplete();

private:
    Token getNextToken();

    std::istringstream inputStream;
    Token currentToken;
};


#endif //BACHELOR_THESIS_TOKENIZER_H
