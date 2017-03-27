
// Generated from resources/textworld.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "textworldParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by textworldParser.
 */
class  textworldVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by textworldParser.
   */
    virtual antlrcpp::Any visitWorld(textworldParser::WorldContext *context) = 0;

    virtual antlrcpp::Any visitItem(textworldParser::ItemContext *context) = 0;

    virtual antlrcpp::Any visitArea(textworldParser::AreaContext *context) = 0;

    virtual antlrcpp::Any visitAction(textworldParser::ActionContext *context) = 0;

    virtual antlrcpp::Any visitAssignment(textworldParser::AssignmentContext *context) = 0;

    virtual antlrcpp::Any visitValue(textworldParser::ValueContext *context) = 0;


};

