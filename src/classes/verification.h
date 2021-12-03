#ifndef _VERIFICATION_
#define _VERIFICATION_
#include "bank.h"
#include "syntax.h"

std::string commonVerificationAccount(Bank);

std::string commonVerificationATM(Bank &);

bool ManagerVerification(Bank);

#endif