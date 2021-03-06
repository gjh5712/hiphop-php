/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/eval/debugger/cmd/cmd_complete.h"
#include "hphp/runtime/eval/debugger/cmd/cmd_info.h"

namespace HPHP { namespace Eval {
///////////////////////////////////////////////////////////////////////////////

TRACE_SET_MOD(debugger);

void CmdComplete::sendImpl(DebuggerThriftBuffer &thrift) {
  DebuggerCommand::sendImpl(thrift);
}

void CmdComplete::recvImpl(DebuggerThriftBuffer &thrift) {
  DebuggerCommand::recvImpl(thrift);
}

void CmdComplete::list(DebuggerClient *client) {
}

bool CmdComplete::help(DebuggerClient *client) {
  client->helpTitle("Copmplete");
  client->help("complete <cmd>");
  client->helpBody(
    "This command provides the same results as TAB completion does on the"
    " command line, but bypasses the complexity of interacting with the"
    " readline library. This help is primarily for use by programs that"
    " need to access completion functionality."
  );
  return true;
}

bool CmdComplete::onClientImpl(DebuggerClient *client) {
  if (DebuggerCommand::onClientImpl(client)) return true;
  std::string text = client->lineRest(1);
  std::vector<std::string> res = client->getAllCompletions(text);
  for (size_t i = 0; i < res.size(); ++i) {
    client->print(res[i].c_str());
  }
  return true;
}

bool CmdComplete::onServer(DebuggerProxy *proxy) {
  assert(false); // this command is processed entirely locally
  return false;
}

///////////////////////////////////////////////////////////////////////////////
}}
