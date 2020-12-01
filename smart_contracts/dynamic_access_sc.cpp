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
    int result = 0;
    switch (this->type)
    {
    case BSC_TRANSFER:
    {
//        printf("Type: BSC_TRANSFER\n");
        TransferMoneySmartContract *tm = (TransferMoneySmartContract *)this;
        result = tm->execute();
        break;
    }
    case BSC_DEPOSIT:
    {
//        printf("Type: BSC_DEPOSIT\n");
        DepositMoneySmartContract *dm = (DepositMoneySmartContract *)this;
        result = dm->execute();
        break;
    }
    case BSC_WITHDRAW:
    {
//        printf("Type: BSC_WITHDRAW\n");
        WithdrawMoneySmartContract *wm = (WithdrawMoneySmartContract *)this;
        result = wm->execute();
        break;
    }
    default:
        assert(0);
        break;
    }

    if (result)
        return RCOK;
    else
        return NONE;
}

#endif