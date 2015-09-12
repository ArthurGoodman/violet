#include "defaultparser.h"

#include "common.h"
#include "io.h"
#include "token.h"
#include "tokens.h"
#include "syntaxerror.h"
#include "listnode.h"
#include "blocknode.h"
#include "binarynode.h"
#include "unarynode.h"
#include "nullarynode.h"
#include "literalnode.h"
#include "emptynode.h"
#include "utility.h"
#include "ifnode.h"
#include "whilenode.h"
#include "fornode.h"
#include "donode.h"
#include "variablenode.h"
#include "variableassignnode.h"
#include "variabledefinitionnode.h"
#include "castnode.h"

Node *DefaultParser::parse(list<Token> tokens) {
    this->tokens = tokens;
    token = this->tokens.begin();

    return program();
}

void DefaultParser::error(string message) {
    throw new SyntaxError(message);
}

bool DefaultParser::check(int id) {
    return *token == id;
}

bool DefaultParser::accept(int id) {
    if (*token == id) {
        getToken();
        return true;
    }

    return false;
}

void DefaultParser::getToken() {
    ++token;
}

Node *DefaultParser::program() {
    list<Node *> nodes;

    while (!check(tEnd))
        nodes << statement();

    return new BlockNode(nodes);
}

Node *DefaultParser::statement() {
    Node *node = 0;

    if (accept(tIf)) {
        Node *condition = expr(), *body = statement(), *elseBody = accept(tElse) ? statement() : 0;
        node = new IfNode(condition, body, elseBody);
    } else if (accept(tWhile)) {
        Node *condition = expr(), *body = statement();
        node = new WhileNode(condition, body);
    } else if (accept(tDo)) {
        Node *body = statement();

        if (!accept(tWhile))
            error("while expected");

        Node *condition = expr();

        node = new DoNode(body, condition);
    } else if (accept(tFor)) {
        if (!accept(tLPar))
            error("left parenthesis expected");

        Node *preffix = (node = definition()) ? node : expr();

        if (!accept(tSemi))
            error("semicolon expected");

        Node *condition = expr();

        if (!accept(tSemi))
            error("semicolon expected");

        Node *suffix = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");

        node = new ForNode(preffix, condition, suffix, statement());
    } else if (accept(tLBrace)) {
        if (accept(tRBrace)) {
            node = new EmptyNode;
        } else {
            list<Node *> nodes;

            while (!check(tRBrace) && !check(tEnd))
                nodes << statement();

            if (!accept(tRBrace))
                error("unmatched braces");

            node = new BlockNode(nodes);
        }
    } else if ((node = definition())) {
        accept(tSemi);
    } //else if(accept(tFunction))
    else if (accept(tSemi))
        node = new EmptyNode;
    else
        node = oper();

    return node;
}

Node *DefaultParser::definition() {
    Node *node = 0;

    if (check(tConst) || check(tVar) || isType()) {
        bool isConst = false;

        if (accept(tConst))
            isConst = true;

        if (!check(tVar) && !isType())
            error("variable definition expected");

        Variant::Type type = toType();

        getToken();

        if (type != Variant::Undefined && !isConst && accept(tLPar)) {
            node = expr();

            if (!accept(tRPar))
                error("unmatched parentheses");

            node = new CastNode(type, node);
        } else {
            list<pair<string, Node *>> definitions;

            do {
                if (!check(tId))
                    error("identifier expected");

                string name = token->getText();
                getToken();

                if (type == Variant::Undefined && !check(tAssign))
                    error("assignment expected");

                definitions << make_pair(name, accept(tAssign) ? logicOr() : 0);
            } while (accept(tComma));

            node = new VariableDefinitionNode(type, definitions, isConst);
        }
    }

    return node;
}

Node *DefaultParser::oper() {
    Node *node = expr();

    accept(tSemi);

    return node;
}

Node *DefaultParser::expr() {
    list<Node *> nodes;

    do
        nodes << logicOr();
    while (accept(tComma));

    return nodes.size() == 1 ? nodes.front() : new ListNode(nodes);
}

