#include "global.h"
#include "helper.h"
#include "smart_contract.h"
#include "smart_contract_txn.h"

#if DYNAMIC_ACCESS_SMART_CONTRACT

uint64_t NewCiphertextSmartContract::execute() {
    printf("Executing NewCiphertextSmartContact\n");
    return 0;
}

/*
Smartt Contract Transaction Manager and Workload
*/

void SmartContractTxn::init(uint64_t thd_id, Workload *h_wl)
{
    printf("INITIALIZING DYNAMIC ACCESS SMART CONTRACT INIT\n");
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
    this->smart_contract->execute();
    return RCOK;
};

RC SCWorkload::init()
{
    printf("INITIALIZING DYNAMIC ACCESS SMART CONTRACT WORKLOAD\n");
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

uint64_t SmartContract::execute()
{
    printf("Executing dynamic access smart contract\n");
    int result = 0;
    switch (this->type)
    {
    case DASC_NEW:
    {
        printf("Type: DASC_NEWE\n");
        NewCiphertextSmartContract *nc = (NewCiphertextSmartContract *)this;
        result = nc->execute();
        break;
    }
    default:
        printf("ERROR: Couldn't find type\n");
        assert(0);
        break;
    }

    if (result)
        return RCOK;
    else
        return NONE;
}

#endif