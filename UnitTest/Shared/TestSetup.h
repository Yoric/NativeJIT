#pragma once

#include <memory>

#include "NativeJIT/ExecutionBuffer.h"
#include "NativeJIT/FunctionBuffer.h"
#include "Temporary/Allocator.h"
#include "Temporary/NonCopyable.h"

namespace NativeJIT
{
    // A setup for a test case inside a test class. Features a function buffer
    // and an allocator that will both get reset after the test case ends.
    class TestCaseSetup final : private NonCopyable
    {
    public:
        TestCaseSetup(FunctionBuffer& code, Allocator& generalAllocator);
        ~TestCaseSetup();

        FunctionBuffer& GetCode();
        Allocators::IAllocator& GetAllocator();

    private:
        Allocator& m_allocator;
        FunctionBuffer& m_code;
    };


    class TestClassSetup
    {
    public:
        static const unsigned c_defaultCodeAllocatorCapacity = 5000;
        static const unsigned c_defaultGeneralAllocatorCapacity = 5000;

        TestClassSetup();
        TestClassSetup(unsigned codeAllocatorCapacity,
                       unsigned generalAllocatorCapacity);

        std::unique_ptr<TestCaseSetup> GetSetup();

    private:
        // Executable buffer and general allocator for the function buffer.
        ExecutionBuffer m_codeAllocator;
        Allocator m_generalAllocator;

        // Function buffer and allocator reset after each test run inside a test class.
        FunctionBuffer m_code;
        Allocator m_testCaseAllocator;
    };
}