//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "SubtractionTestImpl.hpp"

#include "ElementwiseTestImpl.hpp"

template<>
std::unique_ptr<armnn::IWorkload> CreateWorkload<armnn::SubtractionQueueDescriptor>(
    const armnn::IWorkloadFactory& workloadFactory,
    const armnn::WorkloadInfo& info,
    const armnn::SubtractionQueueDescriptor& descriptor)
{
    return workloadFactory.CreateSubtraction(descriptor, info);
}

LayerTestResult<uint8_t, 4> SubtractionUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 2, 2 };

    std::vector<uint8_t> input0 = { 10, 12, 14, 16 };
    std::vector<uint8_t> input1 = {  1,  2,  1,  2 };
    std::vector<uint8_t> output = {  3,  3,  5,  5 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        0.5f,
        2,
        shape1,
        input1,
        1.0f,
        0,
        shape0,
        output,
        1.0f,
        0);
}

LayerTestResult<uint8_t, 4> SubtractionBroadcast1ElementUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<uint8_t> input0 = { 10, 12, 14, 16 };

    std::vector<uint8_t> input1 = { 2 };

    std::vector<uint8_t> output = { 5, 6, 7, 8 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        0.5f,
        2,
        shape1,
        input1,
        1.0f,
        0,
        shape0,
        output,
        1.0f,
        3);
}

LayerTestResult<uint8_t, 4> SubtractionBroadcastUint8Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 2, 1 };

    std::vector<uint8_t> input0 = { 10, 12, 14, 16 };

    std::vector<uint8_t> input1 = { 2, 1 };

    std::vector<uint8_t> output = { 8, 11, 12, 15 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedAsymm8>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<float, 4> SubtractionTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 2, 2 };

    std::vector<float> input0 = { 1,  2, 3, 4 };
    std::vector<float> input1 = { 1, -1, 0, 2 };
    std::vector<float> output = { 0,  3, 3, 2 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<float, 4> SubtractionBroadcast1ElementTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<float> input0 = { 1,  2, 3, 4 };

    std::vector<float> input1 = { 10 };

    std::vector<float> output = { -9,  -8, -7, -6 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<float, 4> SubtractionBroadcastTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 1, 2 };

    std::vector<float> input0 = { 1,  2, 3, 4 };

    std::vector<float> input1 = { 10, -5 };

    std::vector<float> output = { -9,  7, -7, 9 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::Float32>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}

LayerTestResult<int16_t, 4> SubtractionInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape[] = { 1, 1, 2, 2 };

    std::vector<int16_t> input0 = { 10, 12, 14, 16 };
    std::vector<int16_t> input1 = {  1,  2,  1,  2 };
    std::vector<int16_t> output = {  3,  3,  5,  5 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape,
        input0,
        0.5f,
        0,
        shape,
        input1,
        1.0f,
        0,
        shape,
        output,
        1.0f,
        0);
}

LayerTestResult<int16_t, 4> SubtractionBroadcast1ElementInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 1, 1 };

    std::vector<int16_t> input0 = { 10, 12, 14, 16 };

    std::vector<int16_t> input1 = { 2 };

    std::vector<int16_t> output = { 3, 4, 5, 6 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        0.5f,
        0,
        shape1,
        input1,
        1.0f,
        0,
        shape0,
        output,
        1.0f,
        0);
}

LayerTestResult<int16_t, 4> SubtractionBroadcastInt16Test(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    const unsigned int shape0[] = { 1, 1, 2, 2 };
    const unsigned int shape1[] = { 1, 1, 2, 1 };

    std::vector<int16_t> input0 = { 10, 12, 14, 16 };

    std::vector<int16_t> input1 = { 2, 1 };

    std::vector<int16_t> output = { 8, 11, 12, 15 };

    return ElementwiseTestHelper<4, armnn::SubtractionQueueDescriptor, armnn::DataType::QuantisedSymm16>(
        workloadFactory,
        memoryManager,
        shape0,
        input0,
        shape1,
        input1,
        shape0,
        output);
}
