/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/http/blob/main/LICENSE.txt
*/

#include "HTTPSClient.hpp"
#undef min
#include <botan/auto_rng.h>
#include <botan/certstor_system.h>
#include <botan/tls_callbacks.h>
#include <botan/tls_client.h>
#include <botan/tls_policy.h>
#include <botan/tls_session_manager.h>

using namespace Ishiko;

namespace
{

class Callbacks : public Botan::TLS::Callbacks
{
public:
    void tls_emit_data(const uint8_t data[], size_t size) override
    {
        // send data to tls server, e.g., using BSD sockets or boost asio
    }

    void tls_record_received(uint64_t seq_no, const uint8_t data[], size_t size) override
    {
        // process full TLS record received by tls server, e.g.,
        // by passing it to the application
    }

    void tls_alert(Botan::TLS::Alert alert) override
    {
        // handle a tls alert received from the tls server
    }

    bool tls_session_established(const Botan::TLS::Session& session) override
    {
        // the session with the tls server was established
        // return false to prevent the session from being cached, true to
        // cache the session in the configured session manager
        return false;
    }
};

class Client_Credentials : public Botan::Credentials_Manager
{
public:
    Client_Credentials()
    {
        // Here we base trust on the system managed trusted CA list
        m_stores.push_back(new Botan::System_Certificate_Store);
    }

    std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(
        const std::string& type,
        const std::string& context) override
    {
        // return a list of certificates of CAs we trust for tls server certificates
        // ownership of the pointers remains with Credentials_Manager
        return m_stores;
    }

    std::vector<Botan::X509_Certificate> cert_chain(
        const std::vector<std::string>& cert_key_types,
        const std::string& type,
        const std::string& context) override
    {
        // when using tls client authentication (optional), return
        // a certificate chain being sent to the tls server,
        // else an empty list
        return std::vector<Botan::X509_Certificate>();
    }

    Botan::Private_Key* private_key_for(const Botan::X509_Certificate& cert,
        const std::string& type,
        const std::string& context) override
    {
        // when returning a chain in cert_chain(), return the private key
        // associated with the leaf certificate here
        return nullptr;
    }

private:
    std::vector<Botan::Certificate_Store*> m_stores;
};

}

void HTTPSClient::Get(IPv4Address address, Port port, const std::string& uri, HTTPResponse& response, Error& error)
{
    Callbacks callbacks;
    Botan::AutoSeeded_RNG rng;
    Botan::TLS::Session_Manager_In_Memory session_mgr(rng);
    Client_Credentials creds;
    Botan::TLS::Strict_Policy policy;
    Botan::TLS::Client client(callbacks, session_mgr, creds, policy, rng,
        Botan::TLS::Server_Information("needfulsoftware.com", 443),
        Botan::TLS::Protocol_Version::TLS_V12);
}
