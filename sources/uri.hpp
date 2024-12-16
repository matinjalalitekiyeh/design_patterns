#ifndef URI_HPP
#define URI_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace magno {

class uri {

public:
    uri();
    ~uri();
    uri(const uri&) = delete;
    uri& operator=(const uri&) = delete ;
    uri(const uri&&) = delete ;
    uri& operator=(const uri&&) = delete ;

    bool parse_from_string(const std::string& uriString);

    std::string get_scheme() const;

    std::string get_host() const;

    std::vector<std::string> get_path() const;

//    void set_path_delimiter(const std::string& newPathDelimiter);

    bool has_port() const;

    uint16_t get_port() const;

    bool is_relative_reference() const;

    bool is_contains_relative_path() const;

private:
    struct Impl;
    Impl* impl_;

};



}

#endif /* URI_HPP */
