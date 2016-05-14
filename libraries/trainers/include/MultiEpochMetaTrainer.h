////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     MultiEpochMetaTrainer.h (trainers)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ITrainer.h"
#include "IStatefulTrainer.h"

// dataset
#include "RowDataset.h"

//stl
#include <utility>
#include <memory>

namespace trainers
{
    /// <summary> Parameters for the multi-epoch meta-trainer. </summary>
    struct MultiEpochMetaTrainerParameters
    {
        uint64_t numEpochs = 1;
    };

    /// <summary> A class that performs multiple epochs of a learner and exposes a trainer. </summary>
    ///
    /// <typeparam name="PredictorType"> The type of predictor returned by this trainer. </typeparam>
    template <typename PredictorType>
    class MultiEpochMetaTrainer : public ITrainer<PredictorType>
    {
    public:
        MultiEpochMetaTrainer() = delete;

        /// <summary> Constructs an instance of MultiEpochMetaTrainer. </summary>
        ///
        /// <param name="statefulTrainer"> [in,out] The stateful trainer. </param>
        MultiEpochMetaTrainer(std::unique_ptr<IStatefulTrainer<PredictorType>>&& statefulTrainer, const MultiEpochMetaTrainerParameters& parameters);

        /// <summary> Trains and returns a predictor. </summary>
        ///
        /// <param name="exampleIterator"> An example iterator that represents the training set. </param>
        ///
        /// <returns> The trained predictor. </returns>
        virtual PredictorType Train(dataset::GenericRowDataset::Iterator exampleIterator) const;

    private:
        std::unique_ptr<IStatefulTrainer<PredictorType>> _statefulTrainer;
        MultiEpochMetaTrainerParameters _parameters;
    };

    template <typename PredictorType>
    std::unique_ptr<ITrainer<PredictorType>> MakeMultiEpochMetaTrainer(std::unique_ptr<IStatefulTrainer<PredictorType>>&& statefulTrainer);
}

#include "../tcc/MultiEpochMetaTrainer.tcc"
