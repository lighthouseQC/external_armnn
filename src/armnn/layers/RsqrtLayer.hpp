//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <Layer.hpp>

namespace armnn
{

class RsqrtLayer : public Layer
{
public:
    /// Makes a workload for the Rsqrt type.
    /// @param [in] graph The graph where this layer can be found.
    /// @param [in] factory The workload factory which will create the workload.
    /// @return A pointer to the created workload, or nullptr if not created.
    virtual std::unique_ptr<IWorkload> CreateWorkload(const IWorkloadFactory& factory) const override;

    /// Creates a dynamically-allocated copy of this layer.
    /// @param [in] graph The graph into which this layer is being cloned.
    RsqrtLayer* Clone(Graph& graph) const override;

    /// Check if the input tensor shape(s)
    /// will lead to a valid configuration of @ref RsqrtLayer.
    void ValidateTensorShapesFromInputs() override;

    void Accept(ILayerVisitor& visitor) const override;

protected:
    /// Constructor to create an RsqrtLayer.
    /// @param [in] name Optional name for the layer.
    RsqrtLayer(const char* name);

    /// Default destructor
    ~RsqrtLayer() = default;
};

} // namespace