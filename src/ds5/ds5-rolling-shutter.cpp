// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#include <mutex>
#include <chrono>
#include <vector>
#include <iterator>
#include <cstddef>

#include "device.h"
#include "context.h"
#include "image.h"
#include "metadata-parser.h"

#include "ds5-rolling-shutter.h"
#include "ds5-private.h"
#include "ds5-options.h"
#include "ds5-timestamp.h"

namespace librealsense
{
    ds5_rolling_shutter::ds5_rolling_shutter(std::shared_ptr<context> ctx,
                                             const platform::backend_device_group& group)
        : device(ctx, group), ds5_device(ctx, group)
    {
        using namespace ds;

        auto pid = group.uvc_devices.front().pid;
        if ((_fw_version >= firmware_version("5.5.8.0")) && (pid != RS_USB2_PID))
        {
            get_depth_sensor().register_option(RS2_OPTION_ENABLE_AUTO_WHITE_BALANCE,
                std::make_shared<uvc_xu_option<uint8_t>>(get_depth_sensor(),
                                                         depth_xu,
                                                         DS5_ENABLE_AUTO_WHITE_BALANCE,
                                                         "Enable Auto White Balance"));

            // To be checked whether this is still required
            // get_depth_sensor().register_pixel_format(pf_rgb888);
        }
    }
}