Node *DefaultParser::logicOr() {
    Node *node = logicAnd();

    forever {
        if (accept(tOr))
            node = new BinaryNode(BinaryNode::Or, node, logicAnd());
        else
            break;
    }

    return node;
}

Node *DefaultParser::logicAnd() {
    Node *node = equality();

    forever {
        if (accept(tAnd))
            node = new BinaryNode(BinaryNode::And, node, equality());
        else
            break;
    }

    return node;
}

Node *DefaultParser::equality() {
    Node *node = relation();

    forever {
        if (accept(tEq))
            node = new BinaryNode(BinaryNode::Eq, node, relation());
        else if (accept(tNe))
            node = new BinaryNode(BinaryNode::Ne, node, relation());
        else
            break;
    }

    return node;
}

Node *DefaultParser::relation() {
    Node *node = addSub();

    forever {
        if (accept(tLt))
            node = new BinaryNode(BinaryNode::Lt, node, addSub());
        else if (accept(tGt))
            node = new BinaryNode(BinaryNode::Gt, node, addSub());
        else if (accept(tLe))
            node = new BinaryNode(BinaryNode::Le, node, addSub());
        else if (accept(tGe))
            node = new BinaryNode(BinaryNode::Ge, node, addSub());
        else
            break;
    }

    return node;
}

Node *DefaultParser::addSub() {
    Node *node = mulDiv();

    forever {
        if (accept(tPlus))
            node = new BinaryNode(BinaryNode::Plus, node, mulDiv());
        else if (accept(tMinus))
            node = new BinaryNode(BinaryNode::Minus, node, mulDiv());
        else
            break;
    }

    return node;
}

Node *DefaultParser::mulDiv() {
    Node *node = preffix();

    forever {
        if (accept(tMultiply))
            node = new BinaryNode(BinaryNode::Multiply, node, preffix());
        else if (accept(tDivide))
            node = new BinaryNode(BinaryNode::Divide, node, preffix());
        else if (accept(tMod))
            node = new BinaryNode(BinaryNode::Mod, node, preffix());
        else
            break;
    }

    return node;
}

Node *DefaultParser::preffix() {
    Node *node = 0;

    if (accept(tPlus))
        node = new UnaryNode(UnaryNode::Plus, suffix());
    else if (accept(tMinus))
        node = new UnaryNode(UnaryNode::Minus, suffix());
    else if (accept(tNeg))
        node = new UnaryNode(UnaryNode::Neg, suffix());
    else if (accept(tDec)) {
        node = suffix();

        if (!dynamic_cast<VariableNode *>(node))
            error("variable expected");

        node = new UnaryNode(UnaryNode::PrefDec, node);
    } else if (accept(tInc)) {
        node = suffix();

        if (!dynamic_cast<VariableNode *>(node))
            error("variable expected");

        node = new UnaryNode(UnaryNode::PrefInc, node);
    } else
        node = suffix();

    return node;
}

Node *DefaultParser::suffix() {
    Node *node = term();

    if (accept(tDec)) {
        if (!dynamic_cast<VariableNode *>(node))
            error("variable expected");

        node = new UnaryNode(UnaryNode::SuffDec, node);
    } else if (accept(tInc)) {
        if (!dynamic_cast<VariableNode *>(node))
            error("variable expected");

        node = new UnaryNode(UnaryNode::SuffInc, node);
    }

    return node;
}

