#pragma once
#include <exception>
#include <string>


class OutOfRangeException : public std::exception {
    std::string m_err;
public:
    OutOfRangeException(std::string err) : m_err(std::move(err)) {}

    const char* what() const noexcept override {
        return m_err.c_str();
    }
};


class EmptyContainerException : public std::exception {
    std::string m_err;
public:
    EmptyContainerException(std::string err) : m_err(std::move(err)) {}

    const char* what() const noexcept override {
        return m_err.c_str();
    }
};


class BadAllocException : public std::exception {
    std::string m_err;
public:
    BadAllocException(std::string err) : m_err(std::move(err)) {}
    const char* what() const noexcept override {
        return m_err.c_str();
    }
};


class BadIterator : public std::exception {
    std::string m_err;
public:
    BadIterator(std::string err) : m_err(std::move(err)) {}
    const char* what() const noexcept override {
        return m_err.c_str();
    }
};