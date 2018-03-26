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

#ifndef __ELASTOS_IO_CHANNELS_SINKCHANNEL_H__
#define __ELASTOS_IO_CHANNELS_SINKCHANNEL_H__

#include "elastos/io/channels/spi/AbstractSelectableChannel.h"

using Elastos::IO::Channels::Spi::ISelectorProvider;
using Elastos::IO::Channels::Spi::AbstractSelectableChannel;

namespace Elastos {
namespace IO {
namespace Channels {

class SinkChannel
    : public AbstractSelectableChannel
    , public ISinkChannel
    , public IWritableByteChannel
    , public IGatheringByteChannel
{
public:
    CAR_INTERFACE_DECL()

    CARAPI GetValidOps(
        /* [out] */ Int32* ret);

protected:
    SinkChannel();

    SinkChannel(
        /* [in] */ ISelectorProvider* provider);
};

} // namespace Channels
} // namespace IO
} // namespace Elastos

#endif // __ELASTOS_IO_CHANNELS_SINKCHANNEL_H__
