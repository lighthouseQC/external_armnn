//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "DivisionTestImpl.hpp"

#include "ElementwiseTestImpl.hpp"

template<>
std::unique_ptr<armnn::IWorkload> CreateWorkload<armnn::DivisionQueueDescriptor>(
    const armnn::IWorkloadFactory& workloadFactory,
    const armnn::WorkloadInfo& info,
    const armnn::DivisionQueueDescriptor& descriptor)
{
    return workloadFactory.CreateDivision(descriptor, info);
}

LayerTestResult<float, 4> DivisionByZeroTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int width        = 2u;
    const unsigned int height       = 2u;
    const unsigned int channelCount = 2u;
    const unsigned int batchSize    = 2u;

    unsigned int shape[] = { batchSize, channelCount, height, width };

    std::vector<float> input0 =
    {
         1.f,  1.f,  1.f,  1.f,  0.f, 0.f, 0.f, 0.f,
        -1.f, -1.f, -1.f, -1.f,  5.f, 5.f, 5.f, 5.f
    };

    std::vector<float> input1 =
    {
        0.f, 0.f, -0.f, -0.f,  0.f, 0.f, -0.f, -0.f,
        0.f, 0.f, -0.f, -0.f,  5.f, 5.f,  5.f,  5.f
    };

    std::vector<float> output =
    {
         INFINITY,  INFINITY, -INFINITY, -INFINITY,  NAN,  NAN, -NAN, -NAN,
        -INFINITY, -INFINITY,  INFINITY,  INFINITY,    1,    1,    1,    1
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape,
        input0,
        shape,
        input1,
        shape,
        output);
}

LayerTestResult<float, 4> DivisionTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int width        = 2u;
    const unsigned int height       = 2u;
    const unsigned int channelCount = 2u;
    const unsigned int batchSize    = 2u;

    unsigned int shape[] = { batchSize, channelCount, height, width };

    std::vector<float> input0 =
    {
        2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f,
        4.f, 4.f, 4.f, 4.f, 5.f, 5.f, 5.f, 5.f
    };

    std::vector<float> input1 =
    {
        1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f,
        4.f, 4.f, 4.f, 4.f, 4.f, 4.f, 4.f, 4.f
    };

    std::vector<float> output =
    {
        2.f, 2.f, 2.f, 2.f, 1.50f, 1.50f, 1.50f, 1.50f,
        1.f, 1.f, 1.f, 1.f, 1.25f, 1.25f, 1.25f, 1.25f
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape,
        input0,
        shape,
        input1,
        shape,
        output);
}

LayerTestResult<float, 4> DivisionBroadcast1ElementTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 2, 2, 2 };
    unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<float> input0({ 2, 4, 6, 8, 10, 12, 14, 16});

    std::vector<float> input1({ 2 });

    std::vector<float> output({ 1, 2, 3, 4, 5, 6, 7, 8});

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<float, 4> DivisionBroadcast1DVectorTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 3, 3, 2 };
    unsigned int shape1[] = { 1, 1, 1, 2 };

    std::vector<float> input0 =
    {
         1.f,  4.f,  3.f,  8.f,  5.f, 12.f,
         7.f, 16.f,  9.f, 20.f, 11.f, 24.f,
        13.f, 28.f, 15.f, 32.f, 17.f, 36.f
    };

    std::vector<float> input1 = { 1.f, 2.f };

    std::vector<float> output =
    {
         1.f,  2.f,  3.f,  4.f,  5.f,  6.f,
         7.f,  8.f,  9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f, 17.f, 18.f
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<uint8_t, 4> DivisionUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int width        = 2u;
    const unsigned int height       = 2u;
    const unsigned int channelCount = 2u;
    const unsigned int batchSize    = 2u;

    unsigned int shape[] = { batchSize, channelCount, height, width };

    std::vector<uint8_t> input0 =
    {
        2, 2, 2, 2,  3, 3, 3, 3,
        4, 4, 4, 4,  5, 5, 5, 5
    };

    std::vector<uint8_t> input1 =
    {
        1, 1, 1, 1,  2, 2, 2, 2,
        4, 4, 4, 4,  4, 4, 4, 4
    };

    std::vector<uint8_t> output =
    {
        8, 8, 8, 8,  6, 6, 6, 6,
        4, 4, 4, 4,  5, 5, 5, 5
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape,
        input0,
        shape,
        input1,
        shape,
        output,
        0.25f,
        0);
}

LayerTestResult<uint8_t, 4> DivisionBroadcast1ElementUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 2, 2, 2 };
    unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<uint8_t> input0 = { 2, 4, 6, 8, 10, 12, 14, 16};

    std::vector<uint8_t> input1 = { 2 };

    std::vector<uint8_t> output = { 1, 2, 3, 4, 5, 6, 7, 8};

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<uint8_t, 4> DivisionBroadcast1DVectorUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 3, 3, 2 };
    unsigned int shape1[] = { 1, 1, 1, 2 };

    std::vector<uint8_t> input0 =
    {
        1,  4,    3,  8,    5, 12,
        7, 16,    9, 20,   11, 24,
       13, 28,   15, 32,   17, 36
    };

    std::vector<uint8_t> input1 = { 1, 2 };

    std::vector<uint8_t> output =
    {
        1,  2,    3,  4,    5,  6,
        7,  8,    9, 10,   11, 12,
       13, 14,   15, 16,   17, 18
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<int16_t,4> DivisionInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape[] = { 2, 2, 2, 2 };

    std::vector<int16_t> input0 =
    {
        2, 2, 2, 2,  3, 3, 3, 3,
        4, 4, 4, 4,  5, 5, 5, 5
    };

    std::vector<int16_t> input1 =
    {
        1, 1, 1, 1,  2, 2, 2, 2,
        4, 4, 4, 4,  4, 4, 4, 4
    };

    std::vector<int16_t> output =
    {
        8, 8, 8, 8,  6, 6, 6, 6,
        4, 4, 4, 4,  5, 5, 5, 5
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape,
        input0,
        shape,
        input1,
        shape,
        output,
        0.25f,
        0);
}

LayerTestResult<int16_t, 4> DivisionBroadcast1ElementInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 2, 2, 2 };
    unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<int16_t> input0 = { 2, 4, 6, 8, 10, 12, 14, 16};

    std::vector<int16_t> input1 = { 2 };

    std::vector<int16_t> output = { 1, 2, 3, 4, 5, 6, 7, 8};

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<int16_t, 4> DivisionBroadcast1DVectorInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    unsigned int shape0[] = { 1, 3, 3, 2 };
    unsigned int shape1[] = { 1, 1, 1, 2 };

    std::vector<int16_t> input0 =
    {
         1,  4,    3,  8,    5, 12,
         7, 16,    9, 20,   11, 24,
        13, 28,   15, 32,   17, 36
    };

    std::vector<int16_t> input1 = { 1, 2 };

    std::vector<int16_t> output =
    {
         1,  2,    3,  4,    5,  6,
         7,  8,    9, 10,   11, 12,
        13, 14,   15, 16,   17, 18
    };

    return ElementwiseTestHelper<4, armnn::DivisionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}
