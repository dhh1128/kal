#ifndef kaleidoscope_lexer_h
#define kaleidoscope_lexer_h

#include <stdio.h>
#include <string>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum token_type {
    tok_eof = -1,
    
    // commands
    tok_def = -2,
    tok_extern = -3,
    
    // primary
    tok_identifier = -4,
    tok_number = -5
};

/// Break a stream of text into tokens.
class lexer {
    char * text;
    char const * p;
    
    void init(char * source);
    void init(char const * source);
    
public:
    /// Used to parse a file. Most common invocation.
    lexer(FILE * source);
    /// Used to parse an arbitrary, null-terminated buffer.
    lexer(char * source);
    /// Mainly used to parse string literals in testing.
    lexer(char const * source);
    /// Used to eval() strings.
    lexer(std::string const & source);
    ~lexer();
    
    // Filled in if tok_identifier
    std::string identifier;
    // Filled in if tok_number
    double num_val;
    
    int get_next_token();
};

#endif