Node *DefaultParser::term() {
    Node *node = 0;

    if (check(tId)) {
        string name = token->getText();
        getToken();

        if (accept(tAssign))
            node = new VariableAssignNode(name, logicOr());
        else if (accept(tPlusAssign))
            node = new VariableAssignNode(name, new BinaryNode(BinaryNode::Plus, new VariableNode(name), logicOr()));
        else if (accept(tMinusAssign))
            node = new VariableAssignNode(name, new BinaryNode(BinaryNode::Minus, new VariableNode(name), logicOr()));
        else if (accept(tMultiplyAssign))
            node = new VariableAssignNode(name, new BinaryNode(BinaryNode::Multiply, new VariableNode(name), logicOr()));
        else if (accept(tDivideAssign))
            node = new VariableAssignNode(name, new BinaryNode(BinaryNode::Divide, new VariableNode(name), logicOr()));
        else if (accept(tModAssign))
            node = new VariableAssignNode(name, new BinaryNode(BinaryNode::Mod, new VariableNode(name), logicOr()));
        else
            node = new VariableNode(name);
    }

    else if (check(tCharLiteral)) {
        node = new LiteralNode(Variant((char)token->getText().at(0)));
        getToken();
    } else if (check(tIntLiteral)) {
        node = new LiteralNode(Variant(Utility::fromString<int>(token->getText())));
        getToken();
    } else if (check(tFloatLiteral)) {
        node = new LiteralNode(Variant(Utility::fromString<float>(token->getText())));
        getToken();
    } else if (check(tDoubleLiteral)) {
        node = new LiteralNode(Variant(Utility::fromString<double>(token->getText())));
        getToken();
    }

    else if (check(tPrint) || check(tPrintln)) {
        UnaryNode::NodeType type = check(tPrint) ? UnaryNode::Print : UnaryNode::Println;

        getToken();

        bool par = false;
        if (accept(tLPar))
            par = true;

        node = new UnaryNode(type, logicOr());

        if (accept(tComma)) {
            list<Node *> nodes;
            nodes << node;

            do
                nodes << new UnaryNode(type, logicOr());
            while (accept(tComma));

            node = new ListNode(nodes);
        }

        if (par && !accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tScan)) {
        bool par = false;
        if (accept(tLPar))
            par = true;

        node = term();

        if (!dynamic_cast<VariableNode *>(node))
            error("variable expected");

        node = new UnaryNode(UnaryNode::Scan, node);

        if (accept(tComma)) {
            list<Node *> nodes;
            nodes << node;

            do {
                node = term();

                if (!dynamic_cast<VariableNode *>(node))
                    error("variable expected");

                nodes << new UnaryNode(UnaryNode::Scan, node);
            } while (accept(tComma));

            node = new ListNode(nodes);
        }

        if (par && !accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tSizeof))
        node = new UnaryNode(UnaryNode::Sizeof, expr());

    else if (accept(tBreak))
        node = new NullaryNode(NullaryNode::Break);
    else if (accept(tContinue))
        node = new NullaryNode(NullaryNode::Continue);

    else if (accept(tTrue))
        node = new LiteralNode(Variant(true));
    else if (accept(tFalse))
        node = new LiteralNode(Variant(false));

    else if (isType()) {
        Variant::Type type = toType();

        getToken();

        if (!accept(tLPar))
            error("left parenthesis expected");

        node = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");

        node = new CastNode(type, node);
    }

    else if (accept(tLPar)) {
        if (isType()) {
            Variant::Type type = toType();

            getToken();

            if (!accept(tRPar))
                error("unmatched parentheses");

            node = new CastNode(type, term());
        } else {
            node = expr();

            if (!accept(tRPar))
                error("unmatched parentheses");
        }
    }

    else if (check(tEnd))
        error("unexpected end of program");
    else
        error("unexpected token '" + token->getText() + "'");

    return node;
}

bool DefaultParser::isType() {
    return check(tBool) || check(tChar) || check(tShort) || check(tInt) || check(tLong) || check(tFloat) || check(tDouble);
}

Variant::Type DefaultParser::toType() {
    Variant::Type type = Variant::Undefined;

    switch (token->getId()) {
    case tBool:
        type = Variant::Bool;
        break;
    case tChar:
        type = Variant::Char;
        break;
    case tShort:
        type = Variant::Short;
        break;
    case tInt:
        type = Variant::Int;
        break;
    case tLong:
        type = Variant::Long;
        break;
    case tFloat:
        type = Variant::Float;
        break;
    case tDouble:
        type = Variant::Double;
        break;
    }

    return type;
}
