﻿#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../task5/ParseURL.h"

using namespace std;

Protocol protocol;
int port;
string host;
string document;

SCENARIO("ParseURL valid url with protocol http gives protocol http")
{
    string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::HTTP);
}

SCENARIO("ParseURL valid url with protocol http in different case gives protocol http")
{
    string url = "hTTp://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::HTTP);
}

SCENARIO("ParseURL valid url with protocol https gives protocol https")
{
    string url = "https://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::HTTPS);
}

SCENARIO("ParseURL valid url with protocol https in different case gives protocol https")
{
    string url = "htTPs://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::HTTPS);
}

SCENARIO("ParseURL valid url with protocol ftp gives protocol ftp")
{
    string url = "ftp://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::FTP);
}

SCENARIO("ParseURL valid url with protocol ftp in different case gives protocol ftp")
{
    string url = "fTP://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(protocol == Protocol::FTP);
}

SCENARIO("ParseURL invalid url with invalid protocol 'unknown' gives false")
{
    string url = "unknown://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}

SCENARIO("ParseURL valid url with host \"www.mysite.com\" gives host \"www.mysite.com\"")
{
    string url = "ftp://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(host == "www.mysite.com");
}

SCENARIO("ParseURL invalid url empty host gives false")
{
    string url = "ftp:///docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}

SCENARIO("ParseURL with protocol http and without port gives default port for http")
{
	string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
	REQUIRE(isValidUrl);
	REQUIRE(port == 80);
}

SCENARIO("ParseURL with protocol https and without port gives default port for https")
{
    string url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 443);
}

SCENARIO("ParseURL with protocol ftp and without port gives default port for ftp")
{
    string url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 21);
}

SCENARIO("ParseURL with protocol http and port 8000 gives port 8000")
{
    string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 8000);
}

SCENARIO("ParseURL with valid port 1 gives valid URL")
{
    string url = "http://www.mysite.com:1/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 1);
}
SCENARIO("ParseURL with valid port 65535 gives valid URL")
{
    string url = "http://www.mysite.com:65535/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 65535);
}
SCENARIO("ParseURL with invalid port 65536 gives invalid URL")
{
    string url = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}
SCENARIO("ParseURL with invalid port 0 gives invalid URL")
{
    string url = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}
SCENARIO("ParseURL valid url with document gives right document")
{
    string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("ParseURL valid url without document gives empty document")
{
    string url = "http://www.mysite.com/";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(document.empty());
}

SCENARIO("Parse valid url with 1-symbol host and port")
{
    string url = "http://w:1234/";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(isValidUrl);
    REQUIRE(port == 1234);
    REQUIRE(host == "w");
    REQUIRE(document.empty());
}

SCENARIO("Parse invalid url with invalid port with two separator \":\"")
{
    string url = "http://w:1234:9/";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}

SCENARIO("Parse invalid url with invalid port with character")
{
    string url = "http://w:123e/";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}

SCENARIO("Parse invalid url with double :: port")
{
    string url = "http://www::123/";
    bool isValidUrl = ParseURL(url, protocol, port, host, document);
    REQUIRE(!isValidUrl);
}