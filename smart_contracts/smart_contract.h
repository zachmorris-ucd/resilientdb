#ifndef _SC_H_
#define _SC_H_
#include "global.h"
#include "helper.h"
#include "wl.h"

#if DYNAMIC_ACCESS_SMART_CONTRACT

class SmartContract
{
public:
  string execute();
  DASCType type;
};

class NewCiphertextSmartContract : public SmartContract
{
 public:
//  uint64_t source_id;
  std::string public_key;
  std::string cipher_text_hex;
  std::string capsule_hex;
  string execute();
};

class RetrieveCiphertextSmartContract : public SmartContract
{
 public:
//  uint64_t source_id;
  std::string alice_public_key;
  std::string your_public_key;
  string execute();
};


#endif

#if BANKING_SMART_CONTRACT

class SmartContract
{
public:
    uint64_t execute();
    BSCType type;
};

/*
Transfer money form source account to the destination account
Transaction will abort in case that the source account doesn't have enough money
*/
class TransferMoneySmartContract : public SmartContract
{
public:
    uint64_t source_id;
    uint64_t dest_id;
    uint64_t amount;
    uint64_t execute();
};

/*
Deposit $amount$ money to the destination account
Transaction will always commit 
*/
class DepositMoneySmartContract : public SmartContract
{
public:
    uint64_t dest_id;
    uint64_t amount;
    uint64_t execute();
};

/*
Withdraw $amount$ money form source account 
Transaction will abort in case that the source account doesn't have enough money
*/
class WithdrawMoneySmartContract : public SmartContract
{
public:
    uint64_t source_id;
    uint64_t amount;
    uint64_t execute();
};

#endif
#endif
