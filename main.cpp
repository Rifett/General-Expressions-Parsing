#include <iostream>
#include <cassert>
#include "ParsedStorage/ParsedStorage.h"
#include "TableParser/TableParser.h"

//General testing
/*void ParsedStorageTests() {
    ParsedStorage storage;


    //Initial state assertions
    assert( storage . reparsed() == true );
    assert( storage . isPacked() == false );
    assert( storage . empty() == true );
    assert( !storage . match( tok_minus ) );
    assert( !storage . matchSubstorage() );


    storage
    .pushBack(ParsedStorage().pushBack(tok_a))
    .pushBack(tok_plus)
    .pushBack(ParsedStorage().pushBack(tok_a));


    //Content matching
    storage.resetPosition();
    assert( storage . matchSubstorage() && storage . match( tok_plus ) && storage . matchSubstorage() && storage . reparsed() );


    bool exceptionAppeared = false;


    //Attempt to break the format ( two subsequent storages push )
    try {
        storage . pushBack( ParsedStorage().pushBack(tok_a) );
    } catch (const std::runtime_error& e) {
        exceptionAppeared = true;
    }
    assert( exceptionAppeared );
    exceptionAppeared = false;


    //Content matching after the attempt to break the format ( no changes must be done )
    storage.resetPosition();
    assert( storage . matchSubstorage() && storage . match( tok_plus ) && storage . matchSubstorage() && storage . reparsed() );


    //Token mismatch inside a storage
    storage . resetPosition();
    assert( storage . matchSubstorage() && !storage . match( tok_minus ) );
    assert( storage . match( tok_plus ) && storage . matchSubstorage() && storage . reparsed() );


    //Substorage mismatch
    storage . resetPosition();
    assert( storage . matchSubstorage() && !storage . matchSubstorage() );
    assert( storage . match( tok_plus ) && storage . matchSubstorage() && storage . reparsed() );


    auto storageCopy = storage;


    //Packing and unpacking
    storage . pack();
    assert( storage . isPacked() );
    assert( storage . getPackedStorage() == storageCopy );


    //Safety check for the case of memory address copying
    storageCopy . pushBack( tok_exclamation_mark );
    assert( storage . getPackedStorage() != storageCopy );


    //Validation before the attempt to break the format
    storageCopy . resetPosition();
    assert( storageCopy . matchSubstorage() && storageCopy . match( tok_plus ) && storageCopy . matchSubstorage()
            && storageCopy . match( tok_exclamation_mark ) && storageCopy . reparsed() );


    //Attempt to break the format ( two subsequent tokens push )
    try {
        storageCopy . pushBack( tok_question_mark );
    } catch (const std::runtime_error& e) {
        exceptionAppeared = true;
    }
    assert( exceptionAppeared );


    //Validation after the attempt to break the format ( no changes must be done )
    storageCopy . resetPosition();
    assert( storageCopy . matchSubstorage() && storageCopy . match( tok_plus ) && storageCopy . matchSubstorage()
    && storageCopy . match( tok_exclamation_mark ) && storageCopy . reparsed() );
}

void generalExpressionsParserTests() {

    TableParser parser(
            ParsingLayers()
            .addLayer(
                    ParsingLayer( RIGHT )
                    .addOperator( AtomicParsingOp( {tok_question_mark, tok_colon},              true, true ) )
                    .addOperator( AtomicParsingOp( { tok_question_mark, tok_exclamation_mark }, true, true) )
            )
            .addLayer(
                    ParsingLayer( RIGHT )
                    .addOperator( AtomicParsingOp( { tok_not_eq, tok_gr_eq },                   false, false ) )
                    .addOperator( AtomicParsingOp( { tok_not_eq },                              false, true ) )
            )
            .addLayer(
                    ParsingLayer( LEFT )
                    .addOperator( AtomicParsingOp( { tok_div },                                 false, true ) )
                    .addOperator( AtomicParsingOp( { tok_div, tok_eq },                       false, false ) )
            )
            .addLayer(
                    ParsingLayer( RIGHT )
                    .addOperator( AtomicParsingOp( { tok_question_mark, tok_gr },               false, true ) )
                    .addOperator( AtomicParsingOp( { tok_assign },                              true, true ) )
            )
            .addLayer(
                    ParsingLayer( LEFT )
                    .addOperator( AtomicParsingOp( { tok_plus },                                true, true ) )
                    .addOperator( AtomicParsingOp( { tok_minus },                               true, true ) )
            )
            .addLayer(
                    ParsingLayer( LEFT )
                    .addOperator( AtomicParsingOp( { tok_mult },                                true, true ) )
                    .addOperator( AtomicParsingOp( { tok_div },                                 true, true ) )
            )
            .addLayer(
                    ParsingLayer( RIGHT )
                    .addOperator( AtomicParsingOp( { tok_question_mark, tok_semi_colon },       true, true ) )
                    .addOperator( AtomicParsingOp( { tok_question_mark, tok_ls },               false, false ) )
            )
            .addLayer(
                    ParsingLayer( NONE )
                    .addOperator( AtomicParsingOp( { tok_a },                                   false, false ) )
                    .addOperator( AtomicParsingOp( { tok_b },                                   false, false ) )
                    .addOperator( AtomicParsingOp( { tok_c },                                   false, false ) )
                    .addOperator( AtomicParsingOp( { tok_op_par, tok_cl_par },                  false, false ) )
            )
    );


    auto sumAB = ParsedStorage()
            .pushBack( ParsedStorage() . pushBack( tok_a ) )
            .pushBack( tok_plus )
            .pushBack( ParsedStorage() . pushBack( tok_b ) ) . pack();


    //Basic functionality check
    assert( parser . parse( "a + b") );
    assert( parser . compareStorage( sumAB ) );


    //Left recursive rules check
    assert( parser . parse( "a + b + c") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( sumAB . getPackedStorage() )
                    .pushBack( tok_plus )
                    .pushBack( ParsedStorage() . pushBack( tok_c ) ) . pack()
            )
    );


    auto assignBC = ParsedStorage()
            .pushBack( ParsedStorage() . pushBack( tok_b ) )
            .pushBack( tok_assign )
            .pushBack( ParsedStorage() . pushBack( tok_c ) ) . pack();


    //Right recursive rules check
    assert( parser . parse( "a := b := c") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( ParsedStorage() . pushBack( tok_a ) )
                    .pushBack( tok_assign )
                    .pushBack( assignBC . getPackedStorage() ) . pack()
    )
    );


    //Layers combination check
    assert( parser . parse( "a := a + b") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( ParsedStorage() . pushBack( tok_a ) )
                    .pushBack( tok_assign )
                    .pushBack( sumAB . getPackedStorage() ) . pack()
    )
    );


    //Storage coming from below check
    assert( parser . parse( "a ? b : a + b") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( ParsedStorage() . pushBack( tok_a ) )
                    .pushBack( tok_question_mark )
                    .pushBack( ParsedStorage() .pushBack( tok_b) )
                    .pushBack( tok_colon )
                    .pushBack( sumAB . getPackedStorage() ) . pack()
    )
    );


    //Storage coming from above check
    assert( parser . parse( "? a <") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( tok_question_mark )
                    .pushBack( ParsedStorage() .pushBack( tok_a) )
                    .pushBack( tok_ls ) . pack()
    )
    );


    //Storage transition on the same layer check
    assert( parser . parse( "a ? b ! a + b") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( ParsedStorage() . pushBack( tok_a ) )
                    .pushBack( tok_question_mark )
                    .pushBack( ParsedStorage() .pushBack( tok_b ) )
                    .pushBack( tok_exclamation_mark )
                    .pushBack( sumAB . getPackedStorage() ) . pack()
    )
    );

    //Rules, one of which is the prefix of another one -> short one is in the table second -> correct version check
    assert( parser . parse( "<> a >=") );
    assert( parser . compareStorage(
            ParsedStorage()
                    .pushBack( tok_not_eq )
                    .pushBack( ParsedStorage() .pushBack( tok_a ) )
                    .pushBack( tok_gr_eq ) . pack()
    )
    );

    //Rules, one of which is the prefix of another one -> short one is in the table first -> incorrect version check
    assert( !parser . parse( "/ a =") );


    bool exceptionAppeared = false;


    //Invalid input check
    try {
        parser.parse("a ? b [ a + b");
    } catch (const std::runtime_error& error) {
        exceptionAppeared = true;
    }
    assert( exceptionAppeared );


    //Invalid sentence check
    assert ( !parser.parse("a ? b : : a + b") );
    assert ( !parser.parse("a + a a") );
}*/

