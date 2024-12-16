#include "uri.hpp"
#include <stdio.h>
#include <inttypes.h>
struct magno::uri::Impl {
//        std::string /path_delimiter = "/";
    std::string scheme;
    std::string host;
    bool has_port = false;
    uint16_t port = 0;
    std::vector<std::string> path;
};

magno::uri::uri() : impl_(new Impl) {}

bool magno::uri::parse_from_string(const std::string &uriString) {
    // parse scheme.
    const auto scheme_end = uriString.find(':');
    std::string rest;
    if (scheme_end == std::string::npos) {
        impl_->scheme.clear();
        rest = uriString;
    } else {
        impl_->scheme = uriString.substr(0, scheme_end);
        rest = uriString.substr(scheme_end + 1);
    }


    impl_->has_port = false;

    // parse host.
    if (rest.substr(0, 2) == "//") {
        auto authority_end = rest.find('/', 2);

        if (authority_end == std::string::npos) {
            authority_end = rest.length();
        }

        const auto port_delimiter = rest.find(":");
        if (port_delimiter == std::string::npos) {
            impl_->host = rest.substr(2, authority_end - 2);
        }else{
            impl_->host = rest.substr(2, port_delimiter - 2);
            uint32_t newPort = 0;
            for (auto c : rest.substr(port_delimiter + 1, authority_end - port_delimiter - 1)) {
                if (c < '0' || c > '9') {
                    return false;
                }
                newPort *= 10;
                newPort += (uint16_t)(c - '0');
                if ( (newPort & ~((1 << 16) - 1)) != 0 ){
                    return false;
                }
            }
            impl_->port = (uint16_t)(newPort);
            impl_->has_port = true;

//            if (sscanf(rest.substr(port_delimiter + 1, authority_end - port_delimiter - 1).c_str(),
//                         "%" SCNu16, &impl_->port) != 1) {
//                return false;
//            }
        }
        rest = rest.substr(authority_end);
    }else{
        impl_->host.clear();
    }

    // parse path.
    impl_->path.clear();
    if (rest == "/") {
       impl_->path.push_back("");
    } else  if (!rest.empty()) {
        for (;;) {
            auto path_delimiter = rest.find('/');
            if (path_delimiter == std::string::npos) {
                impl_->path.push_back(rest);
                break;
            }else{
                impl_->path.emplace_back(
                                rest.begin(),
                                rest.begin() + path_delimiter
                            );
                rest = rest.substr(path_delimiter + /*impl_->path_delimiter.length()*/1);
            }
        }
    }

    return true;
}

std::string magno::uri::get_scheme() const {
    return impl_->scheme;
}

std::string magno::uri::get_host() const {
    return impl_->host;
}

std::vector<std::string> magno::uri::get_path() const {
    return impl_->path;
}

bool magno::uri::has_port() const {
    return impl_->has_port;
}

uint16_t magno::uri::get_port() const {
    return impl_->port;
}

bool magno::uri::is_relative_reference() const {
    return impl_->scheme.empty();
}

bool magno::uri::is_contains_relative_path() const {
    if (impl_->path.empty()) {
        return true;
    }else{
        return !impl_->path[0].empty();
    }
}

//void magno::uri::set_path_delimiter(const std::string &newPathDelimiter)
//{
//    impl_->path_delimiter = newPathDelimiter;
//}

magno::uri::~uri() = default;
