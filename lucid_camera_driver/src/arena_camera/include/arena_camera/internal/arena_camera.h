/******************************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright (C) 2016, Magazino GmbH. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Magazino GmbH nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef ARENA_CAMERA_INTERNAL_ARENA_CAMERA_H
#define ARENA_CAMERA_INTERNAL_ARENA_CAMERA_H

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wliteral-suffix"

#include <GenApi/IEnumEntry.h>
#include <string>
#include <vector>
#include <map>

#include <arena_camera/arena_camera_parameter.h>
#include <arena_camera/arena_camera.h>

namespace arena_camera
{
    template <typename CameraTraitT>
    
    class ArenaCameraImpl : public ArenaCamera
    {
        public:
            explicit ArenaCameraImpl();

            virtual ~ArenaCameraImpl();

            virtual bool registerCameraConfiguration();

            virtual bool openCamera();

            virtual bool isCamRemoved();

            virtual bool setupSequencer(const std::vector<float>& exposure_times);

            virtual bool applyCamSpecificStartupSettings(const ArenaCameraParameter& parameters);

            virtual bool startGrabbing(const ArenaCameraParameter& parameters);

            virtual bool grab(std::vector<uint8_t>& image);

            virtual bool grab(uint8_t* image);

            virtual bool setShutterMode(const arena_camera::SHUTTER_MODE& mode);

            virtual bool setROI(const sensor_msgs::RegionOfInterest target_roi,
                                sensor_msgs::RegionOfInterest& reached_roi);

            virtual bool setBinningX(const size_t& target_binning_x,
                                        size_t& reached_binning_x);

            virtual bool setBinningY(const size_t& target_binning_y,
                                        size_t& reached_binning_y);

            virtual bool setImageEncoding(const std::string& target_ros_encoding);

            virtual bool setExposure(const float& target_exposure, float& reached_exposure);

            virtual bool setAutoflash(const std::map<int, bool> flash_on_lines);

            virtual bool setGain(const float& target_gain, float& reached_gain);

            virtual bool setGamma(const float& target_gamma, float& reached_gamma);

            virtual bool setBrightness(const int& target_brightness,
                                        const float& current_brightness,
                                        const bool& exposure_auto, const bool& gain_auto);

            virtual std::vector<int> detectAndCountNumUserOutputs();

            virtual bool setUserOutput(const int& output_id, const bool& value);

            virtual size_t currentOffsetX();

            virtual size_t currentOffsetY();

            virtual sensor_msgs::RegionOfInterest currentROI();

            virtual size_t currentBinningX();

            virtual size_t currentBinningY();

            virtual std::vector<std::string> detectAvailableImageEncodings();

            virtual std::string currentROSEncoding() const;

            virtual int imagePixelDepth() const;

            virtual float currentExposure();

            virtual float currentAutoExposureTimeLowerLimit();

            virtual float currentAutoExposureTimeUpperLimit();

            virtual float currentGain();

            virtual float currentAutoGainLowerLimit();

            virtual float currentAutoGainUpperLimit();

            virtual float currentGamma();

            virtual float maxPossibleFramerate();

            virtual bool isArenaAutoBrightnessFunctionRunning();

            virtual bool isBrightnessSearchRunning();

            virtual void disableAllRunningAutoBrightessFunctions();

            virtual void enableContinuousAutoExposure();

            virtual void enableContinuousAutoGain();

            virtual std::string typeName() const;

            virtual float exposureStep();

        protected:
            typedef typename CameraTraitT::ExposureAutoEnums ExposureAutoEnums;
            typedef typename CameraTraitT::GainAutoEnums GainAutoEnums;
            typedef typename CameraTraitT::PixelFormatEnums PixelFormatEnums;
            typedef typename CameraTraitT::PixelSizeEnums PixelSizeEnums;
            typedef typename CameraTraitT::AutoTargetBrightnessType AutoTargetBrightnessType;
            typedef typename CameraTraitT::GainType GainType;
            typedef typename CameraTraitT::ShutterModeEnums ShutterModeEnums;
            typedef typename CameraTraitT::UserOutputSelectorEnums UserOutputSelectorEnums;

            GenApi::IFloat& gamma();
            GenApi::IFloat& exposureTime();
            GenApi::IFloat& autoExposureTimeLowerLimit();
            GenApi::IFloat& autoExposureTimeUpperLimit();
            GenApi::IFloat& resultingFrameRate();
            
            GainType& gain();
            GainType& autoGainLowerLimit();
            GainType& autoGainUpperLimit();
            
            AutoTargetBrightnessType& autoTargetBrightness();

            virtual bool setExtendedBrightness(const int& target_brightness,
                                                const float& current_brightness);

            virtual bool setupSequencer(const std::vector<float>& exposure_times,
                                        std::vector<float>& exposure_times_set);
    };

}  // namespace arena_camera

#endif  // ARENA_CAMERA_INTERNAL_ARENA_CAMERA_H