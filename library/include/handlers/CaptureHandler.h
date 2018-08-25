//
// Created by Michael on 8/24/2018.
//

#ifndef MEX_METAWEAR_CAPTUREHANDLER_H
#define MEX_METAWEAR_CAPTUREHANDLER_H

#include <map>
#include <mex.hpp>
#include "FunctionWrapper.h"

class FunctionWrapper;
class ConnectionHandler;
class CaptureHandler{
private:
    ConnectionHandler* m_connectionHandler;
public:
    CaptureHandler(ConnectionHandler* connectionHandler,FunctionWrapper* wrapper);
    ~CaptureHandler();

    static void mexEnableGyro(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs);
    static void mexEnableAccelerometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs);

    static void mexDisableGyro(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs);
    static void mexDisableAccelerometer(std::shared_ptr<matlab::engine::MATLABEngine> engine,void *context,  ParameterWrapper& outputs, ParameterWrapper& inputs);

};
#endif //MEX_METAWEAR_CAPTUREHANDLER_H
