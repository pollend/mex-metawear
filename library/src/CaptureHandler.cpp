/**
* Copyright 2018 GaitRehabilitation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <MexUtility.h>
#include <MetawearWrapper.h>
#include <metawear/sensor/accelerometer.h>
#include <metawear/sensor/magnetometer_bmm150.h>
#include "handlers/CaptureHandler.h"
#include "handlers/ConnectionHandler.h"

CaptureHandler::CaptureHandler(ConnectionHandler *connectionHandler, FunctionWrapper *wrapper):
    m_connectionHandler(connectionHandler){
    std::map<std::string, WrapperMethod *> functions =  {
            //enable
            {"enable_gyro", mexEnableGyro},
            {"enable_accelerometer", mexEnableAccelerometer},
            {"enable_magnetometer", mexEnableMagnetometer},

            //disable
            {"disable_gyro",mexDisableGyro},
            {"disable_accelerometer",mexDisableAccelerometer},
            {"disable_magnetometer", mexDisableMagnetometer}
    };
    wrapper->registerMethod(this, functions);
}

void CaptureHandler::mexEnableMagnetometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs){
    CaptureHandler* handler = static_cast<CaptureHandler*>(context);
    MexUtility::checkNumberOfParameters(engine,MexUtility::ParameterType::INPUT,inputs.size(),2);
    MexUtility::checkType(engine,MexUtility::ParameterType::INPUT,1,inputs[1].getType(),matlab::data::ArrayType::CHAR);

    matlab::data::CharArray address =  inputs[1];
    MetawearWrapper* wrapper =  handler->m_connectionHandler->getDevice(address.toAscii());
    if(wrapper == nullptr)  MexUtility::error(engine, "Unknown Sensor");
    MblMwMetaWearBoard*  board = wrapper->getBoard();

    mbl_mw_mag_bmm150_enable_b_field_sampling(board);
    mbl_mw_mag_bmm150_start(board);
}

void CaptureHandler::mexDisableMagnetometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs){
    CaptureHandler* handler = static_cast<CaptureHandler*>(context);
    MexUtility::checkNumberOfParameters(engine,MexUtility::ParameterType::INPUT,inputs.size(),2);
    MexUtility::checkType(engine,MexUtility::ParameterType::INPUT,1,inputs[1].getType(),matlab::data::ArrayType::CHAR);

    matlab::data::CharArray address =  inputs[1];
    MetawearWrapper* wrapper =  handler->m_connectionHandler->getDevice(address.toAscii());
    if(wrapper == nullptr)  MexUtility::error(engine, "Unknown Sensor");
    MblMwMetaWearBoard*  board = wrapper->getBoard();

    mbl_mw_mag_bmm150_disable_b_field_sampling(board);
    mbl_mw_mag_bmm150_stop(board);
}


void CaptureHandler::mexEnableGyro(std::shared_ptr<matlab::engine::MATLABEngine> engine, void *context,
                                    ParameterWrapper &outputs, ParameterWrapper &inputs) {
    CaptureHandler* handler = static_cast<CaptureHandler*>(context);
    MexUtility::checkNumberOfParameters(engine,MexUtility::ParameterType::INPUT,inputs.size(),2);
    MexUtility::checkType(engine,MexUtility::ParameterType::INPUT,1,inputs[1].getType(),matlab::data::ArrayType::CHAR);

    matlab::data::CharArray address =  inputs[1];
    MetawearWrapper* wrapper =  handler->m_connectionHandler->getDevice(address.toAscii());
    if(wrapper == nullptr)  MexUtility::error(engine, "Unknown Sensor");
    MblMwMetaWearBoard*  board = wrapper->getBoard();
    mbl_mw_gyro_bmi160_enable_rotation_sampling(board);
    mbl_mw_gyro_bmi160_start(board);
}

void  CaptureHandler::mexEnableAccelerometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs){
    CaptureHandler* handler = static_cast<CaptureHandler*>(context);

    if(inputs.size() != 2){
        MexUtility::error(engine, "Three Inputs Required");
        return;
    }

    matlab::data::CharArray address =  inputs[1];
    MetawearWrapper* wrapper =  handler->m_connectionHandler->getDevice(address.toAscii());
    MblMwMetaWearBoard* board = wrapper->getBoard();
    mbl_mw_acc_enable_acceleration_sampling(board);
    mbl_mw_acc_start(board);
}


void CaptureHandler::mexDisableGyro(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs){
    CaptureHandler* handler = static_cast<CaptureHandler*>(context);

    if(inputs.size() != 2){
        MexUtility::error(engine, "Three Inputs Required");
        return;
    }

    matlab::data::CharArray address =  inputs[1];
    MetawearWrapper* wrapper =  handler->m_connectionHandler->getDevice(address.toAscii());
    MblMwMetaWearBoard* board = wrapper->getBoard();
    mbl_mw_gyro_bmi160_disable_rotation_sampling(board);
    mbl_mw_gyro_bmi160_stop(board);
}

void CaptureHandler::mexDisableAccelerometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs) {
    CaptureHandler *handler = static_cast<CaptureHandler *>(context);

    if (inputs.size() != 2) {
        MexUtility::error(engine, "Three Inputs Required");
        return;
    }

    matlab::data::CharArray address = inputs[1];
    MetawearWrapper *wrapper = handler->m_connectionHandler->getDevice(address.toAscii());
    MblMwMetaWearBoard* board = wrapper->getBoard();
    mbl_mw_acc_disable_acceleration_sampling(board);
    mbl_mw_acc_stop(board);
}


CaptureHandler::~CaptureHandler() {

}

