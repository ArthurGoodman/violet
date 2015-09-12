TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH = source \
    source/exception \
    source/ast \
    source/ast/nodes \
    source/common \
    source/common/definitions \
    source/compiler \
    source/lexer \
    source/parser \
    source/runtime \
    source/variant \
    source/virtualmachine

HEADERS += \
    source/engine.h \
    source/ast/node.h \
    source/common/common.h \
    source/common/io.h \
    source/common/token.h \
    source/common/utility.h \
    source/compiler/program.h \
    source/ast/nodes/ifnode.h \
    source/ast/nodes/whilenode.h \
    source/ast/nodes/fornode.h \
    source/ast/nodes/donode.h \
    source/ast/nodes/literalnode.h \
    source/runtime/runtime.h \
    source/ast/nodes/binarynode.h \
    source/common/definitions/tokens.h \
    source/exception/exception.h \
    source/exception/errorexception.h \
    source/exception/lexicalerror.h \
    source/exception/syntaxerror.h \
    source/exception/runtimeerror.h \
    source/ast/nodes/unarynode.h \
    source/ast/nodes/variablenode.h \
    source/ast/nodes/nullarynode.h \
    source/variant/boolvariant.h \
    source/variant/doublevariant.h \
    source/variant/floatvariant.h \
    source/variant/intvariant.h \
    source/variant/longvariant.h \
    source/variant/shortvariant.h \
    source/variant/variant.h \
    source/variant/voidvariant.h \
    source/variant/variantprivate.h \
    source/variant/charvariant.h \
    source/ast/nodes/blocknode.h \
    source/ast/nodes/listnode.h \
    source/ast/nodes/emptynode.h \
    source/ast/nodes/variableassignnode.h \
    source/ast/nodes/variabledefinitionnode.h \
    source/exception/breakexception.h \
    source/exception/continueexception.h \
    source/ast/nodes/castnode.h \
    source/compiler/compiler.h \
    source/virtualmachine/virtualmachine.h \
    source/ast/runtimecontext.h \
    source/ast/compilercontext.h \
    source/common/definitions/instructions.h \
    source/common/vector.h \
    source/exception/compilationerror.h \
    source/variant/typevariant.h \
    source/ast/nodes/functiondefinitionnode.h \
    source/runtime/function.h \
    source/runtime/interpretedfunction.h \
    source/runtime/compiledfunction.h \
    source/ast/nodes/functioncallnode.h \
    source/parser/iparser.h \
    source/parser/parser.h \
    source/lexer/ilexer.h \
    source/lexer/lexer.h \
    source/ast/icontext.h

SOURCES += \
    source/engine.cpp \
    source/main.cpp \
    source/ast/node.cpp \
    source/common/common.cpp \
    source/common/io.cpp \
    source/common/token.cpp \
    source/common/utility.cpp \
    source/compiler/program.cpp \
    source/ast/nodes/ifnode.cpp \
    source/ast/nodes/whilenode.cpp \
    source/ast/nodes/fornode.cpp \
    source/ast/nodes/donode.cpp \
    source/ast/nodes/literalnode.cpp \
    source/runtime/runtime.cpp \
    source/ast/nodes/binarynode.cpp \
    source/exception/exception.cpp \
    source/exception/errorexception.cpp \
    source/exception/lexicalerror.cpp \
    source/exception/syntaxerror.cpp \
    source/exception/runtimeerror.cpp \
    source/ast/nodes/unarynode.cpp \
    source/ast/nodes/variablenode.cpp \
    source/ast/nodes/nullarynode.cpp \
    source/variant/doublevariant.cpp \
    source/variant/floatvariant.cpp \
    source/variant/intvariant.cpp \
    source/variant/longvariant.cpp \
    source/variant/shortvariant.cpp \
    source/variant/variant.cpp \
    source/variant/voidvariant.cpp \
    source/variant/variantprivate.cpp \
    source/variant/boolvariant.cpp \
    source/variant/charvariant.cpp \
    source/ast/nodes/blocknode.cpp \
    source/ast/nodes/listnode.cpp \
    source/ast/nodes/emptynode.cpp \
    source/ast/nodes/variableassignnode.cpp \
    source/ast/nodes/variabledefinitionnode.cpp \
    source/exception/breakexception.cpp \
    source/exception/continueexception.cpp \
    source/ast/nodes/castnode.cpp \
    source/compiler/compiler.cpp \
    source/virtualmachine/virtualmachine.cpp \
    source/ast/runtimecontext.cpp \
    source/ast/compilercontext.cpp \
    source/common/vector.cpp \
    source/exception/compilationerror.cpp \
    source/variant/typevariant.cpp \
    source/ast/nodes/functiondefinitionnode.cpp \
    source/runtime/function.cpp \
    source/runtime/interpretedfunction.cpp \
    source/runtime/compiledfunction.cpp \
    source/ast/nodes/functioncallnode.cpp \
    source/parser/iparser.cpp \
    source/parser/parser.cpp \
    source/lexer/ilexer.cpp \
    source/lexer/lexer.cpp \
    source/ast/icontext.cpp

OTHER_FILES  += \
    scripts/test.vi \
    source/common/definitions/keywords.def \
    source/common/definitions/operators.def \
    source/common/definitions/othertokens.def \
    source/common/definitions/instructions.def

DISTFILES += \
    scripts/euclid.vi \
    scripts/simple.vi \
    scripts/factorial.vi
