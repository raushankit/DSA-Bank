#include "customer_atm.h"

void ATM_B(Bank &b){
    std::string AccNo = commonVerificationATM(b);
    if(AccNo=="") return;
    std::cout << "Balance: " << b.getAmount(AccNo) << std::endl;
    std::string AtmID = b.addATMlog(log("Balance Inquiry", "AccNo: "+AccNo));
    b.addAccountLog(AccNo,log("Balance Inquiry","ATMID:"+AtmID));
}

void ATM_W(Bank &b){
    std::string AccNo = commonVerificationATM(b);
    if(AccNo=="") return;
    std::cout << "Amount must have less than or equal to 2 decimal digits" << std::endl;
    std::cout << "How much would you like to withdraw? ";
    double amount;
    std::cin >> amount;
    if(!checkAmount(amount)){
        std::cout << "Withdrawal failed\nTry Again" << std::endl;
        return;
    }
    double d = b.getAmount(AccNo);
    if(d<amount){
        std::cout << "You do not have sufficient funds." << std::endl;
        return;
    }
    std::string AtmID = b.addATMlog(log("Withdrawal of "+std::to_string(amount),"AccNo: "+AccNo));
    b.updateAmount(AccNo, d-amount);
    std::cout << "Withdrawn: " << amount << std::endl;
    std::cout << "Balance: " << d-amount << std::endl;
    b.addAccountLog(AccNo,log("Withdrawn "+std::to_string(amount),"ATMID:"+AtmID));
}

void ATM_M(Bank &b){
    std::string AccNo = commonVerificationATM(b);
    if(AccNo=="") return;
    std::cout << "Mini Statement..........." << std::endl;
    std::string AtmID = b.addATMlog(log("Mini Statement Print","AccNo: "+AccNo));
    b.getMIniStatement(AccNo);
    b.addAccountLog(AccNo,log("Mini statement Printed","ATMID:"+AtmID));
}

void ATM_F(Bank &b){
    std::string AccNo = commonVerificationATM(b);
    if(AccNo=="") return;
    std::cout << "Please Enter the reciever's Account Number: ";
    std::string AccSend;
    std::cin >> AccSend;
    if(!b.getAccStatus(AccSend)){
        std::cout << "No Account Exists with this Account Number. " << std::endl;
        std::cout << "Fund Transfer failed\nTry Again!" << std::endl;
        return;
    }
    if(AccNo==AccSend){
        std::cout << "you are trying to send money to yourself. " << std::endl;
        return;
    }
    std::cout << "Amount must have less than or equal to 2 decimal digits" << std::endl;
    std::cout << "How much would you like to send? ";
    double amount;
    std::cin >> amount;
    if(!checkAmount(amount)){
        std::cout << "Fund Transfer failed\nTry Again" << std::endl;
        return;
    }
    double d = b.getAmount(AccNo);
    if(d<amount){
        std::cout << "You do not have sufficient funds." << std::endl;
        return;
    }
    std::string AtmID = b.addATMlog(log("Fund Transfer of "+std::to_string(amount)+" to AccNo: "+AccSend,"AccNo: "+AccNo));
    b.updateAmount(AccNo,d-amount);
    b.updateAmount(AccSend,b.getAmount(AccSend)+amount);
    std::cout << "sent " << amount << " to " << b.getAccountName(AccSend) << std::endl;
    b.addAccountLog(AccNo,log(std::to_string(amount)+" Transfered to: "+b.getAccountName(AccSend),"ATMID:"+AtmID));
    b.addAccountLog(AccSend,log(std::to_string(amount)+" Received from: "+b.getAccountName(AccNo),"ATMID:"+AtmID));
}

void ATM_X(Bank &b){
    std::string AccNo = commonVerificationATM(b);
    if(AccNo=="") return;
    std::cout << "Enter your new ATM PIN: ";
    std::string pin;
    std::cin >> pin;
    if(!checkPIN(pin)){
        std::cout << "Invalid PIN" << std::endl;
        return;
    }
    b.setATMstatus(AccNo,false,pin);
}
