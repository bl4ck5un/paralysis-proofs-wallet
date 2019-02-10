#ifndef PARALYSISPROOFS_WALLET_H
#define PARALYSISPROOFS_WALLET_H

#include "external/json.hpp"
#include <fstream>
#include <log4cxx/logger.h>
#include <string>
#include <vector>

#include <QList>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>

using json = nlohmann::json;
using std::string;
using std::vector;

#include <iostream>

struct User {
  string name;
  string pubkey;
};

void from_json(const json &j, User &p);

class Wallet {
  json _json_wallet;
  string _version;
  vector<User> _users;
  uint32_t _grace_period;
  string _wallet_address;
  string _fee_payment_address;

  log4cxx::LoggerPtr logger;
  QStandardItemModel *model;

public:
  Wallet() : _grace_period(144), logger(log4cxx::Logger::getLogger(__FILE__)) {
    model = new QStandardItemModel;
  }
  QStandardItemModel *get_model() const { return model; }
  void loadJSON(const string &path) {
    std::ifstream wallet_file;
    // register to throw exceptions on I/O failures
    wallet_file.exceptions(std::ifstream::badbit);
    wallet_file.open(path);

    wallet_file >> _json_wallet;

    _version = _json_wallet["version"].get<string>();
    _wallet_address = _json_wallet["wallet_address"].get<string>();
    _fee_payment_address = _json_wallet["fee_payment_address"].get<string>();
    _grace_period = _json_wallet["grace_period"].get<uint32_t>();
    _users = _json_wallet.at("users").get<vector<User>>();

    QStringList labels;
    labels << "Name"
           << "Pubkey key";
    model->setHorizontalHeaderLabels(labels);

    for (int i = 0; i < _users.size(); i++) {
      auto row = QList<QStandardItem *>();
      row << new QStandardItem(QString::fromStdString(_users[i].name))
          << new QStandardItem(QString::fromStdString(_users[i].pubkey));
      model->appendRow(row);
    }
  }

  QStringList get_user_names() const {
    QStringList sl;
    for (const auto &u : _users) {
      sl << QString::fromStdString(u.name);
    }

    return sl;
  }
  const string &get_version() const { return _version; }
  uint32_t get_grace_period() const { return _grace_period; }
  const string &get_wallet_address() const { return _wallet_address; }
  const string &get_fee_payment_address() const { return _fee_payment_address; }
};

#endif // PARALYSISPROOFS_WALLET_H