//Pascal testing
void PascalTableParsingTests() {
    auto parser = TableParser(
            ParsingLayers()
            .addLayer(                                          // Program header part
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_program }, false, true ) )
                    )
            .addLayer(
                    ParsingLayer( RIGHT )      // Chaining operators
                            .addOperator( AtomicParsingOp( { tok_comma }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_semi_colon }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_colon }, true, true ) )
                    )
            .addLayer(                                          // Program block
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_label }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_const }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_type }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_var }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_proc }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_func }, false, true ) )
                    )
            .addLayer(                                          // Statements
                    ParsingLayer( RIGHT )
                            .addOperator( AtomicParsingOp( { tok_with, tok_do }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_for, tok_do }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_repeat, tok_until }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_while, tok_do }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_if, tok_then, tok_else }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_if, tok_then }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_goto }, false, true ) )
                    )
            .addLayer(                                          // Not recursive statements
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_begin, tok_end }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_case, tok_of_end }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_case, tok_of, tok_end }, false, false ) )
                    )
            .addLayer(                                          // Expressions (until the end)
                    ParsingLayer( RIGHT )
                            .addOperator( AtomicParsingOp( { tok_assign }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( LEFT )
                            .addOperator( AtomicParsingOp( { tok_not_eq }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_eq }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_in }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_ls }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_gr }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_ls_eq }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_gr_eq }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_to }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_downto }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( LEFT )
                            .addOperator( AtomicParsingOp( { tok_plus }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_minus }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_or }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( LEFT )
                            .addOperator( AtomicParsingOp( { tok_mult }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_div }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_mod }, true, true ) )
                            .addOperator( AtomicParsingOp( { tok_and }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( RIGHT )
                            .addOperator( AtomicParsingOp( { tok_packed }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_arr_op_br, tok_cl_br_of }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_record, tok_end }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_set_of }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_file_of }, false, true ) )
                    )
            .addLayer(
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_double_dot }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( RIGHT )
                            .addOperator( AtomicParsingOp( { tok_minus }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_not }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_plus }, false, true ) )
                            .addOperator( AtomicParsingOp( { tok_ptr }, false, true ) )
                    )
            .addLayer(
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_ptr }, true, false ) )
                    )
            .addLayer(
                    ParsingLayer( LEFT )
                            .addOperator( AtomicParsingOp( { tok_dot }, true, true ) )
                    )
            .addLayer(
                    ParsingLayer( LEFT )
                            .addOperator( AtomicParsingOp( { tok_op_par, tok_cl_par }, true, false ) )
                            .addOperator( AtomicParsingOp( { tok_op_br, tok_cl_br }, true, false ) )
                    )
            .addLayer(
                    ParsingLayer( NONE )
                            .addOperator( AtomicParsingOp( { tok_int_num }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_real_num }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_id }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_op_par, tok_cl_par }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_string }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_nil }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_op_cl_br }, false, false ) )
                            .addOperator( AtomicParsingOp( { tok_op_br, tok_cl_br }, false, false ) )
                    )
            );

    // Hello world test
    assert( parser.parse("program HelloWorld;\n"
                               "begin\n"
                               "  writeln('Hello, world!')\n"
                               "end")
    );

    // Simple arithmetic test
    assert( parser.parse("program SimpleArithmetic;\n"
                               "var\n"
                               "  a, b, sum: integer;\n"
                               "begin\n"
                               "  a := 10;\n"
                               "  b := 20;\n"
                               "  sum := a + b;\n"
                               "  writeln('Sum of ', a, ' and ', b, ' is ', sum)\n"
                               "end")
    );

    // Function test
    assert( parser.parse("program UsingFunction;\n"
                               "var\n"
                               "  a, b, result: integer;\n"
                               "\n"
                               "function Add(x, y: integer): integer;\n"
                               "begin\n"
                               "  Add := x + y\n"
                               "end;\n"
                               "\n"
                               "begin\n"
                               "  a := 5;\n"
                               "  b := 15;\n"
                               "  result := Add(a, b);\n"
                               "  writeln('The result of addition is ', result)\n"
                               "end")
    );

    // Procedure test
    assert( parser.parse("program UsingProcedure;\n"
                               "var\n"
                               "  x: integer;\n"
                               "\n"
                               "procedure PrintSquare(n: integer);\n"
                               "begin\n"
                               "  writeln('Square of ', n, ' is ', n * n)\n"
                               "end;\n"
                               "\n"
                               "begin\n"
                               "  x := 7;\n"
                               "  PrintSquare(x)\n"
                               "end")
    );

    // For loop test
    assert( parser.parse("program ForLoopExample;\n"
                               "var\n"
                               "  i: integer;\n"
                               "begin\n"
                               "  for i := 1 to 10 do\n"
                               "  begin\n"
                               "    writeln('i = ', i)\n"
                               "  end\n"
                               "end")
    );

    // While loop test
    assert( parser.parse("program WhileLoopExample;\n"
                               "var\n"
                               "  i: integer;\n"
                               "begin\n"
                               "  i := 1;\n"
                               "  while i <= 5 do\n"
                               "  begin\n"
                               "    writeln('i = ', i);\n"
                               "    i := i + 1\n"
                               "  end\n"
                               "end")
    );

    // Dangling else test (with else)
    assert( parser.parse("program ConditionalExample;\n"
                               "var\n"
                               "  a, b: integer;\n"
                               "begin\n"
                               "  a := 15;\n"
                               "  b := 20;\n"
                               "  if a > b then\n"
                               "    writeln('a is greater than b')\n"
                               "  else\n"
                               "    writeln('a is not greater than b')\n"
                               "end")
    );

    // Dangling else test (without else)
    assert( parser.parse("program ConditionalExample;\n"
                               "var\n"
                               "  a, b: integer;\n"
                               "begin\n"
                               "  a := 15;\n"
                               "  b := 20;\n"
                               "  if a > b then\n"
                               "    writeln('a is greater than b')\n"
                               "end")
    );

    // Case statement test
    assert( parser.parse("program CaseStatementExample;\n"
                               "var\n"
                               "  grade: char;\n"
                               "begin\n"
                               "  grade := 'B';\n"
                               "  case grade of\n"
                               "    'A': writeln('Excellent');\n"
                               "    'B': writeln('Good');\n"
                               "    'C': writeln('Fair');\n"
                               "    'D': writeln('Poor');\n"
                               "    'F': writeln('Fail')\n"
                               "  end\n"
                               "end")
    );

    // Array test
    assert( parser.parse("program ArrayExample;\n"
                               "var\n"
                               "  numbers: array[1..5] of integer;\n"
                               "  i: integer;\n"
                               "begin\n"
                               "  numbers[1] := 10;\n"
                               "  numbers[2] := 20;\n"
                               "  numbers[3] := 30;\n"
                               "  numbers[4] := 40;\n"
                               "  numbers[5] := 50;\n"
                               "  \n"
                               "  for i := 1 to 5 do\n"
                               "  begin\n"
                               "    writeln('numbers[', i, '] = ', numbers[i])\n"
                               "  end\n"
                               "end")
    );

    // Record test
    assert( parser.parse("program RecordExample;\n"
                               "type\n"
                               "  Person = record\n"
                               "    name: string[50];\n"
                               "    age: integer\n"
                               "  end;\n"
                               "\n"
                               "var\n"
                               "  p: Person;\n"
                               "\n"
                               "begin\n"
                               "  p.name := 'John Doe';\n"
                               "  p.age := 30;\n"
                               "  writeln('Name: ', p.name);\n"
                               "  writeln('Age: ', p.age)\n"
                               "end")
    );

    // Token mismatch test
    assert( !parser.parse("ABOBA HelloWorld;\n"
                         "begin\n"
                         "  writeln('Hello, world!')\n"
                         "end")
    );

    // Another token mismatch test
    assert( !parser.parse("program HelloWorld;\n"
                         "not begin\n"
                         "  writeln('Hello, world!')\n"
                         "end")
    );

    // Imperfection test (this should not be possible, but it is because of the way general expressions work -> to fix
    // this behaviour some expression type checking must be implemented)
    assert( parser.parse("program ImperfectionTest;\n"
                         "begin\n"
                         "  program HelloWorld;\n"
                         "  begin\n"
                         "      writeln('Hello, world!')\n"
                         "  end\n"
                         "end")
    );

    // Dangling else test ( nested if case )
    assert( parser.parse("program ConditionalExample;\n"
                         "begin\n"
                         "  if a > b then\n"
                         "    if a = b then\n"
                         "          a\n"
                         "        else\n"
                         "           b\n"
                         "end")
    );
}

int main() {
    //General testing
    //ParsedStorageTests();
    //generalExpressionsParserTests();

    //Pascal testing
    PascalTableParsingTests();
    return 0;
}
