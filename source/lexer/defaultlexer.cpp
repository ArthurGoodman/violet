#include "defaultlexer.h"

#include <algorithm>

#include "token.h"
#include "lexicalerror.h"
#include "common.h"
#include "tokens.h"
#include "utility.h"
#include "io.h"

vector<string> DefaultLexer::operators = {
#define X(a, b) b,
#include "operators.def"
#undef X
};

vector<string> DefaultLexer::keywords = {
#define X(a, b) b,
#include "keywords.def"
#undef X
};

vector<string> DefaultLexer::tokenTypes = {
#define X(a, b) #a,
#include "operators.def"
#include "keywords.def"
#include "othertokens.def"
#undef X
};

list<Token> DefaultLexer::lex(string source) {
    this->source = source;
    pos = 0;

    tokens.clear();

    do {
        scan();
        tokens << token;

        //IO::println(tokenTypes[token.getId()] + " : \"" + token.getText() + "\"");
    } while (token != tEnd);

    return tokens;
}

void DefaultLexer::error(string message) {
    throw new LexicalError(message);
}

void DefaultLexer::scan() {
    token = Token();

    skipSpaces();

    while (at(pos) == '/' && at(pos + 1) == '/') {
        while (at(pos) && at(pos) != '\n')
            pos++;

        skipSpaces();
    }

    if (!at(pos))
        token = tEnd;
    else if (at(pos) == '\'') {
        token = tCharLiteral;

        if (at(++pos) == '\\')
            switch (at(++pos)) {
            case 'n':
                token += '\n';
                break;
            case 't':
                token += '\t';
                break;
            case '\\':
                token += '\\';
                break;
            case '0':
                token += '\0';
                break;
            default:
                error("invalid escape sequence '\\" + string() + at(pos) + "'");
            }
        else
            token += at(pos);

        if (at(++pos) != '\'')
            error("invalid char literal");

        pos++;
    } else if (Utility::isDigit(at(pos))) {
        token = tIntLiteral;

        do
            token += at(pos++);
        while (Utility::isDigit(at(pos)));

        if (at(pos) == '.' && Utility::isDigit(at(pos + 1))) {
            token = tDoubleLiteral;

            do
                token += at(pos++);
            while (Utility::isDigit(at(pos)));
        }

        if ((Utility::toLower(at(pos)) == 'e') && (Utility::isDigit(at(pos + 1)) || (Utility::isSign(at(pos + 1)) && Utility::isDigit(at(pos + 2))))) {
            token = tDoubleLiteral;

            token += at(pos++);

            if ((Utility::isSign(at(pos))) && Utility::isDigit(at(pos + 1)))
                do
                    token += at(pos++);
                while (Utility::isDigit(at(pos)));
            else
                while (Utility::isDigit(at(pos)))
                    token += at(pos++);
        }

        if (token == tDoubleLiteral && at(pos) == 'f') {
            token = tFloatLiteral;
            pos++;
        }
    } else if (Utility::isLetter(at(pos))) {
        do
            token += at(pos++);
        while (Utility::isLetterOrDigit(at(pos)));

        vector<string>::iterator i;

        if ((i = find(keywords.begin(), keywords.end(), token.getText())) != keywords.end())
            token = tKeywordMarker + distance(keywords.begin(), i);
        else
            token = tId;
    } else {
        vector<string>::iterator i;

        while (i != operators.end())
            for (i = operators.begin(); i != operators.end(); ++i)
                if (i->substr(0, token.getText().size() + 1) == token.getText() + at(pos)) {
                    token += at(pos++);
                    break;
                }

        if (!token.getText().empty() && (i = find(operators.begin(), operators.end(), token.getText())) != operators.end())
            token = tOperatorMarker + distance(operators.begin(), i);
        else {
            if (token.getText().empty())
                token += at(pos++);

            error("unknown token '" + token.getText() + "'");
        }
    }
}

void DefaultLexer::skipSpaces() {
    while (Utility::isSpace(at(pos)))
        pos++;
}

const char &DefaultLexer::at(int pos) {
    return source[pos];
}
