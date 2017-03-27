
// Generated from resources/textworld.g4 by ANTLR 4.6


#include "textworldListener.h"
#include "textworldVisitor.h"

#include "textworldParser.h"


using namespace antlrcpp;
using namespace antlr4;

textworldParser::textworldParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

textworldParser::~textworldParser() {
  delete _interpreter;
}

std::string textworldParser::getGrammarFileName() const {
  return "textworld.g4";
}

const std::vector<std::string>& textworldParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& textworldParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- WorldContext ------------------------------------------------------------------

textworldParser::WorldContext::WorldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<textworldParser::AreaContext *> textworldParser::WorldContext::area() {
  return getRuleContexts<textworldParser::AreaContext>();
}

textworldParser::AreaContext* textworldParser::WorldContext::area(size_t i) {
  return getRuleContext<textworldParser::AreaContext>(i);
}

std::vector<textworldParser::ActionContext *> textworldParser::WorldContext::action() {
  return getRuleContexts<textworldParser::ActionContext>();
}

textworldParser::ActionContext* textworldParser::WorldContext::action(size_t i) {
  return getRuleContext<textworldParser::ActionContext>(i);
}

std::vector<textworldParser::ItemContext *> textworldParser::WorldContext::item() {
  return getRuleContexts<textworldParser::ItemContext>();
}

textworldParser::ItemContext* textworldParser::WorldContext::item(size_t i) {
  return getRuleContext<textworldParser::ItemContext>(i);
}


size_t textworldParser::WorldContext::getRuleIndex() const {
  return textworldParser::RuleWorld;
}

void textworldParser::WorldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWorld(this);
}

void textworldParser::WorldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWorld(this);
}


antlrcpp::Any textworldParser::WorldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitWorld(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::WorldContext* textworldParser::world() {
  WorldContext *_localctx = _tracker.createInstance<WorldContext>(_ctx, getState());
  enterRule(_localctx, 0, textworldParser::RuleWorld);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << textworldParser::AREA)
      | (1ULL << textworldParser::ITEM)
      | (1ULL << textworldParser::ACTION))) != 0)) {
      setState(15);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case textworldParser::AREA: {
          setState(12);
          area();
          break;
        }

        case textworldParser::ACTION: {
          setState(13);
          action();
          break;
        }

        case textworldParser::ITEM: {
          setState(14);
          item();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(19);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ItemContext ------------------------------------------------------------------

textworldParser::ItemContext::ItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* textworldParser::ItemContext::ITEM() {
  return getToken(textworldParser::ITEM, 0);
}

tree::TerminalNode* textworldParser::ItemContext::ID() {
  return getToken(textworldParser::ID, 0);
}

tree::TerminalNode* textworldParser::ItemContext::LCB() {
  return getToken(textworldParser::LCB, 0);
}

tree::TerminalNode* textworldParser::ItemContext::RCB() {
  return getToken(textworldParser::RCB, 0);
}

std::vector<textworldParser::AssignmentContext *> textworldParser::ItemContext::assignment() {
  return getRuleContexts<textworldParser::AssignmentContext>();
}

textworldParser::AssignmentContext* textworldParser::ItemContext::assignment(size_t i) {
  return getRuleContext<textworldParser::AssignmentContext>(i);
}


size_t textworldParser::ItemContext::getRuleIndex() const {
  return textworldParser::RuleItem;
}

void textworldParser::ItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItem(this);
}

void textworldParser::ItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItem(this);
}


