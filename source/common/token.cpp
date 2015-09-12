#include "token.h"

Token::Token() {
}

Token::Token(int id, string text)
    : id(id), text(text) {
}

int Token::getId() {
    return id;
}

string Token::getText() {
    return text;
}

bool Token::operator==(int id) {
    return this->id == id;
}

bool Token::operator!=(int id) {
    return this->id != id;
}

Token &Token::operator=(int id) {
    this->id = id;
    return *this;
}

Token &Token::operator=(string text) {
    this->text = text;
    return *this;
}

Token &Token::operator+=(string text) {
    this->text += text;
    return *this;
}

Token &Token::operator+=(char c) {
    this->text += c;
    return *this;
}
