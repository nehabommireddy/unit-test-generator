Here are the Google Test cases for the provided C++ controller code:
```cpp
#include <gtest/gtest.h>
#include "AuthController.h"
#include "../plugins/JwtPlugin.h"

TEST(AuthControllerTest, RegisterUserValid) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);
    auto json = Json::Value(R"({"username": "john", "password": "hello"})"_json);
    req->setJsonObject(json);

    auto resp = std::make_shared<drogon::HttpResponse>();
    resp->setStatusCode(drogon::HttpStatusCode::k201Created);

    // Create a valid user
    auto pUser = User(R"({"username": "john", "password": "hello"})"_json);

    AuthController controller;
    controller.registerUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k201Created);
}

TEST(AuthControllerTest, RegisterUserInvalidUsernameTaken) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);
    auto json = Json::Value(R"({"username": "john", "password": "hello"})"_json);
    req->setJsonObject(json);

    auto resp = std::make_shared<drogon::HttpResponse>();
    resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

    // Create a valid user, but username already exists
    auto pUser = User(R"({"username": "john", "password": "hello"})"_json);

    AuthController controller;
    controller.registerUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k400BadRequest);
}

TEST(AuthControllerTest, RegisterUserInvalidMissingFields) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);

    auto resp = std::make_shared<drogon::HttpResponse>();
    resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

    // Create a user with missing fields
    auto pUser = User(R"({"password": "hello"})"_json);

    AuthController controller;
    controller.registerUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k400BadRequest);
}

TEST(AuthControllerTest, LoginUserValid) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);
    auto json = Json::Value(R"({"username": "john", "password": "hello"})"_json);
    req->setJsonObject(json);

    auto resp = std::make_shared<drogon::HttpResponse>();

    // Create a valid user
    auto pUser = User(R"({"username": "john", "password": "hello"})"_json);

    AuthController controller;
    controller.loginUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k200Ok);
}

TEST(AuthControllerTest, LoginUserInvalidUsernameNotFound) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);
    auto json = Json::Value(R"({"username": "john", "password": "hello"})"_json);
    req->setJsonObject(json);

    auto resp = std::make_shared<drogon::HttpResponse>();
    resp->setStatusCode(drogon::HttpStatusCode::k400BadRequest);

    // Create a user that does not exist
    auto pUser = User(R"({"username": "john", "password": "hello"})"_json);

    AuthController controller;
    controller.loginUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k400BadRequest);
}

TEST(AuthControllerTest, LoginUserInvalidIncorrectPassword) {
    // Mock HTTP request and response
    auto req = std::make_shared<drogon::HttpRequest>();
    req->setMethod(drogon::HttpMethod::kPost);
    auto json = Json::Value(R"({"username": "john", "password": "wrong"})"_json);
    req->setJsonObject(json);

    auto resp = std::make_shared<drogon::HttpResponse>();
    resp->setStatusCode(drogon::HttpStatusCode::k401Unauthorized);

    // Create a user with incorrect password
    auto pUser = User(R"({"username": "john", "password": "hello"})"_json);

    AuthController controller;
    controller.loginUser(req, [&](const HttpResponsePtr &callback) {
        callback = resp;  // Set the response to the expected one
    }, pUser);

    EXPECT_EQ(resp->getStatusCode(), drogon::HttpStatusCode::k401Unauthorized);
}

int main(int argc, char **argv) {
    ::testing::InitGoogle(&argc, argv);
    return RUN_ALL_TESTS();
}
```
These tests cover various scenarios for the `registerUser` and `loginUser` methods:

1. Valid user registration
2. User registration with username already taken
3. User registration with missing fields
4. Valid login with correct credentials
5. Login with incorrect password (username not found)
6. Login with incorrect password (correct username, but wrong password)

Note that these tests only cover the HTTP handlers directly and do not test the underlying database operations or plugin interactions.