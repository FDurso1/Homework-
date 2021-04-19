#include <iostream>
#include <sstream>

#include "CTrie.h"

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] +=
    2;  // skip the seg fault
}

#define ASSERT(cond) \
do { \
  if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" \
       << " passed!" << endl; \
  } \
} while (0)
#endif

struct CTrieTest {
  static void DefaultConstructorTest() {
    CTrie q = CTrie();
    ASSERT(q.numChildren() == 0);
    ASSERT(!q.hasChild());
    ASSERT(q.isEndpoint() == false);
  }

  static void AddAssignOperatorTest() {
    CTrie q = CTrie();
    ASSERT(!q.hasChild('h'));
    q += "h";
    ASSERT(q.hasChild('h'));

    const CTrie *hChild = q.getChild('h');
    ASSERT(hChild != nullptr);
    ASSERT(!hChild->hasChild('i'));
    q += "hi";
    ASSERT(hChild->hasChild('i'));
  }

  static void CopyConstructorTest() {
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";
    //    cout << "     cp 0, copy constructor p(q). q has hello, hell, help, johns, joanna, and johnson. p has nothing" << endl;
    CTrie p(q);
    // cout << "     cp 1, copy constructor now done" << endl;
    ASSERT((p == q));
    // cout << "double equals operator works" << endl;
    p += "jelly";
    ASSERT(!(p == q));
  }

  static void AssignmentOperatorTest() {
    CTrie q = CTrie();
    q += "hello";
 
    CTrie r = CTrie();
    r += "rice";
    r += "beans";

    ASSERT(q ^ "hello");
    ASSERT(!(q ^ "rice"));
    ASSERT(!(q ^ "beans"));
    ASSERT(!(r ^ "hello"));
    // cout << "     cp 0.5" << endl;
    ASSERT(r ^ "rice");
    ASSERT(r ^ "beans");
    // cout << "     cp 1 q=r, r has rice and beans. q has hello." << endl;
    q = r;
    cout << "     cp 2" << endl;
    ASSERT(!(q ^ "hello"));
    ASSERT(q ^ "rice");
    ASSERT(q ^ "beans");
    ASSERT(!(r ^ "hello"));
    ASSERT(r ^ "rice");
    ASSERT(r ^ "beans");
    // cout << "     cp 3, Assignment Operator Tests complete" << endl;
  }

  static void CaratOperatorTest() {
    cout << "        cp 4, start Carat Test" << endl;
    CTrie q = CTrie();
    q += "hello";
    ASSERT(q ^ "hello");
    ASSERT(!(q ^ "h"));
    q += "h";
    ASSERT((q ^ "h"));
    
    ASSERT(!(q ^ "hell"));
    q += "hell";
    ASSERT((q ^ "hell"));
    cout << "     cp 5, end carat test" << endl;
  }

  static void ChainingTest() {
    cout << "                            " << endl;
    cout << "     cp 6, start chaining test" << endl;
    CTrie q = CTrie();
    (q += "hello") += "help";
    ASSERT(q ^ "hello");
    ASSERT(q ^ "help");
    cout << "        Chaining error here hello, help. q: " << q << endl; 
    ASSERT(!(q ^ "hell"));
    cout << "     cp 7, end chaining test" << endl;
  }

  static void EqualityOperatorTest() {
    cout << "     cp 8, start equality operator test" << endl;
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";
    cout << "     cp 8.1, q finished +='ing" << endl;

    CTrie p = CTrie();
    p += "joanna";
    p += "johnson";
    p += "help";
    p += "johns";
    p += "hell";
    p += "hello";
    cout << "     cp 8.2, p finished +='ing with the same words in a different order, about to assert ==" << endl;
    cout << "q: " << q << endl;
    cout << "p: " << p << endl;
    ASSERT((p == q));
    cout << "     cp 8.3, == did not crash" << endl;
    p += "howdy";
    ASSERT(!(p == q));
    cout << "      cp 9, end equality operator test" << endl;
  }

  static void OutputStreamOperatorTest() {
    cout << "     cp 10 start output stream" << endl;
    CTrie q = CTrie();
    q += "hello";
    q += "hell";
    q += "help";
    q += "johns";
    q += "joanna";
    q += "johnson";

    std::stringstream ss;
    cout << "     cp 11, right before << tested, should be hello, hell, help, johns, joanna, johnson" << endl;
    ss << q;
    cout << "     cp 12, << did not crash" << endl;
    ASSERT(ss.str() == "hell\nhello\nhelp\njoanna\njohns\njohnson\n");
    cout << "     cp 13, end output stream" << endl;
  }
};

int main(int, char* argv[]) {
  cout << "Testing CTrie" << endl;
  // register a seg fault hanlder
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);

  CTrieTest::DefaultConstructorTest();
  CTrieTest::AddAssignOperatorTest();
  CTrieTest::CopyConstructorTest();
  CTrieTest::AssignmentOperatorTest();
  CTrieTest::CaratOperatorTest();
  CTrieTest::ChainingTest();
  CTrieTest::EqualityOperatorTest();
  CTrieTest::OutputStreamOperatorTest();
}
