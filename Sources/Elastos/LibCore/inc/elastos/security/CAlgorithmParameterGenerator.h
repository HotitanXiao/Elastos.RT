//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_SECURITY_CALGORITHMPARAMETERGENERATOR_H__
#define __ELASTOS_SECURITY_CALGORITHMPARAMETERGENERATOR_H__

#include "_Elastos_Security_CAlgorithmParameterGenerator.h"
#include "elastos/security/AlgorithmParameterGeneratorSpi.h"

using Elastos::Core::Object;
using Elastos::Security::Spec::IAlgorithmParameterSpec;
using Org::Apache::Harmony::Security::Fortress::IEngine;

namespace Elastos {
namespace Security {

/**
 * {@code AlgorithmParameterGenerator} is an engine class which is capable of
 * generating parameters for the algorithm it was initialized with.
 */
CarClass(CAlgorithmParameterGenerator)
    , public Object
    , public IAlgorithmParameterGenerator
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    /**
     * Constructs a new instance of {@code AlgorithmParameterGenerator} with the
     * given arguments.
     *
     * @param paramGenSpi
     *            a concrete implementation, this engine instance delegates to.
     * @param provider
     *            the provider.
     * @param algorithm
     *            the name of the algorithm.
     */
    CARAPI constructor(
        /* [in] */ IAlgorithmParameterGeneratorSpi* paramGenSpi,
        /* [in] */ IProvider* provider,
        /* [in] */ const String& algorithm);

    /**
     * Returns the name of the algorithm.
     *
     * @return the name of the algorithm.
     */
    CARAPI GetAlgorithm(
        /* [out] */ String* algorithm);

    /**
     * Returns a new instance of {@code AlgorithmParameterGenerator} for the
     * specified algorithm.
     *
     * @param algorithm
     *            the name of the algorithm to use.
     * @return a new instance of {@code AlgorithmParameterGenerator} for the
     *         specified algorithm.
     * @throws NoSuchAlgorithmException
     *             if the specified algorithm is not available.
     * @throws NullPointerException
     *             if {@code algorithm} is {@code null}.
     */
    static CARAPI GetInstance(
        /* [in] */ const String& algorithm,
        /* [out] */ IAlgorithmParameterGenerator** generator) /*throws NoSuchAlgorithmException*/;

    /**
     * Returns a new instance of {@code AlgorithmParameterGenerator} from the
     * specified provider for the specified algorithm.
     *
     * @param algorithm
     *            the name of the algorithm to use.
     * @param provider
     *            name of the provider of the {@code
     *            AlgorithmParameterGenerator}.
     * @return a new instance of {@code AlgorithmParameterGenerator} for the
     *         specified algorithm.
     * @throws NoSuchAlgorithmException
     *             if the specified algorithm is not available.
     * @throws NoSuchProviderException
     *             if the specified provider is not available.
     * @throws IllegalArgumentException if {@code provider == null || provider.isEmpty()}
     * @throws NullPointerException
     *             if {@code algorithm} is {@code null}.
     */
    static CARAPI GetInstance(
        /* [in] */ const String& algorithm,
        /* [in] */ const String& provider,
        /* [out] */ IAlgorithmParameterGenerator** generator) /*throws NoSuchAlgorithmException, NoSuchProviderException*/;

    /**
     * Returns a new instance of {@code AlgorithmParameterGenerator} from the
     * specified provider for the specified algorithm. The {@code provider}
     * supplied does not have to be registered.
     *
     * @param algorithm
     *            the name of the algorithm to use.
     * @param provider
     *            the provider of the {@code AlgorithmParameterGenerator}.
     * @return a new instance of {@code AlgorithmParameterGenerator} for the
     *         specified algorithm.
     * @throws NoSuchAlgorithmException
     *             if the specified algorithm is not available.
     * @throws NullPointerException
     *             if {@code algorithm} is {@code null}.
     * @throws IllegalArgumentException if {@code provider == null}
     */
    static CARAPI GetInstance(
        /* [in] */ const String& algorithm,
        /* [in] */ IProvider* provider,
        /* [out] */ IAlgorithmParameterGenerator** generator) /*throws NoSuchAlgorithmException*/;

    /**
     * Returns the provider associated with this {@code
     * AlgorithmParameterGenerator}.
     *
     * @return the provider associated with this {@code
     *         AlgorithmParameterGenerator}.
     */
    CARAPI GetProvider(
        /* [out] */ IProvider** provider);

    /**
     * Initializes this {@code AlgorithmParameterGenerator} with the given size.
     * The default parameter set and a default {@code SecureRandom} instance
     * will be used.
     *
     * @param size
     *            the size (in number of bits).
     */
    CARAPI Init(
        /* [in] */ Int32 size);

    /**
     * Initializes this {@code AlgorithmParameterGenerator} with the given size
     * and the given {@code SecureRandom}. The default parameter set will be
     * used.
     *
     * @param size
     *            the size (in number of bits).
     * @param random
     *            the source of randomness.
     */
    CARAPI Init(
        /* [in] */ Int32 size,
        /* [in] */ ISecureRandom* random);

    /**
     * Initializes this {@code AlgorithmParameterGenerator} with the given {@code
     * AlgorithmParameterSpec}. A default {@code SecureRandom} instance will be
     * used.
     *
     * @param genParamSpec
     *            the parameters to use.
     * @throws InvalidAlgorithmParameterException
     *             if the specified parameters are not supported.
     */
    CARAPI Init(
        /* [in] */ IAlgorithmParameterSpec* genParamSpec) /*throws InvalidAlgorithmParameterException*/;

    /**
     * Initializes this {@code AlgorithmParameterGenerator} with the given
     * {@code AlgorithmParameterSpec} and the given {@code SecureRandom}.
     *
     * @param genParamSpec
     *            the parameters to use.
     * @param random
     *            the source of randomness.
     * @throws InvalidAlgorithmParameterException
     *             if the specified parameters are not supported.
     */
    CARAPI Init(
        /* [in] */ IAlgorithmParameterSpec* genParamSpec,
        /* [in] */ ISecureRandom* random) /*throws InvalidAlgorithmParameterException*/;

    /**
     * Computes and returns {@code AlgorithmParameters} for this generator's
     * algorithm.
     *
     * @return {@code AlgorithmParameters} for this generator's algorithm.
     */
    CARAPI GenerateParameters(
        /* [out] */ IAlgorithmParameters** param);

private:
    // Store spi service name
    static const String SERVICE;

    // Used to access common engine functionality
    static AutoPtr<IEngine> ENGINE;

    // Store SecureRandom
    static AutoPtr<ISecureRandom> RANDOM;

    // Store used provider
    AutoPtr<IProvider> mProvider;

    // Store used AlgorithmParameterGeneratorSpi implementation
    AutoPtr<AlgorithmParameterGeneratorSpi> mSpiImpl;

    //Store used algorithm
    String mAlgorithm;
};

} // namespace Security
} // namespace Elastos

#endif // __ELASTOS_SECURITY_CALGORITHMPARAMETERGENERATOR_H__
