#include <cstdint>
#include "global.h"
#include "helper.h"
#include "smart_contract.h"
#include "smart_contract_txn.h"

#if DYNAMIC_ACCESS_SMART_CONTRACT

string NewCiphertextSmartContract::execute() {
    db->Put(public_key + "_ciphertext", cipher_text_hex);
    db->Put(public_key + "_capsule", capsule_hex);

    cout << "Executing NewCiphertextSmartContact ciphertext: " << cipher_text_hex;

    return "successful upload for " + public_key;
}

string RetrieveCiphertextSmartContract::execute() {
    string ciphertext = db->Get(alice_public_key + "_ciphertext");
    string capsule = db->Get(alice_public_key + "_capsule");

    cout << "Executing RetrieveCiphertextSmartContract ciphertext: " << ciphertext << endl;

    return "capsule: " + capsule + ", ciphertext: " + ciphertext;
}

/*
Smartt Contract Transaction Manager and Workload
*/

void SmartContractTxn::init(uint64_t thd_id, Workload *h_wl)
{
//    printf("INITIALIZING DYNAMIC ACCESS SMART CONTRACT INIT\n");
    TxnManager::init(thd_id, h_wl);
    _wl = (SCWorkload *)h_wl;
    reset();
}

void SmartContractTxn::reset()
{
    TxnManager::reset();
}

RC SmartContractTxn::run_txn()
{
#if DYNAMIC_ACCESS_SMART_CONTRACT
    this->result_message = this->smart_contract->execute();
    return RCOK;
#else
    this->smart_contract->execute();
    return RCOK;
#endif
};

RC SCWorkload::init()
{
//    printf("INITIALIZING DYNAMIC ACCESS SMART CONTRACT WORKLOAD\n");
    Workload::init();
    return RCOK;
}

RC SCWorkload::get_txn_man(TxnManager *&txn_manager)
{
    DEBUG_M("YCSBWorkload::get_txn_man YCSBTxnManager alloc\n");
    txn_manager = (SmartContractTxn *)
                      mem_allocator.align_alloc(sizeof(SmartContractTxn));
    new (txn_manager) SmartContractTxn();
    return RCOK;
}

string SmartContract::execute()
{
//    printf("Executing dynamic access smart contract\n");
    string result;
    switch (this->type)
    {
    case DASC_UPLOAD_CIPHERTEXT: {
        NewCiphertextSmartContract *nc = (NewCiphertextSmartContract *) this;
        result = nc->execute();
        break;
    }
    case DASC_REQUEST_CIPHERTEXT: {
        RetrieveCiphertextSmartContract
            *rc = (RetrieveCiphertextSmartContract *) this;
        result = rc->execute();
        break;
    }
    default:
//        printf("ERROR: Couldn't find type\n");
        assert(0);
        break;
    }

    if (result != "fail")
        return result;
    else
        return "fail";
}

#endif