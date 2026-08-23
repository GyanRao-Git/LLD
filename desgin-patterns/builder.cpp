#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;

/*
    Builder pattern used to create objects that can have many params

    if some are optional then then you do not want a huge constructor

    Example:
        Pizza("large", true, false, true, "thin", "extra cheese");

    Interview Example: Http request

*/

class HttpRequest {
private:
    // has some methods, dont care abt it
    std::string url;
    std::string method;
    std::string body;
    std::map<std::string, std::string> headers;

    // Private constructor, we want devs to create it through our builder
    HttpRequest(
        std::string url,
        std::string method,
        std::map<std::string, std::string> headers,
        std::string body
    ) : url(url), method(method), headers(headers), body(body) {}
    // : member initializer list
    // class member url is initialized with constructor param url

public:
    class Builder {
    private:
        std::string urlValue;
        std::string methodValue = "GET";
        std::map<std::string, std::string> headersValue;
        std::string bodyValue;

    public:
        Builder& url(const std::string& value) {
            urlValue = value;
            return *this;
        }

        Builder& method(const std::string& value) {
            methodValue = value;
            return *this;
        }

        Builder& header(const std::string& key, const std::string& value) {
            headersValue[key] = value;
            return *this;
        }

        Builder& body(const std::string& value) {
            bodyValue = value;
            return *this;
        }

        HttpRequest build() {
            if (urlValue.empty()) {
                throw std::invalid_argument("URL is required");
            }

            return HttpRequest(urlValue, methodValue, headersValue, bodyValue);
        }
    };
};

// Usage
// HttpRequest request = HttpRequest::Builder()
//   .url("https://api.example.com")
//   .method("POST")
//   .header("Content-Type", "application/json")
//   .body("{\"key\": \"value\"}")
//   .build();

/* flow -> http ka builder object
    -> its methods to make its private variable
    -> calling build to make a http ka object and then return

    We reuse the same object over and over again with all methods 

    this is a pointer to the object 
    *this is reference so -> its the object

    & of that returns it by reference 
*/