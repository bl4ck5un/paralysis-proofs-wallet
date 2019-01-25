/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_EXCH_RPC_ABSSERVER_H_
#define JSONRPC_CPP_STUB_EXCH_RPC_ABSSERVER_H_

#include <jsonrpccpp/server.h>

namespace exch {
namespace rpc {
class AbsServer : public jsonrpc::AbstractServer<AbsServer> {
public:
  AbsServer(jsonrpc::AbstractServerConnector &conn,
            jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2)
      : jsonrpc::AbstractServer<AbsServer>(conn, type) {
    this->bindAndAddMethod(jsonrpc::Procedure("appendBlock2FIFO",
                                              jsonrpc::PARAMS_BY_POSITION,
                                              jsonrpc::JSON_BOOLEAN, "param1",
                                              jsonrpc::JSON_STRING, NULL),
                           &exch::rpc::AbsServer::appendBlock2FIFOI);
    this->bindAndAddMethod(jsonrpc::Procedure("deposit",
                                              jsonrpc::PARAMS_BY_POSITION,
                                              jsonrpc::JSON_BOOLEAN, "param1",
                                              jsonrpc::JSON_OBJECT, "param2",
                                              jsonrpc::JSON_STRING, NULL),
                           &exch::rpc::AbsServer::depositI);
    this->bindAndAddMethod(jsonrpc::Procedure("distributeSettlementPkg",
                                              jsonrpc::PARAMS_BY_POSITION,
                                              jsonrpc::JSON_BOOLEAN, "param1",
                                              jsonrpc::JSON_STRING, NULL),
                           &exch::rpc::AbsServer::distributeSettlementPkgI);
    this->bindAndAddMethod(jsonrpc::Procedure("ackSettlementPkg",
                                              jsonrpc::PARAMS_BY_POSITION,
                                              jsonrpc::JSON_BOOLEAN, "param1",
                                              jsonrpc::JSON_STRING, NULL),
                           &exch::rpc::AbsServer::ackSettlementPkgI);
  }

  inline virtual void appendBlock2FIFOI(const Json::Value &request,
                                        Json::Value &response) {
    response = this->appendBlock2FIFO(request[0u].asString());
  }
  inline virtual void depositI(const Json::Value &request,
                               Json::Value &response) {
    response = this->deposit(request[0u], request[1u].asString());
  }
  inline virtual void distributeSettlementPkgI(const Json::Value &request,
                                               Json::Value &response) {
    response = this->distributeSettlementPkg(request[0u].asString());
  }
  inline virtual void ackSettlementPkgI(const Json::Value &request,
                                        Json::Value &response) {
    response = this->ackSettlementPkg(request[0u].asString());
  }
  virtual bool appendBlock2FIFO(const std::string &param1) = 0;
  virtual bool deposit(const Json::Value &param1,
                       const std::string &param2) = 0;
  virtual bool distributeSettlementPkg(const std::string &param1) = 0;
  virtual bool ackSettlementPkg(const std::string &param1) = 0;
};

} // namespace rpc
} // namespace exch
#endif // JSONRPC_CPP_STUB_EXCH_RPC_ABSSERVER_H_
