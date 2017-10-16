//
// Created by shiyang on 10/14/17.
//

#ifndef EXERCISE_ENVIRONMENT_H
#define EXERCISE_ENVIRONMENT_H


#include <gtest/gtest.h>
#include <memory>
namespace unitTest {
    class Resource {
    public:
        explicit Resource(int v = 0) : val(v) {}

        virtual ~Resource() = default;

        int getVal() const { return val; }

        void setVal(int val) { this->val = val; }

    private:
        int val;
    };

    class PrivateResource : public Resource {
    public:
       explicit PrivateResource(int v = 0) : Resource(v) {
            std::cout << "PrivateResource constructed" << std::endl;
        }

        ~PrivateResource() override {
            std::cout << "PrivateResource destructed" << std::endl;
        }
    };


    class SharedResource : public Resource {
    public:
        explicit SharedResource(int v = 0) : Resource(v) {
            std::cout << "SharedResource constructed" << std::endl;
        }

        ~SharedResource() override {
            std::cout << "SharedResource destructed" << std::endl;
        }

    };


    class FooTest : public testing::Test {
    public:

        static void SetUpTestCase() {
            sharedResource.reset(new SharedResource());
            std::cout << "FooTest static set up" << std::endl;
        }

        static void TearDownTestCase() {
            sharedResource.reset();
            std::cout << "FooTest static tear down" << std::endl;
        }

        static std::unique_ptr<SharedResource> sharedResource;

    protected:
        virtual void SetUp() override {
            privateResource.reset(new PrivateResource());
        }

        virtual void TearDown() override {
            privateResource.reset();
        }

        std::unique_ptr<PrivateResource> privateResource;

    };

    class Integer {
        friend std::ostream &operator<<(std::ostream &os, const Integer&);
    public:
        // do not declare a default constructor, as it may lead to compile error.
        explicit Integer(int v = 0) : val(v) {}

        Integer& operator++() {
            ++val;
            return *this;
        }
        Integer& operator=(int v) {
            val = v;
            return *this;
        }
        Integer operator++(int) {
            auto ret = *this;
            ++val;
            return ret;
        }

        bool operator==(const Integer& rhs) const {
            return val == rhs.val;
        }

        bool operator <(const Integer& rhs) const {
            return val < rhs.val;
        }

        const int& getVal() const {
            return val;
        }

    private:
        int val;
    };

    std::ostream &operator<<(std::ostream &os, const Integer& integer) {
        std::cout << integer.val;
        return os;
    }

}
#endif //EXERCISE_ENVIRONMENT_H
