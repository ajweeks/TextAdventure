
// Generated from resources/textworld.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "textworldParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by textworldParser.
 */
class  textworldListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterWorld(textworldParser::WorldContext *ctx) = 0;
  virtual void exitWorld(textworldParser::WorldContext *ctx) = 0;

  virtual void enterItem(textworldParser::ItemContext *ctx) = 0;
  virtual void exitItem(textworldParser::ItemContext *ctx) = 0;

  virtual void enterArea(textworldParser::AreaContext *ctx) = 0;
  virtual void exitArea(textworldParser::AreaContext *ctx) = 0;

  virtual void enterAction(textworldParser::ActionContext *ctx) = 0;
  virtual void exitAction(textworldParser::ActionContext *ctx) = 0;

  virtual void enterPlayer(textworldParser::PlayerContext *ctx) = 0;
  virtual void exitPlayer(textworldParser::PlayerContext *ctx) = 0;

  virtual void enterAssignment(textworldParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(textworldParser::AssignmentContext *ctx) = 0;

  virtual void enterValue(textworldParser::ValueContext *ctx) = 0;
  virtual void exitValue(textworldParser::ValueContext *ctx) = 0;


};

