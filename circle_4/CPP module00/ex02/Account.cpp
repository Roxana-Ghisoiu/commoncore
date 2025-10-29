/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:28:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 12:06:52 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

// Init static variable
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/**
 * @brief Displays the current timestamp in the format [YYYYMMDD_HHMMSS]
 */
void Account::_displayTimestamp() {
    std::time_t now = std::time(NULL);
    std::tm *ltm = std::localtime(&now);

    std::cout << "["
              << 1900 + ltm->tm_year
              << (ltm->tm_mon < 9 ? "0" : "") << 1 + ltm->tm_mon
              << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << "_"
              << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour
              << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min
              << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec
              << "] ";
}

/**
 * @brief Constructs a new Account object with an initial deposit
 * @param initial_deposit The amount to initialize the account with
 */
Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
    _nbAccounts++;
    _totalAmount += initial_deposit;
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";created" << std::endl;
}

/**
 * @brief Destructor for the Account object
 */
Account::~Account() {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";closed" << std::endl;
}

/**
 * @brief Makes a deposit into the account
 * @param deposit The amount to deposit
 */
void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << _amount
              << ";deposit:" << deposit;
    _amount += deposit;
    _nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;
    std::cout << ";amount:" << _amount
              << ";nb_deposits:" << _nbDeposits
              << std::endl;
}

/**
 * @brief Attempts to withdraw an amount from the account
 * @param withdrawal The amount to withdraw
 * @return true if successful, false if insufficient funds
 */
bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";p_amount:" << _amount
              << ";withdrawal:";
    if (withdrawal > _amount) {
        std::cout << "refused" << std::endl;
        return false;
    }
    _amount -= withdrawal;
    _nbWithdrawals++;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;
    std::cout << withdrawal
              << ";amount:" << _amount
              << ";nb_withdrawals:" << _nbWithdrawals
              << std::endl;
    return true;
}

/**
 * @brief Displays the current status of the account
 */
void Account::displayStatus() const {
    _displayTimestamp();
    std::cout << "index:" << _accountIndex
              << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals
              << std::endl;
}

/**
 * @brief Displays the aggregated information for all accounts
 */
void Account::displayAccountsInfos() {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts
              << ";total:" << _totalAmount
              << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals
              << std::endl;
}

/**
 * @brief Gets the total number of accounts
 * @return int Number of accounts
 */
int Account::getNbAccounts() {
    return _nbAccounts;
}

/**
 * @brief Gets the total amount across all accounts
 * @return int Total amount
 */
int Account::getTotalAmount() {
    return _totalAmount;
}

/**
 * @brief Gets the total number of deposits made
 * @return int Number of deposits
 */
int Account::getNbDeposits() {
    return _totalNbDeposits;
}

/**
 * @brief Gets the total number of withdrawals made
 * @return int Number of withdrawals
 */
int Account::getNbWithdrawals() {
    return _totalNbWithdrawals;
}