antlrcpp::Any textworldParser::ItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitItem(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::ItemContext* textworldParser::item() {
  ItemContext *_localctx = _tracker.createInstance<ItemContext>(_ctx, getState());
  enterRule(_localctx, 2, textworldParser::RuleItem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(textworldParser::ITEM);
    setState(21);
    match(textworldParser::ID);
    setState(22);
    match(textworldParser::LCB);
    setState(26);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == textworldParser::ID) {
      setState(23);
      assignment();
      setState(28);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(29);
    match(textworldParser::RCB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AreaContext ------------------------------------------------------------------

textworldParser::AreaContext::AreaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* textworldParser::AreaContext::AREA() {
  return getToken(textworldParser::AREA, 0);
}

tree::TerminalNode* textworldParser::AreaContext::ID() {
  return getToken(textworldParser::ID, 0);
}

tree::TerminalNode* textworldParser::AreaContext::LCB() {
  return getToken(textworldParser::LCB, 0);
}

tree::TerminalNode* textworldParser::AreaContext::RCB() {
  return getToken(textworldParser::RCB, 0);
}

std::vector<textworldParser::AssignmentContext *> textworldParser::AreaContext::assignment() {
  return getRuleContexts<textworldParser::AssignmentContext>();
}

textworldParser::AssignmentContext* textworldParser::AreaContext::assignment(size_t i) {
  return getRuleContext<textworldParser::AssignmentContext>(i);
}


size_t textworldParser::AreaContext::getRuleIndex() const {
  return textworldParser::RuleArea;
}

void textworldParser::AreaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArea(this);
}

void textworldParser::AreaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArea(this);
}


antlrcpp::Any textworldParser::AreaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitArea(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::AreaContext* textworldParser::area() {
  AreaContext *_localctx = _tracker.createInstance<AreaContext>(_ctx, getState());
  enterRule(_localctx, 4, textworldParser::RuleArea);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
    match(textworldParser::AREA);
    setState(32);
    match(textworldParser::ID);
    setState(33);
    match(textworldParser::LCB);
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == textworldParser::ID) {
      setState(34);
      assignment();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
    match(textworldParser::RCB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionContext ------------------------------------------------------------------

textworldParser::ActionContext::ActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* textworldParser::ActionContext::ACTION() {
  return getToken(textworldParser::ACTION, 0);
}

tree::TerminalNode* textworldParser::ActionContext::ID() {
  return getToken(textworldParser::ID, 0);
}

tree::TerminalNode* textworldParser::ActionContext::LCB() {
  return getToken(textworldParser::LCB, 0);
}

tree::TerminalNode* textworldParser::ActionContext::RCB() {
  return getToken(textworldParser::RCB, 0);
}

std::vector<textworldParser::AssignmentContext *> textworldParser::ActionContext::assignment() {
  return getRuleContexts<textworldParser::AssignmentContext>();
}

textworldParser::AssignmentContext* textworldParser::ActionContext::assignment(size_t i) {
  return getRuleContext<textworldParser::AssignmentContext>(i);
}


size_t textworldParser::ActionContext::getRuleIndex() const {
  return textworldParser::RuleAction;
}

void textworldParser::ActionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAction(this);
}

void textworldParser::ActionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAction(this);
}


antlrcpp::Any textworldParser::ActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitAction(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::ActionContext* textworldParser::action() {
  ActionContext *_localctx = _tracker.createInstance<ActionContext>(_ctx, getState());
  enterRule(_localctx, 6, textworldParser::RuleAction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    match(textworldParser::ACTION);
    setState(43);
    match(textworldParser::ID);
    setState(44);
    match(textworldParser::LCB);
    setState(48);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == textworldParser::ID) {
      setState(45);
      assignment();
      setState(50);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(51);
    match(textworldParser::RCB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

textworldParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* textworldParser::AssignmentContext::ID() {
  return getToken(textworldParser::ID, 0);
}

tree::TerminalNode* textworldParser::AssignmentContext::EQ() {
  return getToken(textworldParser::EQ, 0);
}

textworldParser::ValueContext* textworldParser::AssignmentContext::value() {
  return getRuleContext<textworldParser::ValueContext>(0);
}

tree::TerminalNode* textworldParser::AssignmentContext::SC() {
  return getToken(textworldParser::SC, 0);
}


size_t textworldParser::AssignmentContext::getRuleIndex() const {
  return textworldParser::RuleAssignment;
}

void textworldParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void textworldParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


antlrcpp::Any textworldParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::AssignmentContext* textworldParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 8, textworldParser::RuleAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    match(textworldParser::ID);
    setState(54);
    match(textworldParser::EQ);
    setState(55);
    value();
    setState(56);
    match(textworldParser::SC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

textworldParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* textworldParser::ValueContext::STRING() {
  return getToken(textworldParser::STRING, 0);
}

tree::TerminalNode* textworldParser::ValueContext::INT() {
  return getToken(textworldParser::INT, 0);
}

tree::TerminalNode* textworldParser::ValueContext::LIST() {
  return getToken(textworldParser::LIST, 0);
}


size_t textworldParser::ValueContext::getRuleIndex() const {
  return textworldParser::RuleValue;
}

void textworldParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void textworldParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<textworldListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


antlrcpp::Any textworldParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<textworldVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

textworldParser::ValueContext* textworldParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 10, textworldParser::RuleValue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << textworldParser::STRING)
      | (1ULL << textworldParser::INT)
      | (1ULL << textworldParser::LIST))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> textworldParser::_decisionToDFA;
atn::PredictionContextCache textworldParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN textworldParser::_atn;
std::vector<uint16_t> textworldParser::_serializedATN;

std::vector<std::string> textworldParser::_ruleNames = {
  "world", "item", "area", "action", "assignment", "value"
};

std::vector<std::string> textworldParser::_literalNames = {
  "", "'area'", "'item'", "'action'", "'{'", "'}'", "'='", "';'"
};

std::vector<std::string> textworldParser::_symbolicNames = {
  "", "AREA", "ITEM", "ACTION", "LCB", "RCB", "EQ", "SC", "ID", "STRING", 
  "INT", "LIST", "WS", "COMMENT"
};

dfa::Vocabulary textworldParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> textworldParser::_tokenNames;

textworldParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0xf, 0x3f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x12, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 
    0x15, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x1b, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1e, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x26, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0x29, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x7, 0x5, 0x31, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x34, 0xb, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x2, 0x2, 0x8, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0x2, 0x3, 0x3, 0x2, 0xb, 0xd, 0x3e, 0x2, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x16, 0x3, 0x2, 0x2, 0x2, 0x6, 0x21, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x2c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x37, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3c, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x12, 0x5, 0x6, 0x4, 0x2, 0xf, 0x12, 0x5, 0x8, 
    0x5, 0x2, 0x10, 0x12, 0x5, 0x4, 0x3, 0x2, 0x11, 0xe, 0x3, 0x2, 0x2, 
    0x2, 0x11, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x10, 0x3, 0x2, 0x2, 0x2, 
    0x12, 0x15, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 0x2, 0x2, 0x13, 
    0x14, 0x3, 0x2, 0x2, 0x2, 0x14, 0x3, 0x3, 0x2, 0x2, 0x2, 0x15, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x7, 0x4, 0x2, 0x2, 0x17, 0x18, 0x7, 
    0xa, 0x2, 0x2, 0x18, 0x1c, 0x7, 0x6, 0x2, 0x2, 0x19, 0x1b, 0x5, 0xa, 
    0x6, 0x2, 0x1a, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1e, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x1d, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1f, 
    0x20, 0x7, 0x7, 0x2, 0x2, 0x20, 0x5, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 
    0x7, 0x3, 0x2, 0x2, 0x22, 0x23, 0x7, 0xa, 0x2, 0x2, 0x23, 0x27, 0x7, 
    0x6, 0x2, 0x2, 0x24, 0x26, 0x5, 0xa, 0x6, 0x2, 0x25, 0x24, 0x3, 0x2, 
    0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 0x3, 0x2, 0x2, 
    0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x7, 0x2, 0x2, 0x2b, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x5, 0x2, 0x2, 0x2d, 0x2e, 
    0x7, 0xa, 0x2, 0x2, 0x2e, 0x32, 0x7, 0x6, 0x2, 0x2, 0x2f, 0x31, 0x5, 
    0xa, 0x6, 0x2, 0x30, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0x33, 0x35, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 
    0x35, 0x36, 0x7, 0x7, 0x2, 0x2, 0x36, 0x9, 0x3, 0x2, 0x2, 0x2, 0x37, 
    0x38, 0x7, 0xa, 0x2, 0x2, 0x38, 0x39, 0x7, 0x8, 0x2, 0x2, 0x39, 0x3a, 
    0x5, 0xc, 0x7, 0x2, 0x3a, 0x3b, 0x7, 0x9, 0x2, 0x2, 0x3b, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x3c, 0x3d, 0x9, 0x2, 0x2, 0x2, 0x3d, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0x7, 0x11, 0x13, 0x1c, 0x27, 0x32, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

textworldParser::Initializer textworldParser::_init;
