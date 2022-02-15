//
// Created by james on 2/5/2022.
//

#ifndef HOMEWORK4_4_CHECKINGACCOUNT_H
#define HOMEWORK4_4_CHECKINGACCOUNT_H

#include <iosfwd>

#include "BankAccount.h"         // class BankAccount
#include "Check.h"
class Check;


class CheckingAccount : public BankAccount {
public:
    CheckingAccount(long accountNumber,
            double initialBalance,
            const std::string& firstName,
            const std::string& lastName);

    ~CheckingAccount() = default;

    double getBalance() const;

    void depositCheck(const Check&);

    void depositCash(double);

    void withdrawCash(double);

    virtual std::ostream& print(std::ostream&) const;

protected:
    void processAccount();

private:

    struct impl_strurct;
    impl_strurct * actaul_imp;
    /* will contain :
    long accountNumber_;
    double balance_;
    std::string firstName_;
    std::string lastName_;
    std::vector<double> deposits_;
    std::vector<double> withdrawals_;
    std::list<Check> checks_;
     */
};

std::ostream& operator<<(std::ostream&, const CheckingAccount&);

#endif //HOMEWORK4_4_CHECKINGACCOUNT_H